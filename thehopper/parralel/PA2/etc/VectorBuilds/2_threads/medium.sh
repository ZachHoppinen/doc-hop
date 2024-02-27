#!/bin/bash
export OMP_NUM_THREADS=2
../../../build/bin/matrix_vector_mul_tester ../../../tests/test_files/Matrices/mv_mediun ../../../tests/test_files/Vectors/v_medium test-mv_medium