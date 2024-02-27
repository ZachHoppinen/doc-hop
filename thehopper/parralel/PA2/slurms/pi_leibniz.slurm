#!/bin/bash
#SBATCH --job-name pi_leibniz_openmp #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 28 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p classroom # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 23:00:00 # run time. 5 minutes here.
module load gcc
module load mpich

# Set number of threads
START=1
END=28
for (( c=$START; c<=$END; c++ ))
do
    for 
    export OMP_NUM_THREADS=$c
    echo "Running with ${OMP_NUM_THREADS} threads."
    for k in $(seq 1 5)
    do
        ../build/bin/pi_leibniz 10000
        ../build/bin/pi_leibniz 1000000
        ../build/bin/pi_leibniz 20000000000
    done
done