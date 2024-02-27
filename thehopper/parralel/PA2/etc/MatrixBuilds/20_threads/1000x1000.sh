#!/bin/bash
export OMP_NUM_THREADS=20
../../../build/bin/matrix_mul_tester ../../../tests/test_files/Matrices/mm_1000 ../../../tests/test_files/Matrices/mm_1000 test-1000x1000
../../../build/bin/matrix_mul_tester ../../../tests/test_files/Matrices/mm_1000 ../../../tests/test_files/Matrices/mm_1000 test-1000x1000