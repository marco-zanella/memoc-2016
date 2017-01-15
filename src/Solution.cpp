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

#include <vector>

#include "Solution.h"

Solution::Solution(const vector<Node> &nodes, const Instance &instance) :
    nodes(nodes), instance(instance), cost(computeCost(nodes, instance)) {
}


Solution::~Solution() {
}


double
Solution::getCost() const {
    return cost;
}


vector<Node> &
Solution::getNodesAsVector() const {
    return const_cast< vector<Node> &>(nodes);
}


Solution &
Solution::save(ostream *stream) const {
    if (cost < 0.0) {
        *stream << 0 << " " << cost << std::endl;
        return const_cast<Solution &>(*this);
    }

    *stream << nodes.size() << " "
            << cost
            << std::endl;
    for (unsigned int i = 0; i < nodes.size(); i++) {
        nodes[i].save(stream);
    }

    return const_cast<Solution &>(*this);
}


Solution &
Solution::quickPrint() const {
    double totalCost = 0.0;

    for (unsigned int i = 0; i < nodes.size(); i++) {
        const Node current = nodes[i],
                   next    = nodes[(i + 1) % nodes.size()];
        const double cost = instance.getCost(current.getId(), next.getId());
        totalCost += cost;

        printf(
            "(%5.2f, %5.2f) ---> (%5.2f, %5.2f): %8.4f (total: %8.4f)\n",
            current.getX(), current.getY(), next.getX(), next.getY(),
            cost, totalCost);
    }

    return *const_cast<Solution *>(this);
}


double
Solution::computeCost(const vector<Node> &nodes, const Instance &instance) {
    double cost = 0.0;

    for (unsigned int i = 0; i < nodes.size(); i++) {
        const unsigned int current = nodes[i].getId(),
                           next    = nodes[(i + 1) % nodes.size()].getId();
        const double step_cost = instance.getCost(current, next);
        cost += step_cost;

        if (step_cost < 0.0) {
            return -1.0;
        }
    }

    return cost;
}
