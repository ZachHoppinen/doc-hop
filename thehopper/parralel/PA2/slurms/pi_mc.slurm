#!/bin/bash
#SBATCH --job-name pi_mc_openmp #job name
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
for (( c=$START; c<=$END; c += 6 ))
do
    export OMP_NUM_THREADS=$c
    echo "Running with ${OMP_NUM_THREADS} threads."
        ../build/bin/pi_mc 10000
        ../build/bin/pi_mc 1000000
        ../build/bin/pi_mc 20000000000
done