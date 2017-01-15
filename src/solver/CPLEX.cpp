/*
 * Copyright 2015 Marco Zanella
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Victor.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <cfloat>
#include <string>
#include <vector>
#include <map>

#include "CPLEX.h"


/**
 * Skips an iteration of a loop if an arc does not exist.
 * An arc is skipped when it is a self loop or when there is no arc.
 */
#define SKIP_NON_EXISTING_ARCS(instance, i, j) {       \
    if (i == j || skip_arc[i][j]) {                    \
        continue;                                      \
    }                                                  \
}



using std::vector;

namespace solver {

CPLEX::~CPLEX() {
}



Solution CPLEX::solve(const Instance &instance) const {
    CPLEXManager cplex;

    char name[16];
    unsigned int i, j, k;
    vector<Node> nodes(instance.getNodesAsVector()), solution;
    const unsigned int N = nodes.size();
    vector<Node*> projection(N);
    vector<double> ones;
    map< int, map<int, bool> > skip_arc;


    // Pre-calculates some support informations
    for (i = 0; i < N; i++) {
        projection[i] = &nodes[i];
        ones.push_back(1.0);
        for (j = 0; j < N; j++) {
            bool arc = instance.hasArc(nodes[i].getId(), nodes[j].getId());
            skip_arc[i][j] = !arc;
        }
    }


    // TSP is a minimization problem
    cplex.setMin();



    // Adds variables x_i_j: flow from i to j
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            SKIP_NON_EXISTING_ARCS(instance, i, j);

            snprintf(name, sizeof(name), "x_%u_%u", i, j);
            cplex.addIntegerVar(name, 0.0, 0.0);
        }
    }


    // Adds variables y_i_j: 1 iff arch from i to j is used
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            SKIP_NON_EXISTING_ARCS(instance, i, j);

            double c = instance.getCost(nodes[i].getId(), nodes[j].getId());
            snprintf(name, sizeof(name), "y_%u_%u", i, j);
            cplex.addBooleanVar(name, c);
        }
    }


    // Adds Starting Flow constraint
    // At the beginning, x_0 has all the flow units
    vector<string> x_0j;
    for (j = 0; j < N; j++) {
        SKIP_NON_EXISTING_ARCS(instance, 0, j);

        snprintf(name, sizeof(name), "x_0_%u", j);
        x_0j.push_back(name);
    }
    cplex.addEqConstraint(ones, x_0j, N);



    // Adds Flow-Balance constraint
    // Incoming flow is equal to outcoming flow plus one unit (which is
    // kept by the node)
    for (k = 1; k < N; k++) {
        vector<string> x_k;
        vector<double> coeff;
        for (i = 0; i < N; i++) {
            SKIP_NON_EXISTING_ARCS(instance, i, k);

            snprintf(name, sizeof(name), "x_%u_%u", i, k);
            x_k.push_back(name);
            coeff.push_back(1.0);
        }

        for (j = 0; j < N; j++) {
            SKIP_NON_EXISTING_ARCS(instance, k, j);

            snprintf(name, sizeof(name), "x_%u_%u", k, j);
            x_k.push_back(name);
            coeff.push_back(-1.0);
        }
        cplex.addEqConstraint(coeff, x_k, 1);
    }



    // y_i will give away exactly one unit of flow
    for (i = 0; i < N; i++) {
       vector<string> y_ij;
       for (j = 0; j < N; j++) {
            SKIP_NON_EXISTING_ARCS(instance, i, j);

            snprintf(name, sizeof(name), "y_%u_%u", i, j);
            y_ij.push_back(name);
       }
       cplex.addEqConstraint(ones, y_ij, 1);
    }



    // y_j will get exactly one unit of flow
    for (j = 0; j < N; j++) {
        vector<string> y_ij;
        for (i = 0; i < N; i++) {
            SKIP_NON_EXISTING_ARCS(instance, i, j);

            snprintf(name, sizeof(name), "y_%u_%u", i, j);
            y_ij.push_back(name);
        }
        cplex.addEqConstraint(ones, y_ij, 1);
    }



    // Big-N constraint
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            SKIP_NON_EXISTING_ARCS(instance, i, j);

            vector<string> vars;
            vector<double> coeff;

            snprintf(name, sizeof(name), "x_%u_%u", i, j);
            vars.push_back(name);
            coeff.push_back(1.0);

            snprintf(name, sizeof(name), "y_%u_%u", i, j);
            vars.push_back(name);
            coeff.push_back(-static_cast<double>(N));

            cplex.addLeqConstraint(coeff, vars, 0);
        }
    }



    // Solves the problem
    cplex.solve();


    // If no solution exists, return an invalid solution
    if (!cplex.hasSolution()) {
        return Solution(nodes, instance);
    }


    // Saves problem and solution
    cplex.saveProblem("TSP.lp");
    cplex.saveSolution("TSP.sol");


    // Converts CPLEX solution from set of variables to sequence of nodes
    int current = 0;
    for (i = 0; i < N; i++) {
        solution.push_back(*projection[current]);
        j = 0;
        int next = 0;
        while (j < N) {
            snprintf(name, sizeof(name), "y_%u_%u", current, j);
            int value = round(cplex.getVariable(name));
            if (value == 1.0) {
                next = j;
                break;
            }
            j++;
        }
        current = next;
    }


    return Solution(solution, instance);
}

}  // namespace solver
