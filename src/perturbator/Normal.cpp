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
#include <stdlib.h>

#include <vector>

#include "Normal.h"
#include "../RNG.h"

namespace perturbator {

/**
 * Ensures given value to be in [min, max].
 * @param[in, out] value Value to check and modify
 * @param[in]      min   Minimum allowed value
 * @param[in]      max   Maximum allowed value
 */
static void check_limits(double *value, const double min, const double max) {
    if (*value < min) {
        *value = min;
    } else if (*value > max) {
        *value = max;
    }
}


Normal::Normal(const double mi, const double sigma):
    mi(mi), sigma(sigma) {
}


Normal::~Normal() {
}


vector<Node>
Normal::perturbate(
    const vector<Node> &nodes,
    const Panel &panel) const {
    vector<Node> newNodes;
    RNG rng;

    for (unsigned int i = 0; i < nodes.size(); i++) {
        double x = nodes[i].getX() + rng.normal(mi, sigma),
               y = nodes[i].getY() + rng.normal(mi, sigma);

        check_limits(&x, 0.0, panel.getWidth());
        check_limits(&y, 0.0, panel.getHeight());
        newNodes.push_back(Node(x, y));
    }

    return newNodes;
}

}  // namespace perturbator
