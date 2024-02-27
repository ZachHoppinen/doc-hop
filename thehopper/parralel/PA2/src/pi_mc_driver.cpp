/* Calculate pi with monte carlo technique
 https://blogs.sas.com/content/iml/2016/03/14/monte-carlo-estimates-of-pi.html

Usage: pi_mc [number_terms]

arguments:
    number_terms (optional): number of random observations to compare [default: 1000]
*/
#include "utilities.h"
#include "pi_mc.h"
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
    
    printf("Calculating pi using Monte Carlo analysis with %lld values.\n", n);

    // printf("Starting Serial Implementation:\n");

    // // Calculate a guess for pi serially.
    // test_time_func(&calc_pi_mc, n);

    printf("Starting Parrelel Implementation:\n");

    // Calculate a guess for pi using openMP.
    test_time_func(&openMP_pi_mc, n);

    return 0;
}
