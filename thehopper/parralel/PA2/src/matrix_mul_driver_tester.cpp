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
#define NUMTESTS 5
using namespace std;
using namespace std::chrono;



// // prints a usage statement and exits with code 1
// void printUsageExit(){
//     cout << "Usage:\n<path to matrix file> <path to second matrix file> <test name>\n"
//             "Matrix files should specify the number of rows followed by the number of columns, then the full matrix\n"
//             "Example matrix file:\n"
//             "4 4\n1 2 3 4\n5 6 7 8\n9 0 1 2\n\n";
//             exit(1);
// }

int main (int argc, char** argv) {
        if (argc != 4) {
            cout << "WRONG NUMBER OF ARGUMENTS\n\n";
        //     printUsageExit();
        }


        long serialTimes[5];
        long parallelTimes[5];
        Matrix first, second, result;

        for (int i = 0; i < NUMTESTS; i++){
             first = createMatrix(argv[1]);
             second = createMatrix(argv[2]);
             auto startTime = high_resolution_clock::now();
             result = multiplyMatrices(first, second);
             auto stopTime = high_resolution_clock::now();
             auto duration = duration_cast<microseconds>(stopTime - startTime);
             long dur = duration.count();
             freeMatrix(result);
             freeMatrix(first);
             freeMatrix(second);
             serialTimes[i] = dur;

        }



        for (int i = 0; i < NUMTESTS; i++){
            first = createMatrix(argv[1]);
            second = createMatrix(argv[2]);
            auto startTimePar = high_resolution_clock::now();
            Matrix resultPar = multiplyMatricesParallel(first, second);
            auto stopTimePar = high_resolution_clock::now();
            auto durationPar = duration_cast<microseconds>(stopTimePar - startTimePar);
            long dur = durationPar.count();
            freeMatrix(result);
            freeMatrix(second);
            freeMatrix(first);
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
