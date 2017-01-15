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
#include "Node.h"

unsigned int Node::last_id = 0;

Node::Node(const double x, const double y):
    identifier(++last_id), x(x), y(y) {
}

Node
Node::operator=(const Node &other) {
    return Node(other);
}


unsigned int
Node::getId() const {
    return identifier;
}

double
Node::getX() const {
    return x;
}

double
Node::getY() const {
    return y;
}


Node &
Node::save(ostream *stream) const {
    *stream << identifier << " " << x << " " << y << std::endl;

    return const_cast<Node &>(*this);
}


Node
Node::load(istream *stream) {
    unsigned int id;
    double x, y;

    *stream >> id >> x >> y;
    return Node(id, x, y);
}


Node::Node(const unsigned int id, const double x, const double y):
    identifier(id), x(x), y(y) {
}
