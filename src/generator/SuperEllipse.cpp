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
#include <math.h>

#include <iostream>
#include <cmath>
#include <vector>

#include "SuperEllipse.h"

#define PI 3.1415926535897

using std::abs;

namespace generator {

/**
 * Returns sign of a value.
 * @param[in] v Value
 * @return Sign of the value: -1, 0 or +1 when value is negative, zero or
 * positive
 */
static int sign(const double v) {
    return (v == 0.0) ? 0 : ((v < 0) ? -1 : +1);
}


SuperEllipse::SuperEllipse(
    const Perturbator &perturbator,
    const double m,
    const double n
) :
    perturbator(perturbator), m(m), n(n) {
}


SuperEllipse::~SuperEllipse() {
}


/**
 * This algorithm guarantees node to be on the panel as long as
 * A <= panel.width / 2
 * B <= panel.height / 2
 */
vector<Node>
SuperEllipse::generate(const Panel panel, const size_t nHoles) const {
    const double angle = 2.0 * PI / nHoles,
                 A     = panel.getWidth() * 0.5,
                 B     = panel.getHeight() * 0.5,
                 c_x   = A,
                 c_y   = B;
    vector<Node> nodes;

    for (unsigned int i = 0; i < nHoles; i++) {
        const double theta = angle * i,
                     c     = cos(theta),
                     s     = sin(theta),
                     x     = A * pow(abs(c), 2.0 / m) * sign(c) + c_x,
                     y     = B * pow(abs(s), 2.0 / n) * sign(s) + c_y;
        nodes.push_back(Node(x, y));
    }

    return perturbator(nodes, panel);
}

}  // namespace generator
