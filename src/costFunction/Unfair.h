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
#ifndef COSTFUNCTION_UNFAIR_H_
#define COSTFUNCTION_UNFAIR_H_

#include "CostFunction.h"

namespace costFunction {

/**
 * A generalization of the Minkowski cost function.
 * The Minkowski function is modified so that the cost matrix is no
 * longer symmetric and graph is no longer connected.
 * These modifications make the problem harder (and, in some case,
 * impossible) for the solvers.
 *
 * In order to make cost matrix no longer symmetric, a random component
 * is added to each computed distance (normal distribution is used).
 * 
 * In order to make the graph no longer connected, arcs longer than a
 * given threshold are removed.
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Unfair: public CostFunction {
 public:
    /**
     * Constructor.
     * @param[in] p     P-parameter of the Minkowski distance
     * @param[in] mi    Mean of the random component
     * @param[in] sigma Variance of the random component
     * @param[in] t     Threshold above which an arc is removed
     */
    Unfair(
        const double p,
        const double mi,
        const double sigma,
        const double t);


    /**
     * Destructor.
     */
    virtual ~Unfair();


    /**
     * Returns cost of the arc between two nodes.
     * Cost is computed as the Minkowski distance between nodes plus a
     * randomized component. Arcs longer than the threshold are removed
     * (their distance is infinity).
     * @param[in] A First node
     * @param[in] B Second node
     * @return Cost of the arc between nodes A and B
     */
    virtual double cost(const Node &A, const Node &B) const;


 private:
    const double p;      ///< Minkowski P-parameter
    const double mi;     ///< Mean of normal distribution
    const double sigma;  ///< Variance of normal distribution
    const double t;      ///< Threshold above which an arc is removed
};

}  // namespace costFunction

#endif  // COSTFUNCTION_UNFAIR_H_
