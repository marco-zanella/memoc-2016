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
#ifndef RNG_H_
#define RNG_H_

/**
 * A random number generator.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class RNG {
 public:
    /**
     * Constructor.
     */
    RNG();


    /**
     * Constructor.
     * @param[in] seed Seed used to generate random numbers
     */
    explicit RNG(const unsigned int seed);


    /**
     * Returns a random number in given interval.
     * Returns a random number from an uniform distribution.
     * @param[in] min Lowerbound
     * @param[in] max Upperbound
     * @return Random number
     */
    double uniform(const double min, const double max);


    /**
     * Returns a random number.
     * Returns a random number from a normal distribution.
     * @param[in] mi    Mean of the distribution
     * @param[in] sigma Variance of the distribution
     * @return Random number from a normal distribution
     */
    double normal(const double mi, const double sigma);


 private:
    unsigned int seed;
};

#endif  // RNG_H_
