#!/bin/bash
########################################################################
# Case-study about a symmetric, strongly connected graph

########################################################################
# Generates instances
OUTDIR=../run/appendix/instances

for size in 60 70 80
do
    for i in {1..5}
    do
        ./instance_generator -N $size -s 0 -t 9999 > ${OUTDIR}/${size}_${i}.instance
    done
done



########################################################################
# Solves instances with CPLEX solver
INSTANCES_DIR=../run/appendix/instances
OUTDIR=../run/appendix/cplex_solver

for instance in ${INSTANCES_DIR}/*
do
    filename=$(basename "$instance")
    filename="${filename%.*}"
    echo "Running $instance..."
    ./cplex_solver < $instance > ${OUTDIR}/${filename}.solution
done



########################################################################
# Solves instances with Genetic Algorithm (multiple times)
INSTANCES_DIR=../run/appendix/instances
OUTDIR=../run/appendix/ga_solver

for instance in ${INSTANCES_DIR}/*
do
    filename=$(basename "$instance")
    filename="${filename%.*}"
    echo "Running $instance..."
    for i in {1..10}
    do
        ./ga_solver.sh -T 10.0 -K 5000 < $instance > ${OUTDIR}/${filename}_${i}.solution
    done
done