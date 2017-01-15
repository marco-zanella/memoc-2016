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
#ifndef COSTFUNCTION_MINKOWSKI_H_
#define COSTFUNCTION_MINKOWSKI_H_

#include "CostFunction.h"

namespace costFunction {

/**
 * Associates a Minkowski cost to an arc between two nodes.
 * Cost is computed as the Minkowski distance between two nodes.
 * Minkowski distance is defined using a parameter in Reals. When
 * such parameter is >= 1, distance is a metric. In particular, when its
 * value is 1 the Minkowski distance is the Manhattan distance, when its
 * value is 2 this distance is the Euclidean distance.
 * If you whish to use Manhattan or Euclidean distance, please use the
 * dedicated classes (for performance reasons).
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Minkowski: public CostFunction {
 public:
    /**
     * Constructor.
     * Set the value of the paramter p.
     * @param[in] p P-parameter of Minkowski distance
     */
    explicit Minkowski(const double p);


    /**
     * Destructor.
     */
    virtual ~Minkowski();


    /**
     * Returns cost of the arc between two nodes.
     * Cost is computed as the Minkowski distance between nodes.
     * @param[in] A First node
     * @param[in] B Second node
     * @return Cost of the arc between nodes A and B
     */
    virtual double cost(const Node &A, const Node &B) const;


 private:
    const double p;  ///< P-parameter of the Minkowski distance
};

}  // namespace costFunction

#endif  // COSTFUNCTION_MINKOWSKI_H_
