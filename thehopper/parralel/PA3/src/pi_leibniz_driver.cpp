/* Calculate pi with Leibniz Series

Usage: pi_leibniz [number_terms]

arguments:
    number_terms (optional): number of leibniz terms to use [default: 1000]
*/

#include <iostream>
#include <mpi.h>
#include "pi_leibniz.h"
#include "utilities.h"
using namespace std;

int main (int argc, char *argv[]){
  
  long long iter;
  int process, rank;
  double pi = 0;
  MPI_Init(&argc, &argv);
  if (argc == 2) iter = strtol(argv[1], NULL, 0);
   else{
      printf("Wrong number of arguments provided");
      MPI_Finalize();
      return -1;
   }
  MPI_Comm_size(MPI_COMM_WORLD, &process);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  double start,end;
  MPI_Barrier(MPI_COMM_WORLD);
  start=MPI_Wtime();
  
  for (long long n=rank; n<iter; n+=process) {
    double tmp = 1.0 / ( 2.0 * (double)n + 1);
    if (n % 2 == 0) {
      pi += tmp;
    } else {
      pi -= tmp;
    }    
  }
  
  
  double sum;
  MPI_Reduce(&pi, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  end = MPI_Wtime();  
  if (rank == 0) {
    cout << "pi is " << 4.0 * sum << "!\n";
  }
  if (rank == 0) printf("Time: %.7fs\n",end-start);
                     
  MPI_Finalize();
  return 0;
}