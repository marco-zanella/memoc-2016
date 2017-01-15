#!/bin/bash
########################################################################
# Runs Random solver on generated instances
INSTANCES_DIR=../run/instances
OUTDIR=../run/random_solver

for instance in ${INSTANCES_DIR}/*
do
    filename=$(basename "$instance")
    filename="${filename%.*}"
    ./random_solver < $instance > $OUTDIR/$filename.solution
done
