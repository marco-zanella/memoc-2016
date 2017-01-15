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
#ifndef GENERATOR_GENERATOR_H_
#define GENERATOR_GENERATOR_H_

#include <cstddef>
#include <vector>

#include "../Node.h"
#include "../Panel.h"

using std::vector;

namespace generator {

/**
 * Generates a list of nodes.
 * Nodes are guaranteed to be generated inside given panel.
 *
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Generator {
 public:
    /**
     * Destructor.
     */
    virtual ~Generator();


    /**
     * Generates a list of points on a panel.
     * @param[in] panel  Panel on which generate nodes
     * @param[in] nHoles Number of nodes to generate
     * @return A list of nodes on given panel
     */
    vector<Node> operator()(const Panel panel, const size_t nHoles) const;


    /**
     * Generates a list of points on a panel.
     * @param[in] panel  Panel on which generate nodes
     * @param[in] nHoles Number of nodes to generate
     * @return A list of nodes on given panel
     */
    virtual vector<Node>
    generate(const Panel panel, const size_t nHoles) const = 0;
};

}  // namespace generator

#endif  // GENERATOR_GENERATOR_H_
