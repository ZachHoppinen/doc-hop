#!/bin/bash
#SBATCH --job-name mpi_test #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 10 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p classroom # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 00:05:00 # run time. 5 minutes here.

module load gcc
module load openmpi/gcc/64/1.10.7

mpirun ../build/bin/mpi_test
