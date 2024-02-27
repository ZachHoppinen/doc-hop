/*
Multiply two matrixes using cannon's algorithm
*/

#include "matrix.h"

#ifndef CANNON_HEADER

#define CANNON_HEADER

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <math.h>

using namespace std;

typedef struct subMatrix {
    int sub_rows;
    int sub_cols;
    int* data;
    int processor_n;
} subMatrix;

void printArray(int* arr, int rows);

void cannonsInitalize(int** arr, int rows, bool B);

int* createArray(int rows);

void zeroPadArrays(int **arr1, int **arr2, int proc_per_side, int *rows);

int* recvMatrix(int src, int rows, int cols, int tag);

void sendMatrix(int* arr, int rec, int rows, int cols, int tag);

int* createZeroArray(int rows);

void multiplyMatrices(int* arr1, int* arr2, int* arr_result, int rows);

void addMatrixToResult(int* arr1, int* arr_result, int rows, int cols);

bool isPerfectSquare(int x);

void printFinalArray(int* arr, int rows, int unpadded_rows);

int* get_final_matrix(int* final, int rows, int unpadded_rows);

int* cannon(int rows, int argc, char** argv);

void swap(int* arg1, int* arg2);

void transposeArray(int* arr, int rows);

int* serial_mm (int rows);

bool matrix_compare(int* arrA, int* arrB, int rows);

#endif