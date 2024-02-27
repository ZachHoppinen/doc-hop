#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <iostream>
#include <string.h>
#define SEED 35791246
#define master 0

using namespace std;

int main(int argc, char *argv[])
{
   int iter=10000000;
   double x,y,z,pi;
   int i,j,
   count = 0,total = 0;
   int rank, process; 
   MPI_Status status;
   
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&process);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   
   srand(SEED+rank);

   for ( i=0; i<iter; i++) {
      x =(double) rand() / RAND_MAX;
      y =(double) rand() / RAND_MAX;
      z = x*x+y*y;
      if (z<=1){
	      count++;
	   } 
   }

   // The master rank will collect result from all
  
   if (rank == 0){
      total = count;
      
      for (j = 1; j < process; j++)
        {
         MPI_Recv(&count,1,MPI_REAL,j,1,MPI_COMM_WORLD,&status);
         total += count;        
      }
      pi=(double)total/(iter * process) * 4;

      cout << "The value of PI is\n " << pi << "\n";
   }
   else {
      MPI_Send(&count,1,MPI_REAL,master,1,MPI_COMM_WORLD);
   }
   
   MPI_Finalize();        
   return 0;
}
