//
// Created by Camron Collinsworth on 9/11/22.
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <random>
#include <cmath>
#include "matrix.h"
#include "utilities.h"

using namespace std;


/**
 * converts a 2-d matrix coordinate to 1-d
 * @param matrix matrix
 * @param row row index
 * @param col column index
 * @return
 */
int getIndex(Matrix matrix, int i, int j){
    return ((i * matrix.cols) + j);
}


/**
 *
 * @param m matrix
 * @return string of matrix data
 */
string matrixToString(Matrix matrix){
    string ret = "";
    for(int row = 0; row < matrix.rows; row++) {
        for(int col = 0; col < matrix.cols; col++) {
            ret = ret + std::to_string(matrix.table[(getIndex(matrix, row, col))]) + " ";
        }
        ret = ret +  "\n";
    }
    return ret;

}


/**
 * free the memory of vector
 * @param v vector
 */
void freeVector(Vector vector) {
    free(vector.table);
}

/**
 * free the memory of matrix
 * @param m matrix
 */
void freeMatrix(Matrix matrix){
    free(matrix.table);
}

/**
 * counts the number of lines in a text file
 * @param fileName file name
 * @return int number of lines
 */
int lineCount(char* fileName){
    ifstream file(fileName);
    string word;
    int lines = 0;
    while (std::getline(file, word)){
        lines++;
    }
    file.close();
    return lines;
}

/**
 * counts the number of words in a text file
 * @param fileName file name
 * @return int number of words
 */
int wordCount(char* fileName){
    ifstream file(fileName);
    string word;
    int words  = 0;
    while(file >> word){
        words++;
    }
    file.close();
    return words;
}

/**
 * print matrix data to standard out
 * @param m matrix
 */
void printMatrix(Matrix matrix){
    for(int row = 0; row < matrix.rows; row++) {
        for(int col = 0; col < matrix.cols; col++) {
            cout << matrix.table[getIndex(matrix, row, col)] << " ";
        }
        cout << "\n";
    }
}

/**
 * print vector data to standard out
 * @param v vector
 */
void printVector(Vector vector){
    for(int i = 0; i < vector.size; i++){
        cout << vector.table[i] << "\n";
    }
}


/**
 * create a vector object
 * @param filename file name
 * @return vector
 */
Vector createVector(char* filename) {
    ifstream vectorStream(filename);
    if (vectorStream.is_open()) { // parse vector
        Vector vector;
        double* vectorTable;
        int vectorSize;

        vectorStream >> vectorSize;

        if (vectorSize != (lineCount(filename) - 1)) {
            fprintf(stderr, "ERROR SIZE MISMATCH");
            exit(1);
        }

        // dynamically create array
        vectorTable = new double [vectorSize];
        //populate vector
        double in;
        for (int row = 0; row < vectorSize; row++) {
            vectorStream >> in;
            vectorTable[row] = in;
        }

        vector.size = vectorSize;
        vector.table = vectorTable;
        return vector;
    }
    else {
        fprintf(stderr, "unable to open file");
        exit(1);
    }
}
/**
 * create matrix object
 * @param filename filename
 * @return matrix
 */
Matrix createMatrix(char* filename){
    try {
        ifstream matrixStream(filename); // open and parse first matrix file.
        if (matrixStream.is_open()) {
            Matrix matrix;
            int matrixRows, matrixCols;
            double* matrixTable;
            matrixStream >> matrixRows;
            matrixStream >> matrixCols;

            if (matrixRows != (lineCount(filename) - 1)) {  // check row number match
                fprintf(stderr, "ERROR ROW MISMATCH");
                exit(1);
            }
            else if (matrixRows * matrixCols != (wordCount(filename) - 2)) { // check total number match
                fprintf(stderr, "ERROR MATRIX MISMATCH");
                exit(1);
            }

            // dynamically create matrixTable
            matrixTable = new double [(matrixRows * matrixCols)];

            //populate matrixTable
            double in;
            for (int i = 0; i < (matrixRows * matrixCols); i++) {
                matrixStream >> in;
                matrixTable[i] = in;
            }

            
            matrix.table = matrixTable;
            matrix.rows = matrixRows;
            matrix.cols = matrixCols;

            return matrix;
        }
        else{
            fprintf(stderr, "unable to open file");
            exit(1);
        }
    }
    catch (exception){
        fprintf(stderr, "UNEXPECTED ERROR");
        exit(1);
    }
}

