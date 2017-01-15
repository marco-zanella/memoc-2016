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
#ifndef COSTFUNCTION_COSTFUNCTION_H_
#define COSTFUNCTION_COSTFUNCTION_H_

#include <cfloat>

#include "../Node.h"

namespace costFunction {

/**
 * Associates a cost to an arc between two nodes.
 * No assumption is made on the costs of arcs. DBL_MAX is used to
 * represent infinite distance (equivalently, the absence of the arc).
 * It is assumed that, given two nodes, every direct path between them
 * share the same cost.
 * Subclasses must implement the pure virtual member function "cost"
 * following the desired criterion.
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class CostFunction {
 public:
    /**
     * Destructor.
     */
    virtual ~CostFunction();


    /**
     * Returns cost of the arc between two nodes.
     * @param[in] A First node
     * @param[in] B Second node
     * @return Cost of the arc between nodes A and B
     */
    double operator()(const Node &A, const Node &B) const;


    /**
     * Returns cost of the arc between two nodes.
     * @param[in] A First node
     * @param[in] B Second node
     * @return Cost of the arc between nodes A and B
     */
    virtual double cost(const Node &A, const Node &B) const = 0;


    static const double infinite;  ///< Infinite distance
};

}  // namespace costFunction

#endif  // COSTFUNCTION_COSTFUNCTION_H_
