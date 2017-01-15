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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include "Stopwatch.h"
#include "Instance.h"
#include "Solution.h"
#include "solver/CPLEX.h"

using std::cin;
using std::cout;
using std::endl;


/**
 * Prints the helper.
 * @param[in] argc ARGument Counter
 * @param[in] argv ARGument Vector
 */
static void show_helper(int argc, char *argv[]) {
    (void) argc;
    cout << "RANDOM SOLVER\n"
         << "Solves and instance of the TSP problem by randomly choosing a "
         << "walk.\n"
         << "Instance is read form standard input, solution is written to "
         << "standard output.\n"
         << endl
         << "Usage:\n"
         << "  " << argv[0] << " -h" << endl
         << endl
         << "  -h    \t Prints this help and exits\n";
}



/**
 * Generates and solves instances.
 * @param[in] argc ARGument Counter
 * @param[in] argv ARGument Vector
 * @return EXIT_SUCCESS in case of success
 */
int main(int argc, char *argv[]) {
    int opt;

    /*******************************************************************
     * Command line options parsing.
     ******************************************************************/
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
        case 'h':
            show_helper(argc, argv);
            exit(EXIT_SUCCESS);

        default:  // '?'
            cout << "Unrecognized option. Run with -h to see the helper.\n";
            exit(EXIT_FAILURE);
        }
    }



    /*******************************************************************
     * Runs the solver.
     ******************************************************************/
    Stopwatch sw;
    Instance instance = Instance::load(&std::cin);
    solver::CPLEX solver;

    sw.start();
    Solution solution = solver(instance);
    sw.stop();

    solution.save(&std::cout);
    std::cout << "Cost: "      << solution.getCost()
              << " UserTime: " << sw.getUserTime()
              << " CPUTime: "  << sw.getCPUTime()
              << std::endl;


    return EXIT_SUCCESS;
}
