#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int calc_fib(int n)
{
    if(n<0){
	 cout << "Invalid number  provided: " << n << "\n";
	 return -1;
	    
    }
    if (n < 2) {
        return n;
    }
    int a = 0, b = 1, c, i;
    for (i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
