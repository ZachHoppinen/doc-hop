//
// Created by Camron Collinsworth on 9/11/22.
//

#include <gtest/gtest.h>
#include <math.h>
#include "utilities.h"
#include <cstring>
#include <string>



using namespace std;

namespace {
        TEST(MatrixMultiplyTest_3x3_1, CorrectResult) {
        char* expectedmM = (char*)"../tests/test_files/Matrices/3x3_1_Solution";
        char* m1 = (char*)"../tests/test_files/Matrices/mm1_3x3";
        char* m2 = (char*)"../tests/test_files/Matrices/mm2_3x3";

        Matrix expected3x3 = createMatrix(expectedmM);
        Matrix result = runMatrixMult(m1, m2);
        EXPECT_EQ(matrixCompare(expected3x3, result), true);

        freeMatrix(expected3x3);
        freeMatrix(result);
    }

        TEST(MatrixMultiplyTest_3x3_2, CorrectResult) {
        char* expectedmM = (char*)"../tests/test_files/Matrices/3x3_2_Solution";
        char* m1 = (char*)"../tests/test_files/Matrices/mm3_3x3";
        char* m2 = (char*)"../tests/test_files/Matrices/mm4_3x3";

        Matrix expected3x3 = createMatrix(expectedmM);
        Matrix result = runMatrixMult(m1, m2);
        EXPECT_EQ(matrixCompare(expected3x3, result), true);

        freeMatrix(expected3x3);
        freeMatrix(result);
        }

        TEST(MatrixMultiplyTest_3x3_1_Wrong_Answer, CorrectResult) {
        char* expectedmM = (char*)"../tests/test_files/Matrices/3x3_1_Solution";
        char* m1 = (char*)"../tests/test_files/Matrices/mm3_3x3";
        char* m2 = (char*)"../tests/test_files/Matrices/mm2_3x3";

        Matrix expected3x3 = createMatrix(expectedmM);
        Matrix result = runMatrixMult(m1, m2);
        EXPECT_EQ(matrixCompare(expected3x3, result), false);

        freeMatrix(expected3x3);
        freeMatrix(result);
        }

        TEST(MatrixMultiplyTest_3x3_2_Wrong_Answer, CorrectResult) {
        char* expectedmM = (char*)"../tests/test_files/Matrices/3x3_2_Solution";
        char* m1 = (char*)"../tests/test_files/Matrices/mm1_3x3";
        char* m2 = (char*)"../tests/test_files/Matrices/mm4_3x3";

        Matrix expected3x3 = createMatrix(expectedmM);
        Matrix result = runMatrixMult(m1, m2);
        EXPECT_EQ(matrixCompare(expected3x3, result), false);

        freeMatrix(expected3x3);
        freeMatrix(result);
        }

        TEST(MatrixMultiplyTest_4x4_2, CorrectResult) {
        char* expectedmM = (char*)"../tests/test_files/Matrices/4x4_2_Solution";
        char* m1 = (char*)"../tests/test_files/Matrices/mm3_4x4";
        char* m2 = (char*)"../tests/test_files/Matrices/mm4_4x4";

        Matrix expected4x4 = createMatrix(expectedmM);
        Matrix result = runMatrixMult(m1, m2);
        EXPECT_EQ(matrixCompare(expected4x4, result), true);

        freeMatrix(expected4x4);
        freeMatrix(result);
        }

        TEST(MatrixMultiplyTest_4x4_1_Wrong_Answer, CorrectResult) {
        char* expectedmM = (char*)"../tests/test_files/Matrices/4x4_2_Solution";
        char* m1 = (char*)"../tests/test_files/Matrices/mm1_4x4";
        char* m2 = (char*)"../tests/test_files/Matrices/mm2_4x4";

        Matrix expected4x4 = createMatrix(expectedmM);
        Matrix result = runMatrixMult(m1, m2);
        EXPECT_EQ(matrixCompare(expected4x4, result), false);

        freeMatrix(expected4x4);
        freeMatrix(result);
        }


}

