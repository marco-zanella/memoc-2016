#!/bin/bash
########################################################################
# Self-calibrating Genetic Algorithm solver

########################################################################
# Default values
maxT=5.0
maxM=10000
maxK=1000

########################################################################
# Parses command line options
while getopts T:M:K:h opt; do
    case $opt in
    T)
        maxT=$OPTARG
        ;;
    M)
        maxM=$OPTARG
        ;;
    K)
        maxK=$OPTARG
        ;;
    h)
        echo "MANAGED GENETIC SOLVER"
        echo "Solves and instance of the TSP problem by applying a genetic algorithm with a local search and adaptive parameters."
        echo "Instance is read form standard input, solution is written to standard output."
        echo "Most paramters are chosen automatically."
        echo ""
        echo "Usage:"
        echo "$0 -T <double> -M <int> -K <int> -h"
        echo ""
        echo "Options:"
        echo "  -T <double> 	 Maximum execution time, in secs (default 5.0)"
        echo "  -M <int>    	 Maximum number of iterations (default: 10000)"
        echo "  -K <int>    	 Maximum number of consecutive iterations"
        echo "              	 without improvevement (default: 1000)"
        ;;
    esac
done

shift $((OPTIND - 1))


########################################################################
# Reads instance
instance=`cat`
size=`echo $instance | head -n 1 | cut -d" " -f1`
opt="-T $maxT -M $maxM -K $maxK"


########################################################################
# Computes parameters and runs solver
# Algorithm is handcrafted and was obtained from analysis
if [ $size -lt 75 ]
then
    echo $instance | ./ga_solver -c 0.98 -m 1.00 -t 0.80 -p 0.62 -i 0.31 -S 32 $opt
else
    echo $instance | ./ga_solver -c 1.00 -m 1.00 32 $opt
fi
