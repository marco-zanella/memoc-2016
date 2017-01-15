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
#ifndef SOLVER_AGLSA_H_
#define SOLVER_AGLSA_H_

#include "Solver.h"
#include "Population.h"

namespace solver {

/**
 * Solves an instance of the problem using a Genetic Algorithm.
 * Generates solution using an Adaptive Genetic Local Search Algorithm.
 * It is adaptive because probabilities of crossover and mutation, as
 * well as size of the population at each generation, are decided
 * observing the state of the current population.
 * This class uses a Genetic Local Search Algorithm (also known as Memetic
 * Algorithm, or Baldwinian Evolutionary Algorithm, or Lamarckian Evolutionary
 * Algorithm, or Cultural Algorithm) to evolve the population.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class AGLSA: public Solver {
 public:
    /**
     * Constructor.
     * @param[in] configuration Pointer to configuration of the genetic algorithm
     * @param[in] maxTime  Maximum accpted execution time (in seconds)
     * @param[in] maxIter  Maximum number of accepted iterations
     * @param[in] maxSlack Maximum number of iterations without improvement
     * @param[in] maxSize  Maximum accepted population size
     */
    explicit AGLSA(
        const GAConf configuration,
        const double maxTime = 5.0,
        const unsigned int maxIter = 10000,
        const unsigned int maxSlack = 1000,
        const unsigned int maxSize = 30);


    /**
     * Destructor.
     */
    virtual ~AGLSA();


    /**
     * Solves an instance of problem.
     * Solution is build using a AGLSA.
     * @param[in] instance Instance to solve
     * @return Solution for that instance
     */
    virtual Solution solve(const Instance &instance) const;



 private:
    const GAConf configuration;   ///< Configuration for the genetic algorithm
    const double maxTime;         ///< Maximum execution time
    const unsigned int maxIter;   ///< Maximum number of iterations
    const unsigned int maxSlack;  ///< Maximum turns without improvement
    const unsigned int maxSize;   ///< Maximum population size
};

}  // namespace solver

#endif  // SOLVER_AGLSA_H_
