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
#ifndef SOLVER_SOLVER_H_
#define SOLVER_SOLVER_H_

#include "../Instance.h"
#include "../Solution.h"

namespace solver {

/**
 * Solves an instance of the problem.
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Solver {
 public:
    /**
     * Destructor.
     */
    virtual ~Solver();


    /**
     * Solves an instance of problem.
     * @param[in] instance Instance to solve
     * @return Solution for that instance
     */
    Solution operator()(const Instance &instance) const;


    /**
     * Solves an instance of problem.
     * @param[in] instance Instance to solve
     * @return Solution for that instance
     */
    virtual Solution solve(const Instance &instance) const = 0;
};

}  // namespace solver

#endif  // SOLVER_SOLVER_H_
