#include <chrono>
#include <iostream>
#include "fib.h"
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Incorrect number of arguments\n";
        return -1;
    }

    int n = atoi(argv[1]);

    cout << "Calculating the number in place " << n << " of the Fibonnaci Sequence\n";


    auto startTime = high_resolution_clock::now();

    int result = calc_fib(n);

    auto stopTime = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stopTime - startTime);


    cout << "Fibonnaci Number: " << result << "\n";
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    return 0;
}