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



////////////////////////////////////////////////////////////////////////
// Support functions

/**
 * Copies a chromosome with a reversed portion.
 * Source chromosome is copied into destination one, with positions from
 * i to j in reverse order.
 * @note Source and destination chromosomes must be different
 */
static void copy_and_reverse(
    solver::Chromosome *dst,
    const solver::Chromosome *src,
    const unsigned int i,
    const unsigned int j,
    const double *costs) {
    const unsigned int N = src->size;

    for (unsigned int k = 0; k < i; k++) {
        dst->genes[k] = src->genes[k];
    }

    for (unsigned int k = 0; k <= (j - i) / 2; k++) {
        dst->genes[i + k] = src->genes[j - k];
        dst->genes[j - k] = src->genes[i + k];
    }

    for (unsigned int k = j + 1; k < N; k++) {
        dst->genes[k] = src->genes[k];
    }

    chromosome_evaluate(dst, costs);
}



/**
 * Performs a two-opt improvement.
 * Remove two arcs from a solution and tries every possible combination
 * to fix the cycle; then selects best combination.
 * If no feasible alternative exists, chromosome is left as it is.
 * @param[in, out] chromosome Chromosome to improve
 * @param[in]      costs      Cost matrix
 */
static void two_opt(solver::Chromosome *chromosome, const double *costs) {
    const unsigned int N = chromosome->size;
    unsigned int i, j;
    solver::Chromosome neighbor, best;

    chromosome_create(&neighbor, N);
    chromosome_create(&best, N);
    best.fitness = -1.0;

    // Tries every possible 2-opt combination
    for (i = 1; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            copy_and_reverse(&neighbor, chromosome, i, j, costs);
            if (neighbor.fitness > best.fitness && neighbor.fitness > 0.0) {
                chromosome_copy(&best, &neighbor);
            }
        }
    }

    // Copies best chromosome only if improved
    if (best.fitness > -1.0) {
        chromosome_copy(chromosome, &best);
    }

    chromosome_delete(&neighbor);
    chromosome_delete(&best);
}

////////////////////////////////////////////////////////////////////////



namespace solver {

void chromosome_create(Chromosome *chromosome, const unsigned int size) {
    SAFE_MALLOC(chromosome->genes, unsigned int *, size * sizeof(unsigned int));
    chromosome->size = size;
}


void chromosome_delete(Chromosome *chromosome) {
    free(chromosome->genes);
    chromosome->size = 0;
    chromosome->fitness = 0.0;
}


void chromosome_copy(Chromosome *dst, const Chromosome *src) {
    memcpy(dst->genes, src->genes, dst->size * sizeof(unsigned int));
    dst->fitness = src->fitness;
}


void chromosome_evaluate(Chromosome *chromosome, const double *costs) {
    const unsigned int size = chromosome->size;
    unsigned int i;
    unsigned int *genes = chromosome->genes;
    double cost = 0.0;

    for (i = 0; i < size; i++) {
        const double arc = costs[genes[i] * size + genes[(i + 1) % size]];
        if (arc < 0.0) {
            cost = -1.0;
            break;
        }
        cost += arc;
    }

    chromosome->fitness = 1.0 / cost;
}


unsigned int chromosome_hamming_distance(
    const Chromosome *A,
    const Chromosome *B
) {
    unsigned int i, distance = 0;

    for (i = 0; i < A->size; i++) {
        distance += A->genes[i] != B->genes[i];
    }

    return distance;
}


void chromosome_crossover(
    Chromosome *offspring,
    const Chromosome *parent1,
    const Chromosome *parent2) {
    const unsigned int N = offspring->size,
                       p = static_cast<int>(rng.uniform(1.0, N - 1.0));
    bool *already_in;

    SAFE_MALLOC(already_in, bool *, N * sizeof(bool));
    memset(already_in, 0, N * sizeof(bool));

    // Adds nodes from first parent
    for (unsigned int i = 0; i < p; i++) {
        offspring->genes[i] = parent1->genes[i];
        already_in[parent1->genes[i]] = true;
    }

    // Adds nodes from second parent, preserving order
    unsigned int cursor = p;
    for (unsigned int i = 0; i < N; i++) {
        if (!already_in[parent2->genes[i]]) {
            offspring->genes[cursor++] = parent2->genes[i];
        }
    }

    free(already_in);
}


void chromosome_mutation(Chromosome *chromosome) {
    const unsigned int N = chromosome->size,
                       i = static_cast<int>(rng.uniform(1.0, N - 0.0)),
                       j = static_cast<int>(rng.uniform(1.0, N - 0.0)),
                       a = (i < j) ? i : j,
                       b = (i < j) ? j : i;

    for (unsigned int k = 0; k <= (b - a) / 2; k++) {
        const unsigned int swap = chromosome->genes[a + k];
        chromosome->genes[a + k] = chromosome->genes[b - k];
        chromosome->genes[b - k] = swap;
    }
}



/**
 * @todo This could be improved with plateaux, radomization, etc...
 */
void chromosome_improvement(Chromosome *chromosome, const double *costs) {
    double old_fitness = -2.0;

    while (chromosome->fitness > old_fitness) {
        old_fitness = chromosome->fitness;
        two_opt(chromosome, costs);
    }
}

}  // namespace solver
