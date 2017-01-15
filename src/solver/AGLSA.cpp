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
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <iostream>
#include <vector>
#include <map>

#include "AGLSA.h"
#include "Chromosome.h"
#include "Population.h"
#include "../Stopwatch.h"
#include "../RNG.h"
#include "Greedy.h"
#include "Random.h"


/**
 * Prints an error when malloc cannot allocate memory.
 */
#define MALLOC_ERROR \
  fprintf(stderr, "[%s: %d]: Cannot allocate memory.\n", __FILE__, __LINE__)


/**
 * Performs a memory allocation and checks for the result.
 */
#define SAFE_MALLOC(var, type, size)              \
    (var) = reinterpret_cast<type>(malloc(size)); \
    if (NULL == (var)) {                          \
        MALLOC_ERROR;                             \
    }

using std::map;

static RNG rng;  ///< Random Number Generator


////////////////////////////////////////////////////////////////////////
// Non member support functions

/**
 * Encode a solution into a chromosome.
 * @param[out] chromosome Chromosome encoding the solution
 * @param[in]  solution   Solution to encode
 * @param[in]  nodes      Array of pointers to nodes
 * @param[in]  costs      Cost matrix
 */
static void chromosome_encode(
    solver::Chromosome *chromosome,
    vector<Node> solution,
    Node **nodes,
    double *costs) {
    unsigned int N = solution.size();

    map<unsigned int, unsigned int> lookup;
    for (unsigned int i = 0; i < N; i++) {
        lookup[nodes[i]->getId()] = i;
    }

    for (unsigned int i = 0; i < N; i++) {
        chromosome->genes[i] = lookup[solution[i].getId()];
    }

    chromosome_evaluate(chromosome, costs);
}


/**
 * Decodes a chromosome.
 * @param[in] chromosome Chromosome to decode
 * @param[in] nodes      Array of pointers to nodes
 * @return Solution encoded by the chromosome
 */
static vector<Node> chromosome_decode(
    solver::Chromosome *chromosome,
    Node **nodes
) {
    vector<Node> solution;
    for (unsigned int i = 0; i < chromosome->size; i++) {
        solution.push_back(*nodes[chromosome->genes[i]]);
    }

    return solution;
}


/**
 * Generates the initial population.
 * @param[out] population Pointer to population
 * @param[in]  size       Size of the population
 * @param[in]  instance   Original instance
 * @param[in]  nodes      Array of pointers to nodes
 * @param[in]  costs      Cost matrix
 */
static void generate_initial_population(
    solver::Population *population,
    const unsigned int size,
    const Instance &instance,
    Node **nodes,
    double *costs) {
    for (unsigned int i = 0; i < size; i++) {
        solver::Chromosome *c = population->chromosomes;
        solver::Solver *solver;

        if (rng.uniform(0.0, 1.0) < 0.5) {
            solver = new solver::Greedy();
        } else {
            solver = new solver::Random();
        }

        Solution s = (*solver)(instance);
        chromosome_encode(c + i, s.getNodesAsVector(), nodes, costs);
        delete solver;
    }
    population->size = size;
    population_variance(population);
}
////////////////////////////////////////////////////////////////////////
// End of non member support functions



namespace solver {

AGLSA::AGLSA(
    const GAConf configuration,
    const double maxTime,
    const unsigned int maxIter,
    const unsigned int maxSlack,
    const unsigned int maxSize) :
configuration(configuration),
maxTime(maxTime), maxIter(maxIter), maxSlack(maxSlack), maxSize(maxSize) {
}



AGLSA::~AGLSA() {
}



/**
 * Uses direct memory management for performance reasons.
 */
Solution AGLSA::solve(const Instance &instance) const {
    const unsigned int N = instance.getSize();
    vector<Node> instance_nodes(instance.getNodesAsVector());
    Node **nodes;
    double *costs;


    // Pre-computes array of pointers to nodes
    SAFE_MALLOC(nodes, Node **, N * sizeof(Node *));
    for (unsigned int i = 0; i < N; i++) {
       nodes[i] = &instance_nodes[i];
    }


    // Pre-computes cost matrix
    SAFE_MALLOC(costs, double *, N * N * sizeof(double));
    for (unsigned int i = 0; i < N; i++) {
        const unsigned int node_i = nodes[i]->getId();
        for (unsigned int j = 0; j < N; j++) {
            const unsigned int node_j = nodes[j]->getId();
            costs[i * N + j] = instance.getCost(node_i, node_j);
        }
    }


    // Reserves space for current and next generations (maxSize is assumed)
    Population population, next;
    population_create(&population, maxSize, N, costs);
    population_create(&next, maxSize, N, costs);


    // Reserves space for best and local best chromosomes
    Chromosome best, local_best;
    chromosome_create(&best, N);
    chromosome_create(&local_best, N);



    Stopwatch sw;
    double time = 0.0;
    unsigned int iter = 0, slack = 0;

    sw.start();


    // Generates initial population
    generate_initial_population(&population, maxSize, instance, nodes, costs);

    population_best(&population, &best);


    // Generations loop
    while (time < maxTime && iter < maxIter && slack < maxSlack) {
        // Builds next generation
        population_next_generation(&population, &next, &configuration);

        // Updates best chromosome found so far
        population_best(&population, &local_best);
        if (local_best.fitness > best.fitness) {
            chromosome_copy(&best, &local_best);
            slack = 0;
        }

        // Updates counters
        time = sw.stop().getUserTime();
        iter++;
        slack++;
    }



    // Builds solution as vector of nodes
    vector<Node> solution(chromosome_decode(&best, nodes));


    // Releases array of pointers to nodes and cost matrix
    free(nodes);
    free(costs);

    // Releases chromosomes and populations
    chromosome_delete(&best);
    chromosome_delete(&local_best);
    population_delete(&population);
    population_delete(&next);

    return Solution(solution, instance);
}

}  // namespace solver
