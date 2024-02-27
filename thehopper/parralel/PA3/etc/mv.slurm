#!/bin/bash

#SBATCH -J matrix_mul_mpi
#SBATCH -o mv_serial.o%j
#SBATCH -n 1
#SBATCH -N 1
#SBATCH -p classroom
#SBATCH -t 01:00:00
module load slurm
module load gcc
module load openmpi/gcc-6/1.10.3

./mv.out 240
./mv.out 1600
./mv.out 4800