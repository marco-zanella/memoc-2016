#!/bin/bash
########################################################################
# Runs Genetic Algorithm solver on generated instances
INSTANCES_DIR=../run/instances
OUTDIR=../run/ga_solver

for instance in ${INSTANCES_DIR}/*
do
    filename=$(basename "$instance")
    filename="${filename%.*}"
    echo "Running $instance..."
    for i in {1..10}
    do
        ./ga_solver.sh -T 10.0 < $instance > $OUTDIR/${filename}_$i.solution
    done
done
