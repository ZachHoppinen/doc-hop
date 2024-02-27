/*
Created by Camron Collinsworth on 9/1/22.
a program to perform matrix multiplication between two valid matrices that can be multiplied together.
both matrices are provided via a text file. The first line of the text file must specify the
dimensions of both matrices. The rest of the text file must contain only the matrix to be multiplied.
*/
#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include "utilities.h"
using namespace std;
using namespace std::chrono;


bool verbose = false;

// prints a message if in verbose mode
void print(string message){
    if(verbose){
        cout << message << "\n";
    }
}

// prints a usage statement and exits with code 1
void printUsageExit(){
    cout << "Usage:\n<path to matrix file> <path to second matrix file>\n"
            "Matrix files should specify the number of rows followed by the number of columns, then the full matrix\n"
            "Example matrix file:\n"
            "4 4\n1 2 3 4\n5 6 7 8\n9 0 1 2\n\n";
            exit(1);
}

int main (int argc, char** argv) {
        if (argc != 3) {
            cout << "WRONG NUMBER OF ARGUMENTS\n\n";
            printUsageExit();
        }



    cout << "Multiplying Matrices " << argv[1] << ", " << argv[2] << "\n";


    auto startTime = high_resolution_clock::now();

    Matrix result = runMatrixMult(argv[1], argv[2]);

    auto stopTime = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stopTime - startTime);


    cout << "Resulting Matrix:\n";
    printMatrix(result);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
    freeMatrix(result);

    return 0;
}