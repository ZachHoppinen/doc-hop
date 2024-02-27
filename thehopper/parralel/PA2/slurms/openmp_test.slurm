#!/bin/bash
#SBATCH --job-name openmp_test #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 28 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p classroom # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 00:05:00 # run time. 5 minutes here.

# Set number of threads
export OMP_NUM_THREADS=28

echo "Running with ${OMP_NUM_THREADS} threads."

../build/bin/openmp_test
