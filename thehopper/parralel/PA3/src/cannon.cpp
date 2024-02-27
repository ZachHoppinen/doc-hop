#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <math.h>

#include "cannon.h"

using namespace std;

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

void zeroPadArrays(int **arr1, int **arr2, int proc_per_side, int *rows){
    int cols = *rows;
    if (*rows % proc_per_side != 0){
        int pad_rows = proc_per_side * (*rows / proc_per_side + 1);
        int pad_cols = pad_rows;
        
        int* pad_arr1 = (int *) malloc(pad_rows * pad_rows * sizeof(int));
        int* pad_arr2 = (int *) malloc(pad_rows * pad_rows * sizeof(int));
        for (int i = 0; i < *rows; i++){
            for (int j =0; j < cols; j ++){
                *(pad_arr1 + i * pad_cols + j) = *((*arr1 + i * cols + j));
                *(pad_arr2 + i * pad_cols + j) = *((*arr2 + i * cols + j));
                }
            }

            for (int i = *rows; i < pad_rows; i++) {
                for (int j = cols; j < pad_cols; j++) {
                    *(pad_arr1 + i * pad_cols + j) = 0;
                    *(pad_arr2 + i * pad_cols + j) = 0;
                }
            }
        *rows = pad_rows;
        free(*arr1);
        *arr1 = pad_arr1;
        free(*arr2);
        *arr2 = pad_arr2;
    }
}

void cannonsInitalize(int** arr, int rows, bool B){
    int shift;
    int cols = rows;
    int* arr_init = (int*) malloc(rows * cols * sizeof(int));
    if (B == true){
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                shift = (i + j) % rows;
                *(arr_init + i * cols + j) = *((*arr + (shift) * cols + j));
            }
        }
    }
    else{
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                shift = (j + i) % rows;
                *(arr_init + i * cols + j) = *((*arr + i * cols + shift));
            }
        }
    }
    free(*arr);
    *arr = arr_init;
}

int* createZeroArray(int rows){
    int cols = rows;
    int c = 0;
    int* arr = (int*) malloc(rows* rows * sizeof(int));
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
                    *(arr_result + i * cols + j) += *(arr1 + i * cols + k) * *(arr2 + k * cols + j);
                }
            }
        }
    }

void addMatrixToResult(int* arr1, int* arr_result, int rows, int cols){
    int index;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
                index = i * cols + j;
                arr_result[index] += arr1[index];
            }
        }
    }

bool isPerfectSquare(int x){
    // Find floating point value of
    // square root of x.
    if (x >= 0) {
 
        long long sr = sqrt(x);
         
        return (sr * sr == x);
    }
    return false;
}

void printFinalArray(int* arr, int rows, int unpadded_rows){
    int cols = rows;
    // Traverse the 2D array
    for (int i = 0; i < unpadded_rows; i++) {
        for (int j = 0; j < unpadded_rows; j++) {
 
            // Print values of the
            // memory block
            printf("%d ", *(arr + i * rows + j));
        }
        printf("\n");
    }
    printf("\n");
}

int* get_final_matrix(int* final, int rows, int unpadded_rows){
    int cols = rows;
    int* unpadded_arr = (int*) malloc( rows* cols* sizeof(int));
    // Traverse the 2D array
    for (int i = 0; i < unpadded_rows; i++) {
        for (int j = 0; j < unpadded_rows; j++) {
 
            // Print values of the
            // memory block
            *(unpadded_arr + i * unpadded_rows + j) =  *(final + i * rows + j);
        }
    }
    return unpadded_arr;
}

