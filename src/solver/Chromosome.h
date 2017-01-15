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
#ifndef SOLVER_CHROMOSOME_H_
#define SOLVER_CHROMOSOME_H_

namespace solver {

/** A chromosome of a genetic algorithm. */
struct chromosome_s {
    unsigned int *genes;  ///< Genes
    unsigned int size;    ///< Number of genes
    double fitness;       ///< Fitness
};

/** Type of a chromosome. */
typedef struct chromosome_s Chromosome;


/**
 * Creates a chromosome.
 * Allocates space for a chromosome.
 * @param[out] chromosome Pointer to chromosome to create
 * @param[in]  size       Number of genes
 * @note chromosome_delete must be called to deallocate resources
  */
void chromosome_create(Chromosome *chromosome, const unsigned int size);


/**
 * Deletes a chromosome.
 * Deallocates resources of a chromosome.
 * @param[out] chromosome Chromosome to destroy
 */
void chromosome_delete(Chromosome *chromosome);


/**
 * Copies a chromosome into another one.
 * Destination chromosome will become a perfect copy of the
 * source one.
 * @param[out] dst Pointer to destination chromosome
 * @param[in]  src Source chromosome
 */
void chromosome_copy(Chromosome *dst, const Chromosome *src);


/**
 * Evaluates a chromosome.
 * Sets the fitness of a chromosome using given cost matrix.
 * @param[in, out] chromosome Chromosome to evaluate
 * @param[in]      costs      Costs matrix
 */
void chromosome_evaluate(Chromosome *chromosome, const double *costs);


/**
 * Returns Hamming distance between two chromosomes.
 * Hamming distance is the number of genes in which the two chromosome
 * differ.
 * @param[in] A Pointer to first chromosome
 * @param[in] B Pointer to second chromosome
 * @return Hamming distance
 */
unsigned int chromosome_hamming_distance(
    const Chromosome *A,
    const Chromosome *B
);


/**
 * Mates two chromosomes.
 * Performs 1-cut ordered crossover.
 * @param[out] offspring Pointer to newborn chromosome
 * @param[in]  parent1   Pointer to first parent
 * @param[in]  parent2   Pointer to second parent
 */
void chromosome_crossover(
    Chromosome *offspring,
    const Chromosome *parent1,
    const Chromosome *parent2);


/**
 * Mutates a chromosome.
 * Performs 2-opt mutation.
 * @param[in, out] chromosome Pointer to chromosome to mutate
 */
void chromosome_mutation(Chromosome *chromosome);


/**
 * Improves a chromosome using a local search.
 * Performs a simple Hill-Climbing to improve this chromosome
 * @param[in, out] chromosome Pointer to chromosome to improve
 * @param[in]      costs      Cost matrix
 */
void chromosome_improvement(Chromosome *chromosome, const double *costs);

}  // namespace solver

#endif  // SOLVER_CHROMOSOME_H_
