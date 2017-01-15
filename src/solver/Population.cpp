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
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Population.h"
#include "Chromosome.h"
#include "../RNG.h"


/**
 * Prints an error when malloc cannot allocate memory.
 */
#define MALLOC_ERROR \
  fprintf(stderr, "[%s: %d]: Cannot allocate memory.\n", __FILE__, __LINE__)


/**
 * Performs a memory allocation and checks for the result.
 */
#define SAFE_MALLOC(var, type, size)              \
    (var) = reinterpret_cast<type>(malloc(size)); \
    if (NULL == (var)) {                          \
        MALLOC_ERROR;                             \
    }


/** Random number generator. */
static RNG rng;

/**
 * Compares two chromosomes.
 * @param[in] A Pointer to first chromosome
 * @param[in] B Poinyer to second chromosome
 * @return -1, 0 or +1 if A has a better, equal or worse fitness than B
 */
int chromosome_compare(const void *A, const void *B) {
    const double fA = ((solver::Chromosome *) A)->fitness,
                 fB = ((solver::Chromosome *) B)->fitness;
    return (fA > fB) ? -1 : ((fA < fB) ? +1 : 0);
}


namespace solver {

void population_create(
    Population *population,
    const unsigned int maxSize,
    const unsigned int N,
    const double *costs) {
    SAFE_MALLOC(
        population->chromosomes,
        Chromosome *,
        maxSize * sizeof(Chromosome));
    population->size    = 0;
    population->maxSize = maxSize;
    population->costs   = costs;

    for (unsigned int i = 0; i < maxSize; i++) {
        chromosome_create(population->chromosomes + i, N);
    }
}


void population_delete(Population *population) {
    unsigned int i;

    for (i = 0; i < population->maxSize; i++) {
        chromosome_delete(population->chromosomes + i);
    }

    free(population->chromosomes);
    population->size = 0;
}


void population_variance(Population *population) {
    const Chromosome *c = population->chromosomes;
    unsigned int i, min = 0, size = 0;
    double mean = 0.0, sigma2 = 0.0;

    // Computes mean
    for (i = 0; i < population->size; i++) {
        if (c[i].fitness > 0.0) {
            mean += 1.0 / c[i].fitness;
            size++;
            if (c[i].fitness < c[min].fitness) {
                min = i;
            }
        }
    }
    mean /= size;

    // Computes variance sigma^2
    for (i = 0; i < population->size; i++) {
        if (c[i].fitness > 0.0) {
            sigma2 += (mean - 1.0 / c[i].fitness) * (mean - 1.0 / c[i].fitness);
        }
    }
    sigma2 /= size;

    population->mean   = mean;
    population->sigma2 = sigma2;
    population->worst  = population->chromosomes + min;
}


void population_best(const Population *population, Chromosome *chromosome) {
    chromosome_copy(chromosome, population->chromosomes);
}


void population_select(Population *population, Chromosome *chromosome) {
    const unsigned int N = population->size;
    double *rank;

    SAFE_MALLOC(rank, double *, N * sizeof(double));

    // Assigns a rank based on position
    const double scaling = 2.0 / (N * (N + 1));
    for (unsigned int i = 0; i < N; i++) {
        rank[i] = (N - i) * scaling;
    }

    // Chooses a chromosome
    const double p = rng.uniform(0.0, 1.0);
    unsigned int i = N - 1;
    double sum = rank[0];
    while (sum < p) {
        sum += rank[i--];
    }

    chromosome_copy(chromosome, population->chromosomes + i);

    free(rank);
}


bool population_accept(
    const Population *population,
    const GAConf *configuration,
    const unsigned int i) {
    unsigned int j = 0;
    const Chromosome* c = population->chromosomes;

    const double threshold = configuration->threshold,
                 P         = configuration->P;
    const unsigned int min_d = static_cast<unsigned int>(threshold * c[0].size);

    while (j < i) {
        // If distance is smaller than threshold, accepts with probability P
        if (chromosome_hamming_distance(c + i, c + j) < min_d) {
            return rng.uniform(0.0, 1.0) < P;
        }
        j++;
    }

    // No similar chromosome exists in the population: accept
    return true;
}


void population_next_generation(
    Population *population,
    Population *next,
    const GAConf *configuration) {
    Chromosome parent1, parent2;
    chromosome_create(&parent1, population->chromosomes[0].size);
    chromosome_create(&parent2, population->chromosomes[0].size);


    // Calculates adaption factor as standard deviation of costs divided
    // by worst cost minus mean cost
    const double sd       = sqrt(population->sigma2),
                 mean     = population->mean,
                 worst    = 1.0 / population->worst->fitness,
                 adaption = (!isnan(sd / (worst - mean)))
                          ? sd / (worst - mean)
                          : 1.0;

    const double max_p_crossover = configuration->max_p_crossover,
                 max_p_mutation  = configuration->max_p_mutation,
                 p_crossover     = max_p_crossover * adaption,
                 p_mutation      = max_p_mutation * adaption,
                 p_improvement   = configuration->p_improvement;
    const unsigned int next_size = population->size;
    unsigned int i = 0;

    while (i < next_size) {
        // Selects two parents
        population_select(population, &parent1);
        population_select(population, &parent2);

        // Crossover occurs with a certain probability (otherwise one
        // parent is copied as it is)
        if (rng.uniform(0.0, 1.0) < p_crossover) {
            chromosome_crossover(next->chromosomes + i, &parent1, &parent2);
        } else {
            chromosome_copy(next->chromosomes + i, &parent1);
        }

        // Mutation occurs with a certain probability
        if (rng.uniform(0.0, 1.0) < p_mutation) {
            chromosome_mutation(next->chromosomes + i);
        }

        // Evaluates fitness of the offspring
        chromosome_evaluate(next->chromosomes + i, population->costs);

        // Improvement occurs for "good" candidates
        const double cost = 1.0 / next->chromosomes[i].fitness;
        if (cost > 0.0 &&
            cost < mean - sd &&
            rng.uniform(0.0, 1.0) < p_improvement) {
            chromosome_improvement(next->chromosomes + i, population->costs);
        }

        // Adds offspring to population if it meets acceptance criteria
        if (population_accept(next, configuration, i)) {
            i++;
        }
    }
    next->size  = next_size;
    next->costs = population->costs;
    population_sort(next);
    population_variance(next);


    // Population replacement
    Population swap = *population;
    *population = *next;
    *next = swap;


    chromosome_delete(&parent1);
    chromosome_delete(&parent2);
}


void population_sort(Population *population) {
    qsort(
        population->chromosomes,
        population->size,
        sizeof(Chromosome),
        chromosome_compare);
}

}  // namespace solver
