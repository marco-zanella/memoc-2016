#!/bin/bash
########################################################################
# Runs CPLEX solver on generated instances
INSTANCES_DIR=../run/instances
OUTDIR=../run/cplex_solver

for instance in ${INSTANCES_DIR}/*
do
    filename=$(basename "$instance")
    filename="${filename%.*}"
    ./cplex_solver < $instance > $OUTDIR/$filename.solution
done
