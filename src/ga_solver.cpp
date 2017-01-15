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
#include "solver/AGLSA.h"
#include "solver/Population.h"

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
         << "Solves and instance of the TSP problem by applying a genetic "
         << "algorithm with a local search and adaptive parameters.\n"
         << "Instance is read form standard input, solution is written to "
         << "standard output.\n"
         << endl
         << "Usage:\n"
         << "  " << argv[0] << " -c <double> -m <double> -t <double> "
         << "-p <double> -h" << endl
         << endl
         << "Options:\n"
         << "  -c <double> \t Maximum probability of crossover (default: 0.8)\n"
         << "  -m <double> \t Maximum probability of mutation (default: 0.3)\n"
         << "  -t <double> \t Relative distance under which two chromosomes\n"
         << "              \t are considered similar (default: 0.1)\n"
         << "  -p <double> \t Probability to accept a chromosome when there\n"
         << "              \t is already a similar one (default: 0.5)\n"
         << "  -i <double> \t Probability of improving a good chromosome\n"
         << "              \t (default: 0.2)\n"
         << "  -T <double> \t Maximum execution time, in secs (default 5.0)\n"
         << "  -M <int>    \t Maximum number of iterations (default: 10000)\n"
         << "  -K <int>    \t Maximum number of consecutive iterations\n"
         << "              \t without improvevement (default: 1000)\n"
         << "  -S <int>    \t Maximum size of the population (default: 30)\n"
         << "  -h          \t Prints this help and exits\n";
}



/**
 * Generates and solves instances.
 * @param[in] argc ARGument Counter
 * @param[in] argv ARGument Vector
 * @return EXIT_SUCCESS in case of success
 */
int main(int argc, char *argv[]) {
    int opt;
    double p_crossover     = 0.8,
           p_mutation      = 0.3,
           d_threshold     = 0.1,
           p_accept        = 0.5,
           p_improvement   = 0.2,
           max_time        = 5.0;
    unsigned int max_iter  = 10000,
                 max_slack = 1000,
                 max_size  = 30;

    /*******************************************************************
     * Command line options parsing.
     ******************************************************************/
    while ((opt = getopt(argc, argv, "c:m:t:p:i:T:M:K:S:h")) != -1) {
        switch (opt) {
        case 'c': p_crossover   = atof(optarg); break;
        case 'm': p_mutation    = atof(optarg); break;
        case 't': d_threshold   = atof(optarg); break;
        case 'p': p_accept      = atof(optarg); break;
        case 'i': p_improvement = atof(optarg); break;
        case 'T': max_time      = atof(optarg); break;
        case 'M': max_iter      = atoi(optarg); break;
        case 'K': max_slack     = atoi(optarg); break;
        case 'S': max_size      = atoi(optarg); break;
        case 'h':
            show_helper(argc, argv);
            exit(EXIT_SUCCESS);

        default:  // '?'
            cout << "Unrecognized option. Run with -h to see the helper.\n";
            exit(EXIT_FAILURE);
        }
    }

    solver::GAConf config;
    config.max_p_crossover = p_crossover;
    config.max_p_mutation  = p_mutation;
    config.threshold       = d_threshold;
    config.P               = p_accept;
    config.p_improvement   = p_improvement;



    /*******************************************************************
     * Runs the solver.
     ******************************************************************/
    Stopwatch sw;
    Instance instance = Instance::load(&std::cin);
    solver::AGLSA solver(config, max_time, max_iter, max_slack, max_size);

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
