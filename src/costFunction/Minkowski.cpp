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
#include <math.h>

#include <cmath>

#include "Minkowski.h"

namespace costFunction {

using std::abs;

Minkowski::Minkowski(const double p):
    p(p) {
}


Minkowski::~Minkowski() {
}


double
Minkowski::cost(const Node &A, const Node &B) const {
    const double D_x = abs(A.getX() - B.getX()),
                 D_y = abs(A.getY() - B.getY()),
                 sum = pow(D_x, p) + pow(D_y, p);
    return pow(sum, 1.0 / p);
}

}  // namespace costFunction
