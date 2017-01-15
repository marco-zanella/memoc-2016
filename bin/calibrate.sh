#!/bin/bash
########################################################################
# Performs calibration for the Genetic Algorithm
INSTANCES_DIR=../run/ga_calibration/instances
OUT=../run/ga_calibration/results.dat

########################################################################
# Writes header to results file
echo "Cost Size ID Crossover Mutation Threshold Accept Improvement PopSize" > ${OUT}

########################################################################
# Generates calibration set
for i in 50 60 70 80
do
    for j in {1..5}
    do
        ./instance_generator -N $i > ${INSTANCES_DIR}/${i}_${j}.instance
    done
done

########################################################################
# Loops over instances
for instance in ${INSTANCES_DIR}/*
do
    filename=$(basename "$instance")
    filename="${filename%.*}"
    size=`echo $filename | cut -d_ -f1`
    id=`echo $filename | cut -d_ -f2`

    # Loops over reduced paramters' space
    for j in {1..15}
    do
        c=`bc <<< "scale = 2; $((RANDOM % 100)) / 100"`
        m=`bc <<< "scale = 2; $((RANDOM % 100)) / 100"`
        t=`bc <<< "scale = 2; $((RANDOM % 100)) / 100"`
        a=`bc <<< "scale = 2; $((RANDOM % 100)) / 100"`
        i=`bc <<< "scale = 2; $((RANDOM % 100)) / 100"`
        s=$((RANDOM % 48 + 16))

        # Repeats 10 times for statistical significance
        for k in {1..10}
        do
            cost=`./ga_solver -c $c -m $m -t $t -p $a -i $i -S $s < $instance | grep Cost | cut -d' ' -f2`
            echo "$cost $size $id $c $m $t $a $i $s" >> ${OUT}
        done
    done
done
