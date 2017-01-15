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
#include <cfloat>
#include <vector>

#include "Greedy.h"

using std::vector;

namespace solver {

/**
 * Searches closest node in a list of candidates.
 * Returns index of such node.
 * @param[in] node       Current node
 * @param[in] instance   Instance to solve
 * @param[in] candidates List of candidates to look in
 * @return Index of the closest node
 */
static unsigned int search_closest(
    const Node *node,
    const Instance &instance,
    const vector<Node *> &candidates) {
    double minCost = DBL_MAX;
    unsigned int id = node->getId(),
                 idx = 0;
    for (unsigned int i = 0; i < candidates.size(); i++) {
        const double cost = instance.getCost(id, candidates[i]->getId());
        if (cost < minCost && cost > 0.0) {
            minCost = cost;
            idx     = i;
        }
    }

    return idx;
}


Greedy::~Greedy() {
}


Solution Greedy::solve(const Instance &instance) const {
    vector<Node *> candidates;
    vector<Node> solution,
                 nodes(instance.getNodesAsVector());

    // Initializes vector of candidates
    for (unsigned int i = 0; i < nodes.size(); i++) {
        candidates.push_back(&nodes[i]);
    }

    Node *current = candidates[0];
    solution.push_back(*current);
    candidates.erase(candidates.begin());
    while (candidates.size() > 0) {
        // Selects nearest node
        unsigned int minIdx = search_closest(current, instance, candidates);
        current = candidates[minIdx];

        // Pushes nearest node into solution and removes it from candidates
        solution.push_back(*current);
        candidates.erase(candidates.begin() + minIdx);
    }

    return Solution(solution, instance);
}

}  // namespace solver
