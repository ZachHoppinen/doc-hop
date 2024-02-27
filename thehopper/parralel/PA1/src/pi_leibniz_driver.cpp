/* Calculate pi with Leibniz Series

Usage: pi_leibniz.cpp [number_terms]

arguments:
    number_terms (optional): number of leibniz terms to use [default: 1000]
*/

#include <iostream>
#include <chrono>
#include "pi_leibniz.h"
#include "utilities.h"
using namespace std;
using namespace std::chrono;

int main (int argc, char *argv[]){
    // Parsing input values
    long n = strtol(argv[1], NULL, 0);
    // Setting cout floating-point format
    cout.precision(20);
    
    cout << "Calculating pi using Leibniz series with " << n << " values.\n";

    // start timer
    auto startTime = high_resolution_clock::now();

    // Calculate a guess for pi using number of terms.
    float guess = calc_pi_leibniz(n);

    auto stopTime = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    float diff = guess - M_PI;

    // report accuracy and time taken.
    cout << "Current pi guess: " << guess << "\n";
    cout << "Difference to real value " << diff << "\n";
    cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;

    return 0;
}