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
#ifndef SOLVER_CPLEXMANAGER_H_
#define SOLVER_CPLEXMANAGER_H_

#include <ilcplex/cplex.h>

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

namespace solver {

/**
 * Handles calls to CPLEX.
 * Offers a simplified interface to the CPLEX linear programming
 * environment.
 * Every CPLEXManager is responsible for a single Linear Programming
 * problem in CPLEX.
 *
 * This class follows the Facade Design Pattern and offers a Fluent Interface.
 *
 * @author Marco Zanella <marco.zanella.9@studenti.unipd.it>
 */
class CPLEXManager {
 public:
    static const double INF;  ///< Represents +infinity

    /**
     * Constructor.
     * Initializes CPLEX environment and problem.
     */
    CPLEXManager();


    /**
     * Destructor.
     * Finalizes CPLEX environment and problem.
     */
    ~CPLEXManager();


    /**
     * Tells whether problem has a solution.
     * @return True if the problem has a solution
     * @note Returns false if called before solving the problem
     */
    bool hasSolution() const;


    /**
     * Returns value of the objective function.
     * @return Value of the objective function
     * @note Returns 0.0 if called before solving the problem
     */
    double getValue() const;


    /**
     * Returns value of a variable.
     * @param[in] name Name of the variable
     * @return Value associated to given variable in the solution
     * @note Returns 0.0 if called before solving the problem
     */
    double getVariable(const string &name) const;


    /**
     * Adds a continuous variable to the problem.
     * @param[in] name       Name of the variable
     * @param[in] cost       Cost in the objective function
     * @param[in] lowerbound Minimum legal value
     * @param[in] upperbound Maximum legal value
     * @return This CPLEXManager itself
     */
    CPLEXManager &addContinuousVar(
        const string &name,
        const double cost = 0.0,
        const double lowerbound = -INF,
        const double upperbound = +INF);


    /**
     * Adds an integer variable to the problem.
     * @param[in] name       Name of the variable
     * @param[in] cost       Cost in the objective function
     * @param[in] lowerbound Minimum legal value
     * @param[in] upperbound Maximum legal value
     * @return This CPLEXManager itself
     */
    CPLEXManager &addIntegerVar(
        const string &name,
        const double cost = 0.0,
        const double lowerbound = -INF,
        const double upperbound = +INF);


    /**
     * Adds a boolean variable to the problem.
     * @param[in] name Name of the variable
     * @param[in] cost Cost in the objective function
     * @return This CPLEXManager itself
     */
    CPLEXManager &addBooleanVar(const string &name, const double cost = 0.0);


    /**
     * Adds a new "<=" constraint to the problem.
     * Constraints are in the form a*x <= b, where a, b and x are
     * vectors.
     * @param[in] a     Coefficients of variables
     * @param[in] x     Names of variables
     * @param[in] b     Right hand side value
     * @return This CPLEXManager itself
     */
    CPLEXManager &addLeqConstraint(
        const vector<double> a,
        const vector<string> x,
        const double b);


    /**
     * Adds a new "=" constraint to the problem.
     * Constraints are in the form a*x = b, where a, b and x are
     * vectors.
     * @param[in] a     Coefficients of variables
     * @param[in] x     Names of variables
     * @param[in] b     Right hand side value
     * @return This CPLEXManager itself
     */
    CPLEXManager &addEqConstraint(
        const vector<double> a,
        const vector<string> x,
        const double b);


    /**
     * Adds a new ">=" constraint to the problem.
     * Constraints are in the form a*x >= b, where a, b and x are
     * vectors.
     * @param[in] a     Coefficients of variables
     * @param[in] x     Names of variables
     * @param[in] b     Right hand side value
     * @return This CPLEXManager itself
     */
    CPLEXManager &addGeqConstraint(
        const vector<double> a,
        const vector<string> x,
        const double b);


    /**
     * Changes the type of optimization to "min".
     * @return This CPLEXManager itself
     */
    CPLEXManager &setMin();


    /**
     * Changes the type of optimization to "max".
     * @return This CPLEXManager itself
     */
    CPLEXManager &setMax();


    /**
     * Solves the problem.
     * @return This CPLEXManager itself
     */
    CPLEXManager &solve();


    /**
     * Loads problem form a file.
     * @param[in] filepath Path to the file
     * @return This CPLEXManager itself
     */
    CPLEXManager &loadProblem(const char *filepath);


    /**
     * Saves problem to a file.
     * @param[in] filepath Path to the file
     * @return This CPLEXManager itself
     */
    CPLEXManager &saveProblem(const char *filepath) const;


    /**
     * Saves solution to a file.
     * @param[in] filepath Path to the file
     * @return This CPLEXManager itself
     */
    CPLEXManager &saveSolution(const char *filepath) const;



 private:
    bool solved;                 ///< Tells whether problem was solved
    double obj_val;              ///< Value of the objective function
    CPXENVptr environment;       ///< CPLEX environment
    CPXLPptr  problem;           ///< CPLEX problem
    map<string, int> offsets;    ///< Offsets of variables
    map<string, double> values;  ///< Values of variables in the solution


    /**
     * Adds a variable to the problem.
     * Type of the variable can be one of C (continuous), I (integer) or
     * B (boolean).
     * @param[in] name       Name of the variable
     * @param[in] type       Type of the variable
     * @param[in] cost       Cost in the objective function
     * @param[in] lowerbound Minimum legal value
     * @param[in] upperbound Maximum legal value
     * @return This CPLEXManager itself
     */
    CPLEXManager &addVar(
        const string &name,
        const char type = 'C',
        const double cost = 0.0,
        const double lowerbound = -INF,
        const double upperbound = +INF);



    /**
     * Adds a new constraint to the problem.
     * Constraints are in the form a*x = b, where a, b and x are
     * vectors.
     * Sense of (in)equality can be one of L (less than or equal to),
     * E (equality) or G (greater than or equal to).
     * @param[in] a     Coefficients of variables
     * @param[in] x     Names of variables
     * @param[in] sense Sense of the inequality (or equality)
     * @param[in] b     Right hand side value
     * @return This CPLEXManager itself
     */
    CPLEXManager &addConstraint(
        const vector<double> a,
        const vector<string> x,
        const char sense,
        const double b);
};

}  // namespace solver

#endif  // SOLVER_CPLEXMANAGER_H_
