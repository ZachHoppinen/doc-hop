#!/bin/bash
#SBATCH --job-name m_multiply #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 4 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p classroom # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 00:05:00 # run time. 5 minutes here.

module load gcc
module load openmpi/gcc/64/1.10.7

# Give serial first
g++ ../etc/mm.cpp -o ../etc/mm
echo "---------Serial---------------"
./mm 240
./mm 1600
./mm 4800

mpirun ../build/bin/matrix_mul ../tests/test_files/Matrices/mm_50 ../tests/test_files/Matrices/mm_50
mpirun ../build/bin/matrix_mul ../tests/test_files/Matrices/mm_500 ../tests/test_files/Matrices/mm_500
mpirun ../build/bin/matrix_mul ../tests/test_files/Matrices/mm_1000 ../tests/test_files/Matrices/mm_1000
