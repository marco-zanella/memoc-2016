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
#include <iostream>

#include "Stopwatch.h"

Stopwatch::Stopwatch() {
}


Stopwatch::~Stopwatch() {
}


Stopwatch &
Stopwatch::start() {
    cpu_start  = cpu_now();
    user_start = user_now();

    return const_cast<Stopwatch &>(*this);
}


Stopwatch &
Stopwatch::stop() {
    cpu_stop  = cpu_now();
    user_stop = user_now();

    return const_cast<Stopwatch &>(*this);
}


double
Stopwatch::getUserTime() const {
    const double d_usec = user_stop.tv_usec - user_start.tv_usec,
                 d_sec  = user_stop.tv_sec  - user_start.tv_sec;
    return d_sec + d_usec * 1e-6;
}


double
Stopwatch::getCPUTime() const {
    return static_cast<double>(cpu_stop - cpu_start) / CLOCKS_PER_SEC;
}


Stopwatch &
Stopwatch::quickPrint() const {
    std::cout << "User time: " << getUserTime() << " s" << std::endl;
    std::cout << "CPU time:  " << getCPUTime()  << " s" << std::endl;

    return const_cast<Stopwatch &>(*this);
}



struct timeval
Stopwatch::user_now() {
    struct timeval now;

    gettimeofday(&now, NULL);

    return now;
}


clock_t
Stopwatch::cpu_now() {
    return clock();
}
