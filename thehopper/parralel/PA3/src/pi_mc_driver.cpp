/* Calculate pi with monte carlo technique
 https://blogs.sas.com/content/iml/2016/03/14/monte-carlo-estimates-of-pi.html

Usage: pi_mc [number_terms]

arguments:
    number_terms (optional): number of random observations to compare [default: 1000]
*/
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <iostream>
#include <string.h>
#include "utilities.h"
#include "pi_mc.h"

using namespace std;

int main(int argc, char *argv[])
{
   long iter;

   double pi;

   if (argc == 2) iter = strtol(argv[1], NULL, 0);
   else{
      printf("Wrong number of arguments provided");
      MPI_Finalize();
      return -1;
   }

   pi = pi_mc_MPI(iter, argc, argv);

   return 0;
}
