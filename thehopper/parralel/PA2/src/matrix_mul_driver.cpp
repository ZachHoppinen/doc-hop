/*
Created by Camron Collinsworth on 9/1/22.
a program to perform matrix multiplication between two valid matrices that can be multiplied together.
both matrices are provided via a text file. The first line of the text file must specify the
dimensions of both matrices. The rest of the text file must contain only the matrix to be multiplied.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include "utilities.h"
using namespace std;
using namespace std::chrono;



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



    cout << "Multiplying Matrices in serial " << argv[1] << ", " << argv[2] << "\n";

    Matrix first = createMatrix(argv[1]);
    Matrix second = createMatrix(argv[2]);
    auto startTime = high_resolution_clock::now();
    Matrix result = multiplyMatrices(first, second);
    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);


    cout << "Resulting Matrix (serial):\n";
    printMatrix(result);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
    freeMatrix(result);
    freeMatrix(first);
    freeMatrix(second);
    cout << "\n\n";


    cout << "Multiplying Matrices in parallel " << argv[1] << ", " << argv[2] << "\n";

    first = createMatrix(argv[1]);
    second = createMatrix(argv[2]);
    auto startTimePar = high_resolution_clock::now();
    Matrix resultPar = multiplyMatricesParallel(first, second);
    auto stopTimePar = high_resolution_clock::now();
    auto durationPar = duration_cast<microseconds>(stopTimePar - startTimePar);


    cout << "Resulting Matrix:\n";
    printMatrix(result);
    cout << "Time taken by function: " << durationPar.count() << " microseconds" << endl;
    freeMatrix(result);
    freeMatrix(second);
    freeMatrix(first);
    auto serialTime = stopTime - startTime;
    auto parallelTime = stopTimePar - startTimePar;

    if( serialTime < parallelTime){
        cout << "Serial is Faster!\n";

    }
    else{
        cout << "Parallel is Faster!\n";
    }

    cout << "Serial: " << serialTime.count() << "\n";
    cout << "Parallel: " << parallelTime.count() << "\n";

    return 0;
}
