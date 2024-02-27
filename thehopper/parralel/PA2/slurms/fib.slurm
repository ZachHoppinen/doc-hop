#!/bin/bash
#SBATCH --job-name fib_openmp #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 28 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p defq # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 23:00:00 # run time. 23 hours here.

# Set number of threads
START=1
END=28
for (( c=$START; c<=$END; c++ ))
do
    export OMP_NUM_THREADS=$c
    echo "Running with ${OMP_NUM_THREADS} threads."
    for k in $(seq 1 5)
    do
        ../build/bin/fib 10
        ../build/bin/fib 30
        ../build/bin/fib 40
    done
done