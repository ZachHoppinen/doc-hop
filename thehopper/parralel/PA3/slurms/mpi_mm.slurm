#!/bin/bash

#SBATCH -J matrix_mul_mpi
#SBATCH -o logs/mm_mpi.o%j
#SBATCH -n 28
#SBATCH -N 1
#SBATCH -p classroom
#SBATCH -t 01:00:00
module load slurm
module load gcc
module load openmpi/gcc-6/1.10.3

export OMPI_MCA_mca_base_component_show_load_errors=0

echo "--------SMALL------"
echo "2 nodes"
mpirun -np 2 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Matrices/mm_Small
echo "4 nodes"
mpirun -np 4 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Matrices/mm_Small
echo "8 nodes"
mpirun -np 8 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Matrices/mm_Small
echo "12 nodes"
mpirun -np 12 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Matrices/mm_Small
echo "16 nodes"
mpirun -np 16 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Matrices/mm_Small
echo "24 nodes"
mpirun -np 24 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Small ../tests/test_files/Matrices/mm_Small
echo "--------------------"
echo "------MEDIUM-------"
echo "2 nodes"
mpirun -np 2 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Matrices/mm_Medium
echo "4 nodes"
mpirun -np 4 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Matrices/mm_Medium
echo "8 nodes"
mpirun -np 8 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Matrices/mm_Medium
echo "10 nodes"
mpirun -np 10 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Matrices/mm_Medium
echo "16 nodes"
mpirun -np 16 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Matrices/mm_Medium
echo "25 nodes"
mpirun -np 25 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Medium ../tests/test_files/Matrices/mm_Medium
echo "--------------------"
echo "------Large-------"
echo "2 nodes"
mpirun -np 2 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Matrices/mm_Large
echo "4 nodes"
mpirun -np 4 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Matrices/mm_Large
echo "8 nodes"
mpirun -np 8 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Matrices/mm_Large
echo "12 nodes"
mpirun -np 12 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Matrices/mm_Large
echo "16 nodes"
mpirun -np 16 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Matrices/mm_Large
echo "24 nodes"
mpirun -np 24 ../build/bin/mpi_matrix_mul ../tests/test_files/Matrices/mm_Large ../tests/test_files/Matrices/mm_Large
echo "--------------------"



