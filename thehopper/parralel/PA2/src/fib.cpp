#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

int calc_fib(int n)
{
    int i, j;	
    if(n<0){
	 cout << "Invalid number  provided: " << n << "\n";
	 return -1;
	    
    }
    else if (n < 2) {
        return n;
    }
    else{
	#pragma omp task shared(i)
	 i = calc_fib(n-1);
	#pragma omp task shared(j)
	 j = calc_fib(n-2);

	#pragma omp taskwait
	 return i+j;
    }
}
