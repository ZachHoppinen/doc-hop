#!/bin/bash
#SBATCH -J mpi_m_v_multiply
#SBATCH -o logs/mvm_mpi.o%j
#SBATCH -n 28
#SBATCH -N 1
#SBATCH -p classroom
#SBATCH -t 01:00:00

module load slurm
module load gcc
module load openmpi/gcc/64/1.10.7

echo "--------SMALL------"
echo "2 nodes"
mpirun -np 2 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Vectors/v_Small
echo "4 nodes"
mpirun -np 4 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Vectors/v_Small
echo "8 nodes"
mpirun -np 8 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Vectors/v_Small
echo "12 nodes"
mpirun -np 12 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Vectors/v_Small
echo "16 nodes"
mpirun -np 16 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Vectors/v_Small
echo "24 nodes"
mpirun -np 24 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Vectors/v_Small
echo "--------------------"
echo "------MEDIUM-------"
echo "2 nodes"
mpirun -np 2 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Vectors/v_Medium
echo "4 nodes"
mpirun -np 4 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Vectors/v_Medium
echo "8 nodes"
mpirun -np 8 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Vectors/v_Medium
echo "12 nodes"
mpirun -np 12 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Vectors/v_Medium
echo "16 nodes"
mpirun -np 16 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Vectors/v_Medium
echo "24 nodes"
mpirun -np 24 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Vectors/v_Medium
echo "--------------------"
echo "------Large-------"
echo "2 nodes"
mpirun -np 2 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Vectors/v_Large
echo "4 nodes"
mpirun -np 4 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Vectors/v_Large
echo "8 nodes"
mpirun -np 8 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Vectors/v_Large
echo "12 nodes"
mpirun -np 12 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Vectors/v_Large
echo "16 nodes"
mpirun -np 16 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Vectors/v_Large
echo "24 nodes"
mpirun -np 24 ../build/bin/mpi_matrix_vector_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Vectors/v_Large
echo "--------------------"
