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
#ifndef SOLVER_CPLEX_H_
#define SOLVER_CPLEX_H_

#include "Solver.h"
#include "CPLEXManager.h"

namespace solver {

/**
 * Solves an instance of the problem using CPLEX.
 * Finds an exact solution using CPLEX.
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class CPLEX: public Solver {
 public:
    /**
     * Destructor.
     */
    virtual ~CPLEX();


    /**
     * Solves an instance of problem.
     * Solution is build using CPLEX.
     * @param[in] instance Instance to solve
     * @return Solution of that instance
     */
    virtual Solution solve(const Instance &instance) const;
};

}  // namespace solver

#endif  // SOLVER_CPLEX_H_
