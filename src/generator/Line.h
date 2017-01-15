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
#ifndef GENERATOR_LINE_H_
#define GENERATOR_LINE_H_

#include <cstddef>
#include <vector>

#include "Generator.h"
#include "../perturbator/Perturbator.h"

using perturbator::Perturbator;

namespace generator {

/**
 * Generates a list of nodes.
 * Nodes are generated along the main anti-diagonal of given panel, according
 * to an uniform distribution of the distances.
 * Nodes are guaranteed to be generated inside given panel.
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Line: public Generator {
 public:
    /**
     * Constructor.
     * @param[in] perturbator Perturbator to use
     */
    explicit Line(const Perturbator &perturbator);


    /**
     * Destructor.
     */
    virtual ~Line();


    /**
     * Generates a list of points on a panel.
     * Points are placed along the anti-diagonal of the panel.
     * @param[in] panel  Panel on which generate nodes
     * @param[in] nHoles Number of nodes to generate
     * @return A list of nodes on given panel
     */
    virtual vector<Node>
    generate(const Panel panel, const size_t nHoles) const;


 private:
    const Perturbator &perturbator;  ///< Perturbator to use
};

}  // namespace generator

#endif  // GENERATOR_LINE_H_