int* cannon(int rows, int argc, char** argv){
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    int unpadded_rows = rows;

    int* arrA;
    int* arrB;
    double start,end;
    MPI_Status status;

    // Find out rank, size
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int* final;
    if (isPerfectSquare(world_size) == 0){
        printf("n_processors must be perfect square.\n");
        MPI_Finalize();
        return final;
    }
    // Create 2 dimensional grid of processors and find neighbors
    int dims[2];
    int period[2] = {1,1};
    dims[0]=0; dims[1]=0;
    // Create MPI_dims matching number of processors
    MPI_Dims_create(world_size, 2, dims);
    MPI_Comm PROC_GRID;
    // Create new processor with 2d grid
    MPI_Cart_create(MPI_COMM_WORLD,2,dims,period,1,&PROC_GRID);
    int left,right,up,down;
    // Find neighbors for each processor
    // 0 = direction/axis, 1 = displacement.
    MPI_Cart_shift(PROC_GRID,1,1,&left,&right);
    MPI_Cart_shift(PROC_GRID,0,1,&up,&down);
    int cart_rank;
    MPI_Comm_rank(PROC_GRID, &cart_rank);

    if (my_rank == 0) {
        arrA = createArray(rows);
        arrB = createArray(rows);
        zeroPadArrays(&arrA, &arrB, dims[0], &rows);
        // printArray(arrA, rows);
    }
    // Start timing
    MPI_Barrier(MPI_COMM_WORLD);
    start=MPI_Wtime();

    int rank_rows = rows/dims[0];

    MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&rank_rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // Get displacements and counts for scatter
    int scounts[world_size];
    int displs[world_size];
    MPI_Datatype sub_arr, type;
    int sizes[2] = {rows, rows};
    int subsizes[2] = {rank_rows, rank_rows};
    int starts[2] = {0,0};

    // Create MPI data type to hold subarrays
    MPI_Type_create_subarray(2, sizes, subsizes, starts, 
                                MPI_ORDER_C, MPI_INT, &sub_arr);
    // // Resize sub array to correct extent
    MPI_Type_create_resized(sub_arr, 0, rank_rows*sizeof(int), &type);
    MPI_Type_commit(&type);
    // calculate displacements for subarrays
    for (int i=0; i<world_size; i++){
        scounts[i] = 1;
        displs[i] = i/dims[0] * rank_rows * dims[0]+ i%dims[0];
    }

    // scatter sub arrays
    int* la = (int *) malloc(rank_rows * rank_rows * sizeof(int));
    MPI_Scatterv(arrA, scounts, displs, type, la, (rank_rows*rank_rows), MPI_INT, 0, MPI_COMM_WORLD);
    int* lb = (int *) malloc(rank_rows * rank_rows * sizeof(int));
    MPI_Scatterv(arrB, scounts, displs, type, lb, (rank_rows*rank_rows), MPI_INT, 0, MPI_COMM_WORLD);

    // initalize arrays
    int left_ith, right_ith;
    int up_ith, down_ith;
    MPI_Cart_shift(PROC_GRID,1,my_rank/dims[0],&left_ith,&right_ith);
    MPI_Cart_shift(PROC_GRID,0,my_rank%dims[0],&up_ith,&down_ith);
    // if (my_rank == 0) printArray(lb, rank_rows);
    int *buf = (int *) malloc(rank_rows * rank_rows * sizeof(int)); 
    int *tmp = (int *) malloc(rank_rows * rank_rows * sizeof(int));;
    if (left_ith != right_ith){
        if (my_rank%dims[0] == 0){
            MPI_Send(la, rank_rows*rank_rows, MPI_INT, left_ith, 0, MPI_COMM_WORLD);
            MPI_Recv(buf, rank_rows*rank_rows, MPI_INT, right_ith, 0, MPI_COMM_WORLD, &status);
        }
        else{
            MPI_Recv(buf, rank_rows*rank_rows, MPI_INT, right_ith, 0, MPI_COMM_WORLD, &status);
            MPI_Send(la, rank_rows*rank_rows, MPI_INT, left_ith, 0, MPI_COMM_WORLD);
        }
        tmp=buf; buf=la; la=tmp;
    }
    if (up_ith != down_ith){
        if (my_rank < dims[0]){
            MPI_Send(lb, rank_rows*rank_rows, MPI_INT, up_ith, 0, MPI_COMM_WORLD);
            MPI_Recv(buf, rank_rows*rank_rows, MPI_INT, down_ith, 0, MPI_COMM_WORLD, &status);
        }
        else{
            MPI_Recv(buf, rank_rows*rank_rows, MPI_INT, down_ith, 0, MPI_COMM_WORLD, &status);
            MPI_Send(lb, rank_rows*rank_rows, MPI_INT, up_ith, 0, MPI_COMM_WORLD);
        }
        tmp=buf; buf=lb; lb=tmp;
    }

    // loop through and step arrays through all sequences
    int* lr = createZeroArray(rank_rows);
    
    for (int step = 0; step < dims[0]; step++){
        // dot multiply and add to local result
        multiplyMatrices(la, lb, lr, rank_rows);
        // Send matrix to next processor
        if(step==dims[0]-1) break;
        if (my_rank %dims[0] == 0){
            MPI_Send(la, rank_rows*rank_rows, MPI_INT, left, 0, MPI_COMM_WORLD);
            MPI_Recv(buf, rank_rows*rank_rows, MPI_INT, right, 0, MPI_COMM_WORLD, &status);
        }
        else{
            MPI_Recv(buf, rank_rows*rank_rows, MPI_INT, right, 0, MPI_COMM_WORLD, &status);
            MPI_Send(la, rank_rows*rank_rows, MPI_INT, left, 0, MPI_COMM_WORLD);
        }
        tmp=buf; buf=la; la=tmp;
        if (my_rank < dims[0]){
            MPI_Send(lb, rank_rows*rank_rows, MPI_INT, up, 0, MPI_COMM_WORLD);
            MPI_Recv(buf, rank_rows*rank_rows, MPI_INT, down, 0, MPI_COMM_WORLD, &status);
        }
        else{
            MPI_Recv(buf, rank_rows*rank_rows, MPI_INT, down, 0, MPI_COMM_WORLD, &status);
            MPI_Send(lb, rank_rows*rank_rows, MPI_INT, up, 0, MPI_COMM_WORLD);
        }
        tmp=buf; buf=lb; lb=tmp;
    }
    // receive local arrays to main
    // combine and remove zeros
    if ( my_rank == 0) final = (int *)malloc(rows*rows*sizeof(int));
    for (int i=0; i<world_size; i++){
        scounts[i] = rank_rows;
        displs[i] = i/dims[0] * rank_rows * dims[0]+ i%dims[0];
    }

    MPI_Gatherv(lr, rank_rows*rank_rows, MPI_INT,
            final, scounts, displs, type, 0, MPI_COMM_WORLD);
    end = MPI_Wtime();
    if ( my_rank == 0 && unpadded_rows < 30) printFinalArray(final, rows, unpadded_rows);
    if (my_rank==0){
        printf("Time: %.4fs\n",end-start);
        int *final_unpadded;
        final_unpadded = get_final_matrix(final, rows, unpadded_rows);
        return final_unpadded;
    }
    // Free
    free(la);
    free(lb);
    free(lr);
    if (my_rank == 0) {
        free(arrA);
        free(arrB);
        free(final);
    }
    // MPI_Finalize();
    return final;
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

bool matrix_compare(int* arrA, int* arrB, int rows){
    for (int i = 0; i < rows; i ++){
        for (int j = 0; j < rows; j ++){
            if (arrA[i * rows + j] != arrB[i*rows + j]) return false;
        }
    }
    return true;
}