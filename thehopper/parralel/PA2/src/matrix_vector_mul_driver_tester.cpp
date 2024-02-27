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
#define NUMTESTS 5
using namespace std;
using namespace std::chrono;

bool verbose = false;
double **matrix1;


// // print usage and exit with error code
// void printUsageExit(){
//     cout << "Usage:\n<path to matrix file> <path to vector file> <test name>\n"
//             "Matrix files should specify the number of rows followed by the number of columns, then the full matrix\n"
//             "Vector files should specify the vector size on the first line followed by the vector\n"
//             "Example matrix file:\n"
//             "3 4\n1 2 3 4\n5 6 7 8\n9 0 1 2\n\n"
//             "Example vector file:"
//             "4\n1\n2\n3\n4\n\n";
//     exit(1);
// }

int main(int argc, char** argv) {

    if (argc != 4) {
        cout << "WRONG NUMBER OF ARGUMENTS\n\n";
        // printUsageExit();
    }

    long serialTimes[5];
    long parallelTimes[5];
    Matrix first;
    Vector second, result;

    for (int i = 0; i < NUMTESTS; i++){
        first = createMatrix(argv[1]);
        second = createVector(argv[2]);
        auto startTime = high_resolution_clock::now();
        result =  multiplyMatVect(first, second);
        auto stopTime = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stopTime - startTime);
        long dur = duration.count();
        serialTimes[i] = dur;

    }



    for (int i = 0; i < NUMTESTS; i++){
        first = createMatrix(argv[1]);
        second = createVector(argv[2]);
        auto startTimePar = high_resolution_clock::now();
        Vector resultPar =  multiplyMatVectParallel(first, second);
        auto stopTimePar = high_resolution_clock::now();
        auto durationPar = duration_cast<microseconds>(stopTimePar - startTimePar);
        long dur = durationPar.count();
        parallelTimes[i] = dur;
    }

    cout << argv[3] << " " << "serial times:\n";
    double avgTime = 0;
    for (int i = 0; i < NUMTESTS; i++){
        cout << serialTimes[i] << "\n";
        avgTime += serialTimes[i];
    }
    avgTime /= NUMTESTS;
    cout << "Average: " << avgTime;
    cout << "\nparallel times:\n";
    avgTime = 0;
    for (int i = 0; i < NUMTESTS; i++){
        cout << parallelTimes[i] << "\n";
        avgTime += parallelTimes[i];
    }
    avgTime /= NUMTESTS;
    cout << "Average: " << avgTime;
    cout << "\n\n";

    return 0;
}