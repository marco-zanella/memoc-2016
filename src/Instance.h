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
#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <cstddef>
#include <vector>
#include <istream>
#include <ostream>

#include "Node.h"
#include "costFunction/CostFunction.h"

using std::vector;
using std::istream;
using std::ostream;
using costFunction::CostFunction;

/**
 * An instance of the problem to solve.
 * Istances have a list of nodes and a matrix of costs among them.
 * Since no assumption is made on the cost of the arcs, matrix is
 * complete.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Instance {
 public:
    /**
     * Constructor.
     * @param[in] nodes Nodes in the instance
     * @param[in] cost  Function telling costs among nodes
     */
    Instance(const vector<Node> &nodes, const CostFunction &cost);


    /**
     * Copy constructor.
     * @param[in] other Instance to copy from
     */
    Instance(const Instance &other);


    /**
     * Destructor.
     */
    ~Instance();


    /**
     * Tells whether there exists an arc between given nodes.
     * @param[in] A Identifier of first node
     * @param[in] B Identifier of second node
     */
    bool hasArc(const unsigned int A, const unsigned int B) const;


    /**
     * Returns size of this instance.
     * @return Size of this instance
     */
    size_t getSize() const;

    /**
     * Returns node with given identifier.
     * @param[in] identifier Identifier of a node
     * @return Node with given identifier
     */
    Node &getNode(const unsigned int identifier) const;

    /**
     * Returns cost between nodes with given identifiers.
     * @param[in] A Identifier of first node
     * @param[in] B Identifier of second node
     * @return Cost of the arc between A and B
     */
    double getCost(const unsigned int A, const unsigned int B) const;

    /**
     * Returns the list of nodes as a vector.
     * @return Nodes as a vector
     */
    vector<Node> getNodesAsVector() const;


    /**
     * Saves this instance as a string.
     * @param[out] stream Stream on which save this instance
     * @return This instance itself
     */
    Instance &save(ostream *stream) const;


    /**
     * Loads an instance from a string.
     * @param[in] stream Stream to read from
     * @return An instance read from the stream
     */
    static Instance load(istream *stream);


 private:
    const size_t size;      ///< Number of nodes in this instance
    vector<Node> nodes;     ///< Nodes in this instance
    size_t map_size;        ///< Size of the nodes map
    const unsigned min_id;  ///< Minimum identifier
    const unsigned max_id;  ///< Maximum identifier
    double* costs;          ///< Cost matrix


    /**
     * Constructs an instance with given nodes and costs.
     * @param[in] nodes    Nodes in the instance
     * @param[in] map_size Size of the internal map structure
     * @param[in] costs    Cost matrix
     */
    Instance(
        const vector<Node> nodes,
        const size_t map_size,
        const double *costs);


    /**
     * Builds cost matrix using given cost function.
     * @param[in] cost Cost function to use
     */
    void computeCostMatrix(const CostFunction &cost);
};

#endif  // INSTANCE_H_
