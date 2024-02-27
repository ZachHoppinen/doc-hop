#!/bin/bash
#SBATCH --job-name m_v_multiply #job name
#SBATCH -o logs/%x-%j.log # output and error file name (%j expands to jobID)
#SBATCH --ntasks-per-node 8 # number of tasks requested (threads?)
#SBATCH --nodes 1 # number of nodes you want to run on
#SBATCH -p classroom # queue to join - defq, eduq, gpuq, shortq
#SBATCH -t 00:05:00 # run time. 5 minutes here.
module load gcc

# Set number of threads
export OMP_NUM_THREADS=8

echo "Running with ${OMP_NUM_THREADS} threads."

../build/bin/matrix_vector_mul ../tests/test_files/Matrices/mm_50 ../tests/test_files/Vectors/v_50
../build/bin/matrix_vector_mul ../tests/test_files/Matrices/mm_500 ../tests/test_files/Vectors/v_500
../build/bin/matrix_vector_mul ../tests/test_files/Matrices/mm_1000 ../tests/test_files/Vectors/v_1000
