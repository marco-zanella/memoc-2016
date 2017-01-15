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
#ifndef PANEL_H_
#define PANEL_H_

/**
 * An electrical panel.
 * Panels have a fixed size.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Panel {
 public:
    /**
     * Default constructor.
     * @param[in] width  Width of the panel
     * @param[in] height Height of the panel
     */
    Panel(const double width, const double height);

    /**
     * Destructor.
     */
    ~Panel();


    /**
     * Returns width of this panel.
     * @return Width of this panel
     */
    double getWidth() const;

    /**
     * Returns height of this panel.
     * @return Height of this panel
     */
    double getHeight() const;


 private:
    const double width;   ///< Width of this panel
    const double height;  ///< Height of this panel
};

#endif  // PANEL_H_
