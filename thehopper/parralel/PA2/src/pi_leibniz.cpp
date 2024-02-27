/* Calculate pi with Leibniz Series

Usage: pi_leibniz.cpp [number_terms]

arguments:
    number_terms (optional): number of leibniz terms to use [default: 1000]
*/

#include <math.h>
#include <iostream>
#include <omp.h>
using namespace std;

float calc_pi_leibniz( long n){

    if (n < 1){
        cout << "Invalid number of terms provided: " << n << "\n";
        return -1;
    }

    float pi = 1;
    float d;
    float guess;

    for (unsigned long long i = 0; i < n; i++){
        d = 3 + 2*i;
        if (i % 2 == 0){
            pi -= (1/d);
        }
        else if (i % 2 != 0){
            pi += (1/d);
        }
    }
    guess = 4 * pi;
    return guess;
}

float openMP_pi_leibniz( long n){
    if (n < 1){
        cout << "Invalid number of terms provided: " << n << "\n";
        return -1;
    }

    float pi = 0;
    float d;
    float guess;

    #pragma omp parallel for reduction(+:pi)
    for (unsigned long long i = 0; i < n; i++){
        d = 3 + 2*i;
        if (i % 2 == 0){
            pi -= (1/d);
        }
        else if (i % 2 != 0){
            pi += (1/d);
        }
    }
    guess = 4 * (pi + 1);
    return guess;
}
