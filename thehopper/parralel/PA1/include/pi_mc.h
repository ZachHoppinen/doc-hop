/*
Calculate pi using the a monte carlo estimation. Checks for invalid number of terms 
and then uses a for loop to generate random values and calculate pi using the
area under the curve sqrt(1-x^2).

Reference: https://blogs.sas.com/content/iml/2016/03/14/monte-carlo-estimates-\
of-pi.html#:~:text=To%20compute%20Monte%20Carlo%20estimates,the%20curve%20is%20%\
CF%80%20%2F%204.
*/

#ifndef MC_HEADER
#define MC_HEADER

float calc_pi_mc (long n);

#endif