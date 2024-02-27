#include <chrono>
#include <iostream>
#include "fib.h"
#include <omp.h>
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Incorrect number of arguments\n";
        return -1;
    }

    int n = atoi(argv[1]);


    auto startTime = high_resolution_clock::now();

    #pragma omp parallel shared(n)
    {
	#pragma omp single
	 cout << n <<"th Fibonacchi Number is " << calc_fib(n) << "\n"; 

    }

    auto stopTime = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    return 0;
}
