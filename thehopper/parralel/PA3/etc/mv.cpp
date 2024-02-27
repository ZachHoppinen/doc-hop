#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <math.h>

int* createArray(int rows){
    int cols = rows;
    int c = 0;
    int* arr = (int*) malloc(rows* cols * sizeof(int));
    for (int i = 0; i < rows; i++){
	   for (int j =0; j < cols; j ++){
		*(arr + i * cols + j) = ++c;
	    }
    }
    return arr;
}

int* createVector(int rows){
    int c = 0;
    int* arr = (int*) malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++){
		*(arr + i ) = ++c;
	}
    return arr;
}

int* createZeroArray(int rows){
    int cols = rows;
    int c = 0;
    int* arr = (int*) malloc(rows* cols * sizeof(int));
    for (int i = 0; i < rows; i++){
	   for (int j =0; j < cols; j ++){
		*(arr + i * cols + j) = c;
	    }
    }
    return arr;
}

void multiplyMatrices(int* arr1, int* arr2, int* arr_result, int rows){
    int cols = rows;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
                for (int k = 0; k < rows; k++){
                    // assume array is tranposed
                    *(arr_result + i * cols + j) += *(arr1 + i * cols + k) * *(arr2 + j * cols + k);
                }
            }
        }
    }

void multiplyMatrixVector(int* arr1, int* vecB, int* arr_result, int rows){
    int cols = rows;
    for (int i = 0; i < rows; i++){
            for (int k = 0; k < rows; k++){
                *(arr_result + i) += *(arr1 + i * cols + k) * *(vecB + k);
            }
        }
    }

void printArray(int* arr, int rows){
    int cols = rows;
    // Traverse the 2D array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
 
            // Print values of the
            // memory block
            printf("%d ", *(arr + i * cols + j));
        }
        printf("\n");
    }
    printf("\n");
}

void printVector(int* vector, int rows){
    // Traverse the 1D array
    for (int i = 0; i < rows; i++) {
        // Print values of the
        // memory block
        printf("%d ", *(vector + i));
    }
    printf("\n");
}

int* serial_mv (int rows){
    int *arrA, *vecB, *arrR;
    arrA = createArray(rows);
    vecB = createVector(rows);
    clock_t start, duration;
    start = clock();
    arrR = createZeroArray(rows);
    multiplyMatrixVector(arrA, vecB, arrR, rows);
    duration = clock() - start;
    printf("Serial run time: %.15f seconds\n", ((double)duration)/CLOCKS_PER_SEC);
    free(arrA);
    free(vecB);
    return arrR;
}

int main(int argc, char** argv){
    
    int rows;
    if (argc == 2) rows = atoi(argv[1]);
    else return -1;

    int *arrR;

    arrR = serial_mv(rows);
    if (rows < 30) printVector(arrR, rows);

    free(arrR);
    return 0;
}