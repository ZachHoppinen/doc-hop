/*
Created by Camron Collinsworth on 9/1/22.
This is a program that will multiple a valid vector by a valid matrix.
Both a matrix and a vector are provided by their own text file with their dimension specified on the first line.
*/

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <chrono>
#include "utilities.h"
using namespace std;
using namespace std::chrono;

bool verbose = false;
double **matrix1;


// print usage and exit with error code
void printUsageExit(){
    cout << "Usage:\n<path to matrix file> <path to vector file>\n"
            "Matrix files should specify the number of rows followed by the number of columns, then the full matrix\n"
            "Vector files should specify the vector size on the first line followed by the vector\n"
            "Example matrix file:\n"
            "3 4\n1 2 3 4\n5 6 7 8\n9 0 1 2\n\n"
            "Example vector file:"
            "4\n1\n2\n3\n4\n\n";
    exit(1);
}

int main(int argc, char** argv) {

    if (argc != 3) {
        cout << "WRONG NUMBER OF ARGUMENTS\n\n";
        printUsageExit();
    }




    cout << "Multiplying Matrix " << argv[1] << " and Vector " << argv[2] << "\n";


    auto startTime = high_resolution_clock::now();

    Vector result = runVectMatrixMult(argv[1], argv[2]);

    auto stopTime = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stopTime - startTime);


    cout << "Resulting Vector:\n";
    printVector(result);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
    freeVector(result);

    return 0;
}