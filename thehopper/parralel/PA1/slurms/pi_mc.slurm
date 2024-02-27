#!/bin/bash
#SBATCH --job-name pi_mc_openmp #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 8 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p classroom # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 00:05:00 # run time. 5 minutes here.
module load gcc

# Set number of threads
export OMP_NUM_THREADS=8

echo "Running with ${OMP_NUM_THREADS} threads."

../build/bin/pi_mc 10000
../build/bin/pi_mc 1000000
../build/bin/pi_mc 200000000
