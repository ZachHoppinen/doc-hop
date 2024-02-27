#!/bin/bash
export OMP_NUM_THREADS=12
../../../build/bin/matrix_mul_tester ../../../tests/test_files/Matrices/mm_100 ../../../tests/test_files/Matrices/mm_100 test-100x100