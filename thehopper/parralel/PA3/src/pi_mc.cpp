/*
Calculate pi using the a monte carlo estimation. Checks for invalid number of terms 
and then uses a for loop to generate random values and calculate pi using the
area under the curve sqrt(1-x^2).

Reference: https://blogs.sas.com/content/iml/2016/03/14/monte-carlo-estimates-\
of-pi.html#:~:text=To%20compute%20Monte%20Carlo%20estimates,the%20curve%20is%20%\
CF%80%20%2F%204.
*/

#include <random>
#include <cmath>
#include <iostream>
#include <vector>
#include "omp.h"
#include <mpi.h>
#define SEED 35791246
#define master 0
using namespace std;

float calc_pi_mc (int n){
    // Estimate pi using a monte carlo esimation of points along sqrt(1-x^2)
    if (n < 1){
        cout << "Invalid number of terms provided: " << n << "\n";
        return -1;
    }
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution <> dist(0, 1);

    float u, y, guess;
    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        u = dist(gen);
        y = sqrt(1 - pow(u, 2));
        sum += y;
    }
    guess = 4 * sum / n;
    return guess;
}

float openMP_pi_mc (int n){
    // Estimate pi using a monte carlo esimation of points along sqrt(1-x^2)
    if (n < 1){
        cout << "Invalid number of terms provided: " << n << "\n";
        return -1;
    }
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution <> dist(0, 1);

    float u, y, guess;
    float sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        u = dist(gen);
        y = sqrt(1 - pow(u, 2));
        sum += y;
    }
    guess = 4 * sum / n;
    return guess;
}

int pi_mc_MPI(long iter, int argc, char *argv[]){

   double x,y,z,pi;
   long int i,j,
   count = 0,total = 0;
   int rank, process; 
   MPI_Status status;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&process);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   iter = ceil(iter / process);
   srand(SEED+rank);
   double start,end;
   MPI_Barrier(MPI_COMM_WORLD);
   start=MPI_Wtime();

   for (i=0; i<iter; i++) {
      x =(double) rand() / RAND_MAX;
      y =(double) rand() / RAND_MAX;
      z = x*x+y*y;
      if (z<=1){
	 count++;
	} 
   }

    MPI_Reduce(&count, &total, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    end = MPI_Wtime();
    if(rank == 0){
    pi=(double)total/(iter * process) * 4;
    cout << "The value of PI is\n " << pi << "\n";
    printf("Time: %.7fs\n",end-start);
    }
   
   MPI_Finalize();

   return pi;
}