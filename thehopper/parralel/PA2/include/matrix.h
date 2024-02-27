//
// Created by Camron Collinsworth on 9/11/22.
//

#ifndef CS430_TEAME_MATRIX_H
#define CS430_TEAME_MATRIX_H
/**
 *  class defines a matrix object that contains info about the matrix as well as its contents in a 2-d array format
 */
class Matrix{
public:
    double* table;
    int rows, cols;
};
/**
 *  class defines a vector object that contains info about the vector as well as its contents in an array
 */
class Vector{
public:
    double* table;
    int size;
};

#endif //CS430_TEAME_MATRIX_H
