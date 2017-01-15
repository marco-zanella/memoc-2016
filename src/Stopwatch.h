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
#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <time.h>
#include <sys/time.h>

/**
 * Implements a simple stopwatch.
 *
 * This class has a Fluent Interface.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class Stopwatch {
 public:
    /**
     * Default constructor.
     */
    Stopwatch();

    /**
     * Destructor.
     */
    virtual ~Stopwatch();


    /**
     * Starts this stopwatch.
     * Returns this stopwatch itself.
     */
    Stopwatch &start();

    /**
     * Stops this stopwatch.
     * Returns this stopwatch itself.
     */
    Stopwatch &stop();


    /**
     * Reads user time, in seconds.
     * @return Elapsed user time
     */
    double getUserTime() const;

    /**
     * Reads CPU time, in seconds.
     * @return Elapsed CPU time
     */
    double getCPUTime() const;


    /**
     * Prints a string representation of the current time.
     * Prints on standard output. Mainly for debug purposes.
     * @return This stopwatch itself
     */
    Stopwatch &quickPrint() const;


 private:
    clock_t cpu_start;            ///< CPU start time
    clock_t cpu_stop;             ///< CPU stop time
    struct timeval user_start;    ///< User start time
    struct timeval user_stop;     ///< User stop time


    /**
     * Returns current user time.
     * @return Current user time
     */
    static struct timeval user_now();

    /**
     * Returns current CPU time.
     * @return Current CPU time
     */
    static clock_t cpu_now();
};

#endif  // STOPWATCH_H_
