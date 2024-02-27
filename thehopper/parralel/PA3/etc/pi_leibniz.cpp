#include <iostream>
using namespace std;

int main (int argc, char *argv[]){
  
  long long iter;
  int process, rank;
  double pi = 0;
  if (argc == 2) iter = strtol(argv[1], NULL, 0);
   else{
      printf("Wrong number of arguments provided");
      return -1;
   }
  clock_t start, duration;
    start = clock();
  double sum;
  for (long long n=0; n<iter; n++) {
    double tmp = 1.0 / ( 2.0 * (double)n + 1);
    if (n % 2 == 0) {
      pi += tmp;
    } else {
      pi -= tmp;
    }    
  }
  
  
    cout << "pi is " << 4.0 * pi << "!\n";
  duration = clock() - start;
    printf("Serial run time: %f8 seconds\n", ((double)duration)/CLOCKS_PER_SEC);
                     
  return 0;
}