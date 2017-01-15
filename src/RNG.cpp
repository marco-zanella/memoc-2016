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
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "RNG.h"

RNG::RNG() {
    seed = time(NULL) + getpid();
}



RNG::RNG(const unsigned int seed) {
    this->seed = seed;
}


double
RNG::uniform(const double min, const double max) {
    const double base  = static_cast<double>(rand_r(&seed)) / RAND_MAX,
                 delta = max - min;
    return min + base * delta;
}


double
RNG::normal(const double mi, const double sigma) {
    double U1, U2, W, X;

    do {
        U1 = -1 + (static_cast<double>(rand_r(&seed)) / RAND_MAX) * 2;
        U2 = -1 + (static_cast<double>(rand_r(&seed)) / RAND_MAX) * 2;
        W  = pow(U1, 2) + pow(U2, 2);
    } while (W >= 1 || W == 0);

    X = U1 * sqrt((-2.0 * log(W)) / W);

    return mi + sigma * X;
}
