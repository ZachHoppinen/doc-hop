#!/bin/bash
export OMP_NUM_THREADS=4
../../../build/bin/matrix_mul_tester ../../../tests/test_files/Matrices/mm_50 ../../../tests/test_files/Matrices/mm_50 test-50x50