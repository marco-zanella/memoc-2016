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
#ifndef COSTFUNCTION_MANHATTAN_H_
#define COSTFUNCTION_MANHATTAN_H_

#include "CostFunction.h"

namespace costFunction {

/**
 * Associates a Manhattan cost to an arc between two nodes.
 * Cost is computed as the Manhattan distance between two nodes.
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Manhattan: public CostFunction {
 public:
    /**
     * Destructor.
     */
    virtual ~Manhattan();


    /**
     * Returns cost of the arc between two nodes.
     * Cost is computed as the Manhattan distance between nodes.
     * @param[in] A First node
     * @param[in] B Second node
     * @return Cost of the arc between A and B
     */
    virtual double cost(const Node &A, const Node &B) const;
};

}  // namespace costFunction

#endif  // COSTFUNCTION_MANHATTAN_H_
