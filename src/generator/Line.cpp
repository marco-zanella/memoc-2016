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

#include "Line.h"
#include "../RNG.h"

namespace generator {

Line::Line(const Perturbator &perturbator):
    perturbator(perturbator) {
}


Line::~Line() {
}


/**
 * The algorithm itselfs guarantees generated node to be on the panel: it is
 * never the case that a node is generated outside the panel.
 */
vector<Node>
Line::generate(const Panel panel, const size_t nHoles) const {
    const double max_x = panel.getWidth(),
                 max_y = panel.getHeight(),
                 m     = max_y / max_x;
    vector<Node> nodes;
    RNG rng;

    for (unsigned int i = 0; i < nHoles; i++) {
        const double x = rng.uniform(0.0, max_x),
                     y = m * x;
        nodes.push_back(Node(x, y));
    }

    return perturbator(nodes, panel);
}

}  // namespace generator
