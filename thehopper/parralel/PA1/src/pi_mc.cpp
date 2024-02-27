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
using namespace std;

float calc_pi_mc (long n){
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
    for (long i = 0; i < n; i++) {
        u = dist(gen);
        y = sqrt(1 - pow(u, 2));
        sum += y;
    }
    guess = 4 * sum / n;
    return guess;
}

// float calc_pi_mc_v2 (int n){
    // secondary approach to calculate pi that was not implemented.
//    // make vector
//     vector<float> v(n);
//     // Generate Random values
//     auto f = []() -> float { return sqrt(1- pow((rand()%10000)/10000.0,2)); };
//     // Fill up the vector
//     generate(v.begin(), v.end(), f);

//     float sum = 0.0;
//     for (int i = 0; i < n; i++) {
//         sum += v[i];
//     }
//     float guess = 4 * sum / n;
//     return guess;
// }