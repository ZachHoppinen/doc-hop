/* Calculate pi with monte carlo technique
 https://blogs.sas.com/content/iml/2016/03/14/monte-carlo-estimates-of-pi.html

Usage: pi_mc.cpp [number_terms]

arguments:
    number_terms (optional): number of random observations to compare [default: 1000]
*/
#include <chrono>
#include "utilities.h"
#include "pi_mc.h"
using namespace std;
using namespace std::chrono;


int main (int argc, char *argv[]){
    // Parsing input values
    long n = strtol(argv[1], NULL, 0);
    // Setting cout floating-point format
    cout.precision(20);

    cout << "Calculating pi using the monte carlo technique with " << n << " values\n";

    // start timer
    auto startTime = high_resolution_clock::now();

    // Calculate a guess for pi using number of terms.
    auto guess = calc_pi_mc(n);

    auto stopTime  = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stopTime - startTime);


    float diff = guess - M_PI;

    // report accuracy and time taken.
    cout << "Current pi guess: " << guess << "\n";
    cout << "Difference to real value " << diff << "\n";
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    return 0;
}