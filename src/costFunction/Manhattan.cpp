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
#include <cmath>

#include "Manhattan.h"

namespace costFunction {

Manhattan::~Manhattan() {
}

double
Manhattan::cost(const Node &A, const Node &B) const {
    const double D_x = std::abs(A.getX() - B.getX()),
                 D_y = std::abs(A.getY() - B.getY());
    return D_x + D_y;
}

}  // namespace costFunction
