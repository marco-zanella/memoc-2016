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
#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <vector>
#include <ostream>

#include "Instance.h"
#include "Node.h"

using std::vector;
using std::ostream;

/**
 * A solution of the problem.
 * For convenience reasons, solution mantains data about the instance of which
 * it is a solution.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Solution {
 public:
    /**
     * Constructor.
     */
    Solution(const vector<Node> &nodes, const Instance &instance);


    /**
     * Destructor.
     */
    ~Solution();


    /**
     * Returns cost of this solution.
     * @return Cost fo this solution
     */
    double getCost() const;


    /**
     * Returns nodes in this solution.
     * @return Nodes in this solution, as vector
     */
    vector<Node> &getNodesAsVector() const;


    /**
     * Saves this solution as a string.
     * @param[out] stream Stream on which save this solution
     * @return This solution itself
     */
    Solution &save(ostream *stream) const;


    /**
     * Prints a string representation of this solution.
     * Prints on standard output. Mainly for debug purposes.
     * @return This solution itself
     */
    Solution &quickPrint() const;


 private:
    vector<Node> nodes;        ///< Sequence of nodes
    const Instance &instance;  ///< Instance this solution was derived from
    const double cost;         ///< Cost of this solution


    /**
     * Computes cost of a solution.
     * @param[in] nodes    Nodes in the solution
     * @param[in] instance Instance the solution originates from
     * @return Cost of the solution
     */
    static double
    computeCost(const vector<Node> &nodes, const Instance &instance);
};

#endif  // SOLUTION_H_
