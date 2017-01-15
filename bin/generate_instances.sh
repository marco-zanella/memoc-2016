#!/bin/bash
########################################################################
# Generates instances
OUTDIR=../run/instances

for size in {10..80..10}
do
    for repeat in {1..20}
    do
        ./instance_generator -N ${size} > ${OUTDIR}/${size}_${repeat}.instance
    done
done
