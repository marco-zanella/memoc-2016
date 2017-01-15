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
#ifndef GENERATOR_SUPERELLIPSE_H_
#define GENERATOR_SUPERELLIPSE_H_

#include <cstddef>
#include <vector>

#include "Generator.h"
#include "../perturbator/Perturbator.h"

using perturbator::Perturbator;

namespace generator {

/**
 * Generates a list of nodes.
 * Nodes are generated forming a superellipse, also known as Lame' curve.
 * The superellipse is the set of all points (x, y) with:
 * (x / A)^m + (x / B)^n = 1.
 * When m = n = 2, the superellipse is a regular ellipse.
 * Nodes are guaranteed to be generated inside given panel.
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class SuperEllipse: public Generator {
 public:
    /**
     * Constructor.
     * @param[in] perturbator Perturbator to use
     * @param[in] m           Horizontal exponent
     * @param[in] n           Vertical exponent
     */
    SuperEllipse(
        const Perturbator &perturbator,
        const double m = 2.0,
        const double n = 2.0);


    /**
     * Destructor.
     */
    virtual ~SuperEllipse();


    /**
     * Generates a list of points on a panel.
     * Points are placed along a superellipse in the panel.
     * @param[in] panel  Panel on which generate nodes
     * @param[in] nHoles Number of nodes to generate
     * @return A list of nodes on given panel
     */
    virtual vector<Node>
    generate(const Panel panel, const size_t nHoles) const;


 private:
    const Perturbator &perturbator;  ///< Perturbator to use
    const double m;                  ///< Horizontal exponent
    const double n;                  ///< Vertictal exponent
};

}  // namespace generator

#endif  // GENERATOR_SUPERELLIPSE_H_
