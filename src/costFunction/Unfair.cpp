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
#include <cmath>

#include "Unfair.h"
#include "Minkowski.h"
#include "../RNG.h"

using std::abs;

namespace costFunction {

Unfair::Unfair(
        const double p,
        const double mi,
        const double sigma,
        const double t):
p(p), mi(mi), sigma(sigma), t(t) {
}


Unfair::~Unfair() {
}


double
Unfair::cost(const Node &A, const Node &B) const {
    if (A.getId() == B.getId()) {
        return 0.0;
    }

    Minkowski minkowski(p);
    RNG rng(A.getId() - B.getId());

    const double cost = abs(minkowski(A, B) + rng.normal(mi, sigma));
    return (cost <= t) ? cost : CostFunction::infinite;
}

}  // namespace costFunction
