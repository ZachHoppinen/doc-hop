//
// Created by Camron Collinsworth on 11/7/22.
//

#include <iostream>
#include <fstream>
using namespace std;

int main (int argc, char** argv) {
    ofstream myfile;
    int randyDandy;
    myfile.open (argv[3]);
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    myfile << rows;
    myfile << " ";
    myfile << cols;
    myfile << "\n";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++) {
            randyDandy = 1 + rand() % 9;
            myfile << randyDandy << " ";
        }
        myfile << "\n";
    }
    myfile.close();
    return 0;
}