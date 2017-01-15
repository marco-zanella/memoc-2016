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
#ifndef PERTURBATOR_UNIFORM_H_
#define PERTURBATOR_UNIFORM_H_

#include <vector>

#include "Perturbator.h"

namespace perturbator {

/**
 * Applies an uniform perturbation on a list of nodes.
 * An uniform perturbation alters each dimension of a node up to a given
 * magnitude.
 * 
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Uniform: public Perturbator {
 public:
    /**
     * Constructor.
     * @param[in] magnitude Magnitude of the perturbation
     */
    explicit Uniform(const double magnitude);


    /**
     * Destructor.
     */
    virtual ~Uniform();


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
    const double magnitude;  ///< Magnitude of the perturbator
};

}  // namespace perturbator

#endif  // PERTURBATOR_UNIFORM_H_
