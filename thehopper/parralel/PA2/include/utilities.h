#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include "matrix.h"


#ifndef UTILITY_HEADER

#define UTILITY_HEADER

using namespace std;

/**
 *
 * @param m matrix
 * @return string of matrix data
 */
string matrixToString(Matrix matrix);

/**
 * converts a 2-d matrix coordinate to 1-d
 * @param matrix matrix
 * @param row row index
 * @param col column index
 * @return
 */
int getIndex(Matrix matrix, int row, int col);

/**
 * free the memory of vector
 * @param v vector
 */
void freeVector(Vector vector);

/**
 * free the memory of matrix
 * @param m matrix
 */
void freeMatrix(Matrix matrix);

/**
 * counts the number of lines in a text file
 * @param fileName file name
 * @return int number of lines
 */
int lineCount(char* fileName);

/**
 * counts the number of words in a text file
 * @param fileName file name
 * @return int number of words
 */
int wordCount(char* fileName);

/**
 * print matrix data to standard out
 * @param m matrix
 */
void printMatrix(Matrix matrix);

/**
 * print vector data to standard out
 * @param v vector
 */
void printVector(Vector vector);


/**
 * create a vector object
 * @param filename file name
 * @return vector
 */
Vector createVector(char* filename);
/**
 * create matrix object
 * @param filename filename
 * @return matrix
 */
Matrix createMatrix(char* filename);

/**
 * multiply two matrices
 * @param m1 matrix first
 * @param m2 matrix second
 * @return matrix result
 */
Matrix multiplyMatrices(Matrix matrix1, Matrix matrix2);

/**
 * multiply two matrices in parallel
 * @param m1 matrix first
 * @param m2 matrix second
 * @return matrix result
 */
Matrix multiplyMatricesParallel(Matrix matrix1, Matrix matrix2);

/**
 * multiply a matrix and vector
 * @param m matrix
 * @param v vector
 * @return vector result
 */
Vector multiplyMatVect(Matrix matrix,Vector vector);

/**
 * multiply a matrix and vector
 * @param m matrix
 * @param v vector
 * @return vector result
 */
Vector multiplyMatVectParallel(Matrix matrix,Vector vector);

/**
 * performs a matrix multiply on two matrices and returns the result matrix
 * @param file1 filename matrix 1
 * @param file2 filename matrix 2
 * @return matrix result
 */
Matrix runMatrixMult(char* file1, char* file2);

/**
 *
 * @param f1 filename matrix
 * @param f2 filename vector
 * @return vector result
 */
Vector runVectMatrixMult(char* file1, char*file2);

/**
 * compare two matrices return true if equal, else false
 * @param m1 matrix first
 * @param m2 matrix second
 * @return bool
 */
bool matrixCompare(Matrix matrix1, Matrix matrix2);

/**
 * compare two vectors return true if equal, else false
 * @param v1
 * @param v2
 * @return bool
 */
bool vectorCompare(Vector vector1, Vector vector2);

bool stringIsInt(const string& str);

int parseInput(int argc, char *argv[]);

void print_result(float guess, int duration, bool parse);

void test_time_func(float (*func)( long),  long n);

#endif