/*
Helper functions to parse inputs for pi calculation programs.
*/

#include <iostream>
#include <random>
#include <cmath>
using namespace std;

#ifndef PI_FUNCS

#define PI_FUNCS

bool stringIsInt(const string& str){
    // Boolean check if std contains non-numeric characters.
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

int parseInput(int argc, char *argv[]){
    // parse command line arguments and provide appropriate exceptions if
    // incorrect arguments and to return a int n to use in our pi calculations.
    int n;
    if (argc == 1){
        n = 1000;
    }
    else if (argc == 2){
        string str_n = argv[1];
        if (str_n.find('.') != string::npos){
            throw invalid_argument("Provide an integer number of terms.\n");
        }
        else if (str_n.find('-') != string::npos){
            throw invalid_argument("Negative number of terms provided.\n");
        }
        else if (!stringIsInt(str_n)){
            throw invalid_argument("Provide a valid number.\n");
        }
        sscanf(argv[1], "%d", &n);
    }
    else{
        throw range_error("Too many terms provided.\n");
    }
    return n;
}

#endif