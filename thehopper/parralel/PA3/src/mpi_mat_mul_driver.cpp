//
// Created by Camron Collinsworth on 11/12/22.
//
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <random>
#include <cmath>
#include <chrono>
#include <string>
#include "mpi.h"
#include "utilities.h"

static int N = 0; // matrix dim.  I understand that there are better ways to do this

/**
 * converts 2-d array coordinates to 1-d
 * @param i
 * @param j
 * @return
 */
int getI(int i, int j){
    return ((i * N) + j);
}

/**
 * prints out a matrix
 * @param matrix double* to matrix data
 */
void printMat(double* matrix){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", matrix[getI(i, j)]);
        }
        printf ("\n");
    }
    printf ("\n\n");
}

/**
 * creates matrix from input file
 * @param filename path to input file
 * @return
 */
double* createMat(char* filename){
    std::ifstream matrixStream(filename); // open and parse  matrix file.
    int rows, cols;

    matrixStream >> rows;
    matrixStream >> cols;
    if (!N)
        N = rows; // assume all matrices to be square

    // dynamically create matrix
    double* matrix = new double [(rows * cols)];

    //populate matrix
    double in;
    for (int i = 0; i < (rows * cols); i++) {
        matrixStream >> in;
        matrix[i] = in;
    }
    return matrix;
}


int main(int argc, char** argv){
    double* first; // matrix a
    double* second; // matrix b
    int i, j, k; // iterator variables
    double psum = 0; // store partial sum
    double start,end; // for timing
    int rank;
    int size;

    // matrix a and b
    first = createMat(argv[1]);
    second = createMat(argv[2]);

    // result matrix
    double* c = new double [(N*N)];




    // setup mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    
    // rows to be sent out with scatter
    double* firstRows = new double [(N/size)*N];    //   N/size rows and N cols
    double* cRows = new double [(N/size)*N];    //   N/size rows and N cols

    start=MPI_Wtime();


    // scatter rows of first matrix
    MPI_Scatter(first, (N*N)/size, MPI_DOUBLE, firstRows, (N*N)/size, MPI_DOUBLE,0,MPI_COMM_WORLD);
    // broadcast the second matrix
    MPI_Bcast(second, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    // perform multiplication
    for(k = 0; k < N/size; k++) { // iterate over rows
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                psum = psum + firstRows[getI(k, j)] * second[getI(j, i)];
            }
            cRows[getI(k, i)] = psum;
            psum = 0;
        }
    }

    // gather data
    MPI_Gather(cRows, (N*N)/size, MPI_DOUBLE, c, (N*N)/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD); // wait for everyone
    end=MPI_Wtime();
    MPI_Finalize();
    if(!rank) { // print matrix
        printf("%.4fs\n",end-start);
        // cleanup
        free(first);
        free(second);
        free(firstRows);
        free(c);
        free(cRows);
    }

   


}
