#include <random>
#include <cmath>
#include <iostream>
#include <vector>
#define SEED 35791246
#define master 0
using namespace std;


int main(int argc, char *argv[]){

   double x,y,z,pi;
   long int i,j, iter = 1000,
   count = 0,total = 0;
   int rank, process; 
   if (argc == 2) iter = strtol(argv[1], NULL, 0);
   
   srand(SEED);
   clock_t start, duration;
    start = clock();
   for (i=0; i<iter; i++) {
      x =(double) rand() / RAND_MAX;
      y =(double) rand() / RAND_MAX;
      z = x*x+y*y;
      if (z<=1){
	 count++;
	} 
   }
    total = count;
    pi=(double)total/(iter) * 4;
      cout << "The value of PI is\n " << pi << "\n";

   duration = clock() - start;
    printf("Serial run time: %f8 seconds\n", ((double)duration)/CLOCKS_PER_SEC);
   

   return pi;
}