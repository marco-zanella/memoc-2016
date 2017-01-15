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

#include <cstddef>
#include <vector>
#include <map>

#include "Instance.h"

/**
 * Prints an error when malloc cannot allocate memory.
 */
#define MALLOC_ERROR \
  fprintf(stderr, "[%s: %d]: Cannot allocate memory.\n", __FILE__, __LINE__)


/**
 * Performs a memory allocation and checks for the result.
 */
#define SAFE_MALLOC(var, type, size)              \
    (var) = reinterpret_cast<type>(malloc(size)); \
    if (NULL == (var)) {                          \
        MALLOC_ERROR;                             \
    }



/**
 * Returns identifier with the lowest value in a list of nodes.
 * @param[in] nodes List of nodes
 * @return Lowest identifier
 */
unsigned int search_min_id(const vector<Node> &nodes) {
    if (nodes.size() == 0) {
        return 0;
    }

    unsigned int min_id = nodes[0].getId();

    for (unsigned int i = 1; i < nodes.size(); i++) {
        unsigned int id = nodes[i].getId();
        if (id < min_id) {
            min_id = id;
        }
    }

    return min_id;
}


/**
 * Returns identifier with the highest value in a list of nodes.
 * @param[in] nodes List of nodes
 * @return Highest identifier
 */
unsigned int search_max_id(const vector<Node> &nodes) {
    if (nodes.size() == 0) {
        return 0;
    }

    unsigned int max_id = nodes[0].getId();

    for (unsigned int i = 1; i < nodes.size(); i++) {
        unsigned int id = nodes[i].getId();
        if (id > max_id) {
            max_id = id;
        }
    }

    return max_id;
}



Instance::Instance(const vector<Node> &nodes, const CostFunction &cost) :
    size(nodes.size()), nodes(nodes),
    min_id(search_min_id(nodes)), max_id(search_max_id(nodes)) {
    map_size = max_id - min_id + 1;

    computeCostMatrix(cost);
}


/**
 * Cost matrix is implemented with direct memory management for performance
 * reasons.
 */
Instance::Instance(const Instance &other) :
    size(other.size), map_size(other.map_size),
    min_id(other.min_id), max_id(other.max_id) {
    // Copies nodes
    nodes = other.nodes;

    // Copies cost matrix
    SAFE_MALLOC(costs, double *, map_size * map_size * sizeof(double));
    memcpy(costs, other.costs, map_size * map_size * sizeof(double));
}


Instance::~Instance() {
    free(costs);

    costs = NULL;
}


bool
Instance::hasArc(const unsigned int A, const unsigned int B) const {
    return costs[(A - min_id) * map_size + (B - min_id)] >= 0;
}


size_t
Instance::getSize() const {
    return size;
}


Node &
Instance::getNode(const unsigned int identifier) const {
    return const_cast<Node &>(nodes[identifier - min_id]);
}


double
Instance::getCost(const unsigned int A, const unsigned int B) const {
    return costs[(A - min_id) * map_size + (B - min_id)];
}


vector<Node>
Instance::getNodesAsVector() const {
    return nodes;
}


Instance &
Instance::save(ostream *stream) const {
    *stream << size << " " << map_size << " "
            << min_id << " " << max_id << " "
            << std::endl;

    // Writes every node
    for (unsigned int i = 0; i < size; i++) {
        nodes[i].save(stream);
    }

    // Writes cost matrix, row major
    for (unsigned int i = 0; i < map_size; i++) {
        for (unsigned int j = 0; j < map_size; j++) {
            *stream << costs[i * map_size + j] << " ";
        }
        *stream << std::endl;
    }

    return const_cast<Instance &>(*this);
}


Instance
Instance::load(istream *stream) {
    size_t size, map_size;
    unsigned int min_id, max_id;
    vector<Node> nodes;
    double *costs;

    // Reads general data
    *stream >> size >> map_size >> min_id >> max_id;

    // Reads data about nodes
    for (unsigned int i = 0; i < size; i++) {
        nodes.push_back(Node::load(stream));
    }

    // Reads data about cost
    SAFE_MALLOC(costs, double *, map_size * map_size * sizeof(double));
    for (unsigned int i = 0; i < map_size; i++) {
        for (unsigned int j = 0; j < map_size; j++) {
            *stream >> costs[i * map_size + j];
        }
    }

    Instance instance(nodes, map_size, costs);
    free(costs);

    return instance;
}


Instance::Instance(
    const vector<Node> nodes,
    const size_t map_size,
    const double *costs) :
    size(nodes.size()), nodes(nodes), map_size(map_size),
    min_id(search_min_id(nodes)), max_id(search_max_id(nodes)) {
    SAFE_MALLOC(this->costs, double *, map_size * map_size * sizeof(double));
    memcpy(this->costs, costs, map_size * map_size * sizeof(double));
}


/**
 * Cost matrix is implemented with direct memory management for performance
 * reasons.
 */
void
Instance::computeCostMatrix(const CostFunction &cost) {
    SAFE_MALLOC(costs, double *, map_size * map_size * sizeof(double));
    for (size_t i = 0; i < size; i++) {
        const unsigned int id_i = nodes[i].getId() - min_id;
        for (size_t j = 0; j < size; j++) {
            const unsigned int id_j = nodes[j].getId() - min_id;
            costs[id_i * map_size + id_j] = cost(nodes[id_i], nodes[id_j]);
        }
    }
}
