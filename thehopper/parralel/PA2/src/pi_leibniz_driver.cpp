/* Calculate pi with Leibniz Series

Usage: pi_leibniz [number_terms]

arguments:
    number_terms (optional): number of leibniz terms to use [default: 1000]
*/

#include <iostream>
#include <climits>
#include "stdint.h"
#include "pi_leibniz.h"
#include "utilities.h"
using namespace std;

int main (int argc, char *argv[]){

    float guess;
    long n;
    // Parsing input values
    if (argc != 2){
        n = 1000;
    }
    else{
        n = strtol(argv[1], NULL, 0);
    }

    // int n = parseInput(argc, argv);
    
    printf("Calculating pi using Leibniz series with %lld values.\n", n);

    // printf("Starting Serial Implementation:\n");

    // // Calculate a guess for pi serially.
    // test_time_func(&calc_pi_leibniz, n);

    printf("Starting Parrelel Implementation:\n");

    // Calculate a guess for pi using openMP.
    test_time_func(&openMP_pi_leibniz, n);

    return 0;
}