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
#ifndef PERTURBATOR_NORMAL_H_
#define PERTURBATOR_NORMAL_H_

#include <vector>

#include "Perturbator.h"

namespace perturbator {

/**
 * Applies a normal perturbation on a list of nodes.
 * A normal perturbation alters each dimension of node adding a random
 * number obtained from a normal distribution.
 * 
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Normal: public Perturbator {
 public:
    /**
     * Constructor.
     * @param[in] mi    Mean of the normal distribution
     * @param[in] sigma Variance of the normal distribution
     */
    Normal(const double mi, const double sigma);


    /**
     * Destructor.
     */
    virtual ~Normal();


    /**
     * Perturbates a list of points on a panel.
     * Points coordinates are perturbated, altering their coordinates
     * up to a given magnitude (in each dimension).
     * @param[in] nodes  Points to perturbate
     * @param[in] panel  Panel on which operate
     * @return A new list of perturbated points
     */
    virtual vector<Node> perturbate(
        const vector<Node> &nodes,
        const Panel &panel) const;


 private:
    const double mi;     ///< Meam of this distribution
    const double sigma;  ///< Variance of this distribution
};

}  // namespace perturbator

#endif  // PERTURBATOR_NORMAL_H_
