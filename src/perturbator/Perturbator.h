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
#ifndef PERTURBATOR_PERTURBATOR_H_
#define PERTURBATOR_PERTURBATOR_H_

#include <vector>

#include "../Node.h"
#include "../Panel.h"

using std::vector;

namespace perturbator {

/**
 * Perturbates a list of nodes.
 * Perturbation should be such that points stays on the panel.
 * 
 * This class follows the Strategy Design Pattern.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Perturbator {
 public:
    /**
     * Destructor.
     */
    virtual ~Perturbator();


    /**
     * Perturbates a list of points on a panel.
     * @param[in] nodes  Points to perturbate
     * @param[in] panel  Panel on which operate
     * @return A new list of perturbated points
     */
    vector<Node> operator()(
        const vector<Node> &nodes,
        const Panel &panel) const;


    /**
     * Perturbates a list of points on a panel.
     * @param[in] nodes  Points to perturbate
     * @param[in] panel  Panel on which operate
     * @return A new list of perturbated points
     */
    virtual vector<Node> perturbate(
        const vector<Node> &nodes,
        const Panel &panel) const = 0;
};

}  // namespace perturbator

#endif  // PERTURBATOR_PERTURBATOR_H_
