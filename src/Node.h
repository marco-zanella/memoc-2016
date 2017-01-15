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
#ifndef NODE_H_
#define NODE_H_

#include <istream>
#include <ostream>

using std::istream;
using std::ostream;

/**
 * A node in the Traveling Salesman Problem graph.
 * Nodes represent holes in a panel.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Node {
 public:
    /**
     * Constructor.
     * @param[in] x X-coordinate
     * @param[in] y Y-coordinate
     */
    Node(const double x, const double y);


    /**
     * Assignment operator
     * @param[in] other Other node
     */
    Node operator=(const Node &other);


    /**
     * Returns identifier of this node.
     * @return Identifier of this node
     */
    unsigned int getId() const;

    /**
     * Returns X-coordinate of this node.
     * @return X-coordinate
     */
    double getX() const;

    /**
     * Returns Y-coordinate of this node.
     * @return Y-coordinate
     */
    double getY() const;


    /**
     * Saves this node as a string.
     * @param[out] stream Stream on which save this node
     * @return This node itself
     */
    Node &save(ostream *stream) const;


    /**
     * Loads a node from a string.
     * @param[in] stream Stream to read from
     * @return A node read from the stream
     */
    static Node load(istream *stream);


 private:
    static unsigned int last_id;
    unsigned int identifier;  ///< Identifier of this node
    const double x;           ///< X-coordinate of this node
    const double y;           ///< Y-coordinate of this node


    /**
     * Constructor.
     * @param[in] id Identifier of the node
     * @param[in] x  X-coordinate
     * @param[in] y  Y-coordinate
     */
    Node(const unsigned int id, const double x, const double y);
};

#endif  // NODE_H_
