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

void swap(int* arg1, int* arg2)
{
    int buffer = *arg1;
    *arg1 = *arg2;
    *arg2 = buffer;
}

void transposeArray(int* arr, int rows){
    int cols = rows;
    for (int i = 0; i < rows; i++){
	   for (int j = i+1; j < cols; j ++){
		    swap(arr + i * cols + j, arr + j * cols + i);
	    }
    }
}

int* serial_mm (int rows){
    int *arrA, *arrB, *arrR;
    arrA = createArray(rows);
    arrB = createArray(rows);
    transposeArray(arrB, rows);
    arrR = createZeroArray(rows);
    clock_t start, duration;
    start = clock();
    multiplyMatrices(arrA, arrB, arrR, rows);
    duration = clock() - start;
    printf("Serial run time: %f seconds\n", ((double)duration)/CLOCKS_PER_SEC);
    free(arrA);
    free(arrB);
    return arrR;
}

int main(int argc, char** argv){
    
    int rows;
    if (argc == 2) rows = atoi(argv[1]);
    else return -1;

    int *arrR;

    arrR = serial_mm(rows);
    if (rows < 30) printArray(arrR, rows);

    free(arrR);
    return 0;
}