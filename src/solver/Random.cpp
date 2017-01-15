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
#include <time.h>

#include <vector>

#include "Random.h"

using std::vector;

namespace solver {

Random::~Random() {
}


Solution Random::solve(const Instance &instance) const {
    unsigned int size = instance.getSize();
    vector<Node> nodes = instance.getNodesAsVector();

    unsigned int seed = time(NULL);

    for (unsigned int i = 0; i < size; i++) {
        unsigned int newPosition = rand_r(&seed) % size;
        Node swapNode(nodes[i]);

        memcpy(&nodes[i], &nodes[newPosition], sizeof(Node));
        memcpy(&nodes[newPosition], &swapNode, sizeof(Node));
    }

    return Solution(nodes, instance);
}

}  // namespace solver
