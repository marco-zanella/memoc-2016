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
#ifndef SOLVER_POPULATION_H_
#define SOLVER_POPULATION_H_

#include "Chromosome.h"

namespace solver {

/** A population of a genetic algorithm. */
struct population_s {
    Chromosome *chromosomes;  ///< Chromosomes
    unsigned int size;        ///< Number of chromosomes
    unsigned int maxSize;     ///< Maximum size of the population
    double mean;              ///< Mean fitness
    double sigma2;            ///< Variance of fitnesses
    Chromosome *worst;        ///< Pointer to worst chromosome
    const double *costs;      ///< Cost matrix
};

/** Configuration of a genetic algorithm. */
struct ga_conf_s {
    double max_p_crossover;  ///< Maximum probability of a crossover
    double max_p_mutation;   ///< Maximum probability of a mutation
    double threshold;        ///< Threshold under wich two chromosomes
                             ///< are toconsidered similar
    double P;                ///< Probability to accept a chromosome when
                             ///< there is a similar one in the population
    double p_improvement;    ///< Probability of improve a good chromosome
};


/** Type of a population. */
typedef struct population_s Population;

/** Type of a configuration of a genetic algorithm. */
typedef struct ga_conf_s GAConf;


/**
 * Creates a population.
 * Allocates space for a population.
 * @param[out] population Pointer to population to create
 * @param[in]  maxSize    Maximum size of population
 * @param[in]  N          Number of genes in a chromosome
 * @param[in]  costs      Costs matrix
 * @note population_delete must be called to deallocate resources
  */
void population_create(
    Population *population,
    const unsigned int maxSize,
    const unsigned int N,
    const double *costs);


/**
 * Deletes a population.
 * Deallocates resources of a population.
 * @param[out] population Population to destroy
 */
void population_delete(Population *population);


/**
 * Computes variance and mean of the population.
 * @param[in, out] population Pointer to population
 */
void population_variance(Population *population);


/**
 * Returns best individual in the population.
 * @param[in]  population Pointer to population
 * @param[out] chromosome Pointer to chromosome
 * @note This function expects chromosomes in the population to be sorted
 * (best one first).
 */
void population_best(const Population *population, Chromosome *chromosome);


/**
 * Selects a chromosome from the population.
 * Performs the Linear Ranking selection.
 * @param[in, out] population Pointer to population to select from
 * @param[out]     chromosome Pointer to selected chromosome
 * @note This function expects chromosomes in the population to be sorted
 * (best one first).
 */
void population_select(Population *population, Chromosome *chromosome);


/**
 * Tells whether a new chromosome should be accepted.
 * Chromosomes which are too similar to those already in the population
 * are accepted with a probability P; chromosomes significatively different
 * from the others are accepted. Likelihood is measued with the Hamming
 * distance.
 * Both likelihood threshold and accepting probability in case of
 * similarity are computed from the current status of the population.
 * @param[in] population    Pointer to population to test
 * @param[in] configuration Pointer to configuration of the genetic algorithm
 * @param[in] i             Index of the chromosome to test
 * @return True iff the chromosome should be accepted
 */
bool population_accept(
    const Population *population,
    const GAConf *configuration,
    const unsigned int i);


/**
 * Generates a new population.
 * Performs the Population Replacement.
 * @param[in]  population Pointer to population
 * @param[out] next       Pointer to next population
 * @param[in] configuration Pointer to configuration of the genetic algorithm
 * @note This function expects chromosomes in the population to be sorted
 * (best one first).
 */
void population_next_generation(
    Population *population,
    Population *next,
    const GAConf *configuration);


/**
 * Sorts chromosomes in the population.
 * @param[out] population Pointer to population to sort
 */
void population_sort(Population *population);

}  // namespace solver

#endif  // SOLVER_POPULATION_H_
