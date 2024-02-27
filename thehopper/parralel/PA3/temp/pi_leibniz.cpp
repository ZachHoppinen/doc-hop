#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
  
  long long val  = 1000;
  MPI_Init(&argc, &argv);
  int process, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &process);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
  int myShare = floor(val/process);
    if (val%process > rank)
	{
    // add one to subsequent processors until remainder is filled.
		myShare = myShare + 1;
	}
  float pi = 1;
  float  d = 3;
  for (long int n=rank; n<val; n+=process) {
    if (n % 2 == 0) {
      pi -=(1/d); 
    } else {
      pi += (1/d);
    } 
   d = d+2;    
  }
  // printf("proc: %i, is %f", rank, pi);
  float guess;

  MPI_Reduce(&pi, &guess, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0) cout << "pi is " << 4*guess << "!\n";

                     
  MPI_Finalize();
  return 0;
}
