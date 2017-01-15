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
#include <fstream>
#include <vector>

#include "Panel.h"
#include "perturbator/Normal.h"
#include "generator/Uniform.h"
#include "costFunction/Unfair.h"
#include "Instance.h"

using std::cout;
using std::endl;


/**
 * Prints the helper.
 * @param[in] argc ARGument Counter
 * @param[in] argv ARGument Vector
 */
static void show_helper(int argc, char *argv[]) {
    (void) argc;
    cout << "INSTANCE GENERATOR\n"
         << "Use this tool to generate an instance of a TSP problem.\n"
         << "Instance is printed to standard output.\n"
         << "This generator uses a function to generate nodes and distances "
         << "trying to complicate the problem: distance matrix is not "
         << "symmetric, graph is not connected, triangular inequality is "
         << "not satisfied.\n"
         << "Every parameter is optional. Default values are tuned to produce "
         << "a reasonable instance for the purpose of my examination.\n"
         << endl
         << "Usage:\n"
         << "  " << argv[0] << " -N <int> -X <num> -Y <num> "
         << "-M <num> -S <num> "
         << "-p <num> -m <num> -s <num> -t <num> -h\n"
         << endl
         << "Options:\n"
         << "  -N <int> \t Number of nodes in the instance (default: 10)\n"
         << "  -x <num> \t Width of the panel (default: 200.0)\n"
         << "  -y <num> \t Height of the panel (default: 100.0)\n"
         << "  -M <num> \t Mean of the perturbation\n"
         << "  -S <num> \t Variance of the perturbation\n"
         << "  -p <num> \t Minkowski P-parameter (default: 1.0)\n"
         << "  -m <num> \t Mean of the random parameter in cost function\n"
         << "  -s <num> \t Variance of the random parameter in cost function\n"
         << "  -t <num> \t Threshold over which an arc is removed\n"
         << "  -h       \t Prints this help and exit\n";
}



/**
 * Generates an instance.
 * @param[in] argc ARGument Counter
 * @param[in] argv ARGument Vector
 * @return EXIT_SUCCESS in case of success
 */
int main(int argc, char *argv[]) {
    int opt;

    /*******************************************************************
     * Default values for paramters.
     ******************************************************************/
    unsigned int N = 10;
    double X       = 200.0,
           Y       = 100.0,
           pMi     = 0.0,
           pSigma  = 1.0,
           cP      = 1.0,
           cMi     = 0.0,
           cSigma  = 5.0,
           cT      = 200.0;


    /*******************************************************************
     * Command line options parsing.
     ******************************************************************/
    while ((opt = getopt(argc, argv, "N:x:y:M:S::p:m:s:t:h")) != -1) {
        switch (opt) {
        case 'N': N      = atoi(optarg); break;
        case 'x': X      = atof(optarg); break;
        case 'y': Y      = atof(optarg); break;
        case 'M': pMi    = atof(optarg); break;
        case 'S': pSigma = atof(optarg); break;
        case 'p': cP     = atof(optarg); break;
        case 'm': cMi    = atof(optarg); break;
        case 's': cSigma = atof(optarg); break;
        case 't': cT     = atof(optarg); break;
        case 'h':
            show_helper(argc, argv);
            exit(EXIT_SUCCESS);
            break;
        default:
            cout << "Unrecognized option. Run with -h to see the helper.\n";
            exit(EXIT_FAILURE);
        }
    }


    /*******************************************************************
     * Runs generator or solver.
     ******************************************************************/
    Panel panel(X, Y);
    perturbator::Normal perturbator(pMi, pSigma);
    generator::Uniform generator(perturbator);
    costFunction::Unfair cost_function(cP, cMi, cSigma, cT);
    Instance instance(generator(panel, N), cost_function);

    instance.save(&std::cout);

    return EXIT_SUCCESS;
}
