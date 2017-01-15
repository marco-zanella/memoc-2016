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
#include <stdio.h>
#include <string.h>
#include <ilcplex/cplex.h>

#include <string>
#include <vector>
#include <map>

#include "CPLEXManager.h"


/**
 * Checks the return value of a CPLEX call.
 * Prints an error message in case of error.
 */
#define CPX_CALL(call) {     \
    int status = call;       \
    if (status) {            \
        CPX_ERROR(status);   \
    }                        \
}


/**
 * Reads and prints a CPLEX error message.
 */
#define CPX_ERROR(status) {                                      \
    char msg[4096];                                              \
    unsigned int size;                                           \
    CPXgeterrorstring(NULL, status, msg);                        \
    size = strlen(msg);                                          \
    if (size > 0) {                                              \
        msg[size - 1] = '\0';                                    \
    }                                                            \
    fprintf(stderr, "[%s @ %d]: %s\n", __FILE__, __LINE__, msg); \
}


namespace solver {

const double CPLEXManager::INF = CPX_INFBOUND;


CPLEXManager::CPLEXManager() {
    int status;

    solved = false;

    environment = CPXopenCPLEX(&status);
    if (status) {
        CPX_ERROR(status);
    }

    problem = CPXcreateprob(environment, &status, "");
    if (status) {
        CPX_ERROR(status);
    }
}


CPLEXManager::~CPLEXManager() {
    CPXfreeprob(environment, &problem);
    CPXcloseCPLEX(&environment);
}


bool CPLEXManager::hasSolution() const {
    return solved;
}



double CPLEXManager::getValue() const {
    return solved ? obj_val : 0.0;
}


double CPLEXManager::getVariable(const string &name) const {
    double value = values.find(name)->second;
    return solved ? value : 0.0;
}



CPLEXManager &CPLEXManager::addContinuousVar(
        const string &name,
        const double cost,
        const double lowerbound,
        const double upperbound) {
    return addVar(name, 'C', cost, lowerbound, upperbound);
}


CPLEXManager &CPLEXManager::addIntegerVar(
        const string &name,
        const double cost,
        const double lowerbound,
        const double upperbound) {
    return addVar(name, 'I', cost, lowerbound, upperbound);
}


CPLEXManager &CPLEXManager::addBooleanVar(
    const string &name,
    const double cost) {
    return addVar(name, 'B', cost, 0.0, 1.0);
}



CPLEXManager &CPLEXManager::addLeqConstraint(
        const vector<double> a,
        const vector<string> x,
        const double b) {
    return addConstraint(a, x, 'L', b);
}


CPLEXManager &CPLEXManager::addEqConstraint(
        const vector<double> a,
        const vector<string> x,
        const double b) {
    return addConstraint(a, x, 'E', b);
}


CPLEXManager &CPLEXManager::addGeqConstraint(
        const vector<double> a,
        const vector<string> x,
        const double b) {
    return addConstraint(a, x, 'G', b);
}



CPLEXManager &CPLEXManager::setMin() {
    CPX_CALL(CPXchgobjsen(environment, problem, CPX_MIN));
    return *this;
}


CPLEXManager &CPLEXManager::setMax() {
    CPX_CALL(CPXchgobjsen(environment, problem, CPX_MAX));
    return *this;
}



CPLEXManager &CPLEXManager::solve() {
    int type;

    CPX_CALL(CPXmipopt(environment, problem));

    // Checks whether solution exists
    CPX_CALL(CPXsolninfo(
        environment,
        problem,
        NULL,
        &type,
        NULL,
        NULL));
    solved = type != CPX_NO_SOLN;


    // Stops if no solution exists
    if (!solved) {
        return *this;
    }


    CPX_CALL(CPXgetobjval(environment, problem, &obj_val));

    // Reads back values of variables
    int size = CPXgetnumcols(environment, problem);
    vector<double> vars(size);

    CPX_CALL(CPXgetx(environment, problem, &vars[0], 0, size - 1));
    map<string, int>::iterator i;
    for (i = offsets.begin(); i != offsets.end(); i++) {
        values[i->first] = vars[i->second];
    }

    return *this;
}



CPLEXManager &CPLEXManager::loadProblem(const char *filepath) {
    CPX_CALL(CPXreadcopyprob(environment, problem, filepath, NULL));
    return *this;
}


CPLEXManager &CPLEXManager::saveProblem(const char *filepath) const {
    CPX_CALL(CPXwriteprob(environment, problem, filepath, NULL));
    return const_cast<CPLEXManager &>(*this);
}


CPLEXManager &CPLEXManager::saveSolution(const char *filepath) const {
    CPX_CALL(CPXsolwrite(environment, problem, filepath));
    return const_cast<CPLEXManager &>(*this);
}



CPLEXManager &CPLEXManager::addVar(
        const string &name,
        const char type,
        const double cost,
        const double lowerbound,
        const double upperbound) {
    char *local_name = const_cast<char *>(name.c_str());

    CPX_CALL(CPXnewcols(
        environment,
        problem,
        1,
        &cost,
        &lowerbound,
        &upperbound,
        &type,
        &local_name));
    offsets[local_name] = CPXgetnumcols(environment, problem) - 1;

    return *this;
}


CPLEXManager &CPLEXManager::addConstraint(
        const vector<double> a,
        const vector<string> x,
        const char sense,
        const double b) {
    int rmatbeg = 0;

    vector<int> idx;
    for (unsigned int i = 0; i < x.size(); i++) {
        idx.push_back(offsets[x[i]]);
    }

    CPX_CALL(CPXaddrows(
        environment,
        problem,
        0,
        1,
        x.size(),
        &b,
        &sense,
        &rmatbeg,
        &idx[0],
        &a[0],
        NULL,
        NULL));

    return *this;
}

}  // namespace solver