/**
 * multiply two matrices
 * @param m1 matrix first
 * @param m2 matrix second
 * @return matrix result
 */
Matrix multiplyMatrices(Matrix matrix1, Matrix matrix2){

    if (matrix1.cols != matrix2.rows) { // check if two matrices can be multiplied.
        fprintf(stderr,"Unable to multiply specified matrices based on dimensions");
        exit(1);
    }

    // dynamically create result matrix
    double * result;
    result = new double [(matrix1.rows * matrix2.cols)];

    // multiply the matrices
    int sum = 0;
    for (int i = 0; i < matrix1.rows; i++) {
        for (int j = 0; j < matrix2.cols; j++) {
            for (int k = 0; k < matrix2.rows; k++) {
                sum += matrix1.table[getIndex(matrix1, i, k)] * matrix2.table[getIndex(matrix2, k, j)];
            }
            result[getIndex(matrix2, i, j)] = sum;
            sum = 0;
        }
    }

    Matrix ret;
    ret.table = result;
    ret.rows = matrix1.rows;
    ret.cols = matrix2.cols;
    return ret;
}

/**
 * multiply a matrix and vector
 * @param m matrix
 * @param v vector
 * @return vector result
 */
Vector multiplyMatVect(Matrix matrix,Vector vector){
    double * result;
    if(matrix.cols != vector.size){ // ensure that the two can be multiplied
        fprintf(stderr, "ERROR VECTOR/MATRIX SIZE MISMATCH");
        freeMatrix(matrix);
        freeVector(vector);
        exit(1);
    }
     result = new double[matrix.rows];
    // perform multiplication
    for(int i = 0; i < matrix.rows; i++){
        double partialProduct = 0;
        for(int j = 0; j < matrix.cols; j++){
            partialProduct += matrix.table[getIndex(matrix, i, j)] * vector.table[j];
        }
        result[i] = partialProduct;
    }
    Vector ret;
    ret.size = matrix.rows;
    ret.table = result;
    return ret;
}

/**
 * performs a matrix multiply on two matrices and returns the result matrix
 * @param file1 filename matrix 1
 * @param file2 filename matrix 2
 * @return matrix result
 */
Matrix runMatrixMult(char* file1, char* file2){
    Matrix matrix1 = createMatrix(file1);
    Matrix matrix2 = createMatrix(file2);
    Matrix result = multiplyMatrices(matrix1, matrix2);
    //printMatrix(result);
    freeMatrix(matrix1);
    freeMatrix(matrix2);
    return result;
}

/**
 *
 * @param f1 filename matrix
 * @param f2 filename vector
 * @return vector result
 */
Vector runVectMatrixMult(char* file1, char*file2){
    Matrix matrix = createMatrix(file1);
    Vector vector = createVector(file2);
    Vector result = multiplyMatVect(matrix, vector);
    //printVector(result);
    freeMatrix(matrix);
    freeVector(vector);
    return result;
}

/**
 * compare two matrices return true if equal, else false
 * @param m1 matrix first
 * @param m2 matrix second
 * @return bool
 */
bool matrixCompare(Matrix matrix1, Matrix matrix2){
    if(matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols){
        return false;
    }
    for(int i = 0; i < matrix1.rows; i++){
        for(int j = 0; j < matrix1.cols; j++){
            if(matrix1.table[getIndex(matrix1, i, j)] != matrix2.table[getIndex(matrix2, i, j)]){
                return false;
            }
        }
    }
    return true;
}

/**
 * compare two vectors return true if equal, else false
 * @param v1
 * @param v2
 * @return bool
 */
bool vectorCompare(Vector vector1, Vector vector2){
    if(vector1.size != vector2.size){
        return false;
    }
    for(int i = 0; i < vector1.size; i++){
        if(vector1.table[i] != vector2.table[i]){
            return false;
        }
    }
    return true;
}

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