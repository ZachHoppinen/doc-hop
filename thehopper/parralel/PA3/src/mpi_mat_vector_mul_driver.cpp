/**
 * MPI program for Matrix-Vector multiplication.
 * Created for use in CS430 P3 Fall 2022
 *
 * @author Logan Hurd
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include "mpi.h"
#include "matrix.h"
#include "utilities.h"


const int ROOT = 0;
static int N = 0;

void printUsageExit() {
    cout << "Usage:\n<path to matrix file> <path to vector file>\n"
        "Matrix files should specify the number of rows followed by the number of columns, then the full matrix\n"
        "Vector files should specify the vector size on the first line followed by the vector\n";
    exit(1);
}




double* createMat(char* filename){
    std::ifstream matrixStream(filename); // open and parse  matrix file.
    int rows, cols;

    matrixStream >> rows;
    matrixStream >> cols;
    if (!N)
        N = rows; // assume all matrices to be square

    // dynamically create matrix
    double* matrix = new double[(rows * cols)];

    //populate matrix
    double in;
    for (int i = 0; i < (rows * cols); i++) {
        matrixStream >> in;
        matrix[i] = in;
    }
    matrixStream.close();
    return matrix;
}

int main(int argc, char** argv)
{
    double* rowsToEvaluate;
    int numRowsToEvaluate = 0;
    int* numRowsToEvaluatePtr = &numRowsToEvaluate;
    double* vectorTable;
    double* matrixTable;
    int cols = 0;
    int rows = 0;
    int* colsPtr = &cols;
    double* processResult;
    double* result;
    int processorNum;
    int myRank;
    int* lengthRowstoSend;
    int* numRowstoRecieve;
    int* scattervDisplacement;
    int* gathervDisplacement;
    Vector myVector;
    std::chrono::high_resolution_clock::time_point startTime;



    MPI_Init(&argc, &argv);

    // Who am I?
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    // How many of us are there?
    MPI_Comm_size(MPI_COMM_WORLD, &processorNum);


    // Announcing Startup
    //cout << "\nProcess " << myRank << " starting up.\n";

    // Root process does some startup work
    if (myRank == ROOT) {
        char* matrixFile = argv[argc - 2];
        char* vectorFile = argv[argc - 1];
        //cout << "\n";
        //cout << "Multiplying Matrix " << matrixFile << " and Vector " << vectorFile << "\n";
        //cout << "\tNumber of processes: " << processorNum << "\n";


        matrixTable = createMat(matrixFile);
        cols = N;
        rows = N;
        myVector = createVector(vectorFile);
        
        startTime = std::chrono::high_resolution_clock::now();
    }

    
    // Telling everyone the matrix's number of columns
    MPI_Bcast(colsPtr, 1, MPI_INT, ROOT, MPI_COMM_WORLD);


    // Creating local vectorTable
    vectorTable = (double*)malloc(sizeof(double) * cols);
    if (myRank == ROOT) {
        for (int i = 0; i < cols; i++) {
            vectorTable[i] = myVector.table[i];
        }
        freeVector(myVector);
    }
    
    // Giving everyone a copy of the vector table
    MPI_Bcast(vectorTable, cols, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);


    // Calculating number of rows to send/recieve and setting displacement amounts
    if (myRank == ROOT) {
        int baseNum = rows / processorNum;
        int remainder = rows % processorNum;
        lengthRowstoSend = new int[processorNum];
        numRowstoRecieve = new int[processorNum];
        scattervDisplacement = new int[processorNum];
        gathervDisplacement = new int[processorNum];
        int total = 0;
        for (int i = 0; i < processorNum; i++) {
            numRowstoRecieve[i] = baseNum;
            if (i < remainder) 
                numRowstoRecieve[i]++;
            gathervDisplacement[i] = total;
            scattervDisplacement[i] = total * cols;
            lengthRowstoSend[i] = numRowstoRecieve[i] * cols;
            total += numRowstoRecieve[i];
        }
    }

    
    // Telling everyone how many rows they're getting then giving them the rows
    MPI_Scatter(lengthRowstoSend, 1, MPI_INT, 
                numRowsToEvaluatePtr, 1, MPI_INT, 
                ROOT, MPI_COMM_WORLD);
    //cout << "I expect " << *numRowsToEvaluatePtr << " numbers.\n";
    rowsToEvaluate = (double*)malloc(sizeof(double) * *numRowsToEvaluatePtr);
    MPI_Scatterv(matrixTable, lengthRowstoSend, scattervDisplacement, MPI_DOUBLE, 
                 rowsToEvaluate, *numRowsToEvaluatePtr, MPI_DOUBLE, 
                 ROOT, MPI_COMM_WORLD);
    if (myRank == ROOT) { free(matrixTable); free(lengthRowstoSend); }

    
    //cout << "doing math\n";
    //doMultiplication();
    processResult = new double[(*numRowsToEvaluatePtr / cols)];
    //cout << (*numRowsToEvaluatePtr / cols) << "\n";
    for (int i = 0; i < (*numRowsToEvaluatePtr / cols); i++) {
        double rowResult = 0;
        for (int j = 0; j < cols; j++) {
            rowResult += vectorTable[j] * rowsToEvaluate[(i * cols) + j];
        }
        processResult[i] = rowResult;
    }
    free(rowsToEvaluate);
    free(vectorTable);
    

    // Gathering final result
    if (myRank == ROOT) {
        result = (double *)malloc(sizeof(double) * rows);
    }
    MPI_Gatherv(processResult, (*numRowsToEvaluatePtr / cols), MPI_DOUBLE,
                result, numRowstoRecieve, gathervDisplacement, MPI_DOUBLE,
                ROOT, MPI_COMM_WORLD);
    free(processResult);
    
    // Root prints result and frees memory
    if (myRank == ROOT) {
        Vector endVector;
        endVector.size = rows;
        endVector.table = result;

        auto stopTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

        //cout << "Resulting Vector:\n";
        //printVector(endVector);
        cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

        
        freeVector(endVector);
        free(result);
    }

    // Announcing Finish
    // cout << "\nProcess " << myRank << " is finished.\n";

    MPI_Finalize();
    return 0;
}

