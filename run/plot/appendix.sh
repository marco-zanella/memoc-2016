#!/bin/bash
########################################################################
# Performs analysis on strongly connected, symmetric TSP
CPLEX_DIR=../appendix/cplex_solver
GA_DIR=../appendix/ga_solver

########################################################################
# Aggregates data from CPLEX solver
echo "#Size Instance Cost WallclockTime" > cplex.dat
for instance in ${CPLEX_DIR}/*
do
    filepath=$(basename "$instance")
    filename="${filepath%.*}"
    size=`echo $filename | cut -d_ -f1`
    id=`echo $filename | cut -d_ -f2`
    data=`tail -n 1 $instance | cut -d" " -f2,4`

    echo "$size $id $data" >> cplex.dat
done



########################################################################
# Aggregates data from Genetic Algorithm solver
echo "#Size Instance Repeat Cost WallclockTime" > ga.dat
for instance in ${GA_DIR}/*
do
    filepath=$(basename "$instance")
    filename="${filepath%.*}"
    size=`echo $filename | cut -d_ -f1`
    id=`echo $filename | cut -d_ -f2`
    repeat=`echo $filename | cut -d_ -f3`
    data=`tail -n 1 $instance | cut -d" " -f2,4`

    echo "$size $id $repeat $data" >> ga.dat
done



########################################################################
# Computes cumulative percentage of solved instance for CPLEX solver
echo "Time Perc.Solved" > cplex_cumulative.dat
size=$((`cat cplex.dat | wc -l` - 1))
for t in 0.1 0.5 1.0 1.5 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 20.0 30.0 40.0 50.0 75.0 100.0 150.0 200.0 
do
    select="\$4 < $t && \$3 > -1"
    solved=`grep -v 'Size' cplex.dat | awk "$select" | wc -l`
    percentage=`bc <<< "scale = 4; $solved / $size * 100"`
    echo "$t $percentage" >> cplex_cumulative.dat
done



########################################################################
# Computes cumulative percentage of solved instance for Genetic Algorithm solver
echo "Time Perc.Solved" > ga_cumulative.dat
size=$((`cat ga.dat | wc -l` - 1))
for t in 0.1 0.5 1.0 1.5 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 20.0 30.0 40.0 50.0 75.0 100.0 150.0 200.0 
do
    select="\$5 < $t && \$4 > -1"
    solved=`grep -v 'Size' ga.dat | awk "$select" | wc -l`
    percentage=`bc <<< "scale = 4; $solved / $size * 100"` 
    echo "$t $percentage" >> ga_cumulative.dat
done



########################################################################
# Computes additional statistics about the experiment
Rscript appendix.R



########################################################################
# Generates plots
./appendix.gpl



########################################################################
# Clean up
rm -f *.dat