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

#include <vector>

#include "Uniform.h"
#include "../RNG.h"

namespace generator {

Uniform::Uniform(const Perturbator &perturbator):
    perturbator(perturbator) {
}


Uniform::~Uniform() {
}


vector<Node>
Uniform::generate(const Panel panel, const size_t nHoles) const {
    const double max_x = panel.getWidth(),
                 max_y = panel.getHeight();
    vector<Node> nodes;
    nodes.reserve(nHoles);
    RNG rng;

    for (size_t i = 0; i < nHoles; i++) {
        Node new_node(rng.uniform(0.0, max_x), rng.uniform(0.0, max_y));
        nodes.push_back(new_node);
    }

    return perturbator(nodes, panel);
}

}  // namespace generator
