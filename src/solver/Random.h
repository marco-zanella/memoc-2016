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
#ifndef SOLVER_RANDOM_H_
#define SOLVER_RANDOM_H_

#include "Solver.h"

namespace solver {

/**
 * Solves an instance of the problem.
 * Solution is generated randomly shuffling nodes in the problem and
 * considering the resulting list as the order.
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Random: public Solver {
 public:
    /**
     * Destructor.
     */
    virtual ~Random();


    /**
     * Solves an instance of problem.
     * Randomly shuffles nodes in the problem.
     * @param[in] instance Instance to solve
     * @return Solution for that instance
     */
    virtual Solution solve(const Instance &instance) const;
};

}  // namespace solver

#endif  // SOLVER_RANDOM_H_
