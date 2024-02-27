//
// Created by Camron Collinsworth on 9/12/22.
//
// #define _GLIBCXX_USE_CXX11_ABI 0
#include <gtest/gtest.h>
#include <math.h>
#include "utilities.h"
#include <cstring>
#include <string>



using namespace std;

namespace {
    TEST(MatrixVectorMultiplyTest_3x3_v3_1, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/3_1_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm1_3x3";
    char *v1 = (char *) "../tests/test_files/Vectors/v_3";

    Vector expected3x3 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected3x3, result), true);

    freeVector(expected3x3);
    freeVector(result);
}

    TEST(MatrixVectorMultiplyTest_3x3_v3_1_Wrong_Answer, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/3_2_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm1_3x3";
    char *v1 = (char *) "../tests/test_files/Vectors/v_3";

    Vector expected3x3 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected3x3, result), false);

    freeVector(expected3x3);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_3x3_v3_2, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/3_2_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm2_3x3";
    char *v1 = (char *) "../tests/test_files/Vectors/v_3";

    Vector expected3x3 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected3x3, result), true);


    freeVector(expected3x3);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_3x3_v3__Wrong_Answer, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/3_1_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm2_3x3";
    char *v1 = (char *) "../tests/test_files/Vectors/v_3";

    Vector expected3x3 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected3x3, result), false);


    freeVector(expected3x3);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_4x4_v4_1, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/4_1_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm1_4x4";
    char *v1 = (char *) "../tests/test_files/Vectors/v_4";

    Vector expected4x4 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected4x4, result), true);


    freeVector(expected4x4);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_4x4_v4_1_Wrong_Answer, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/4_2_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm1_4x4";
    char *v1 = (char *) "../tests/test_files/Vectors/v_4";

    Vector expected4x4 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected4x4, result), false);

    freeVector(expected4x4);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_4x4_v4_2, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/4_2_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm2_4x4";
    char *v1 = (char *) "../tests/test_files/Vectors/v_4";

    Vector expected4x4 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected4x4, result), true);

    freeVector(expected4x4);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_4x4_v4_2_Wrong_Answer, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/4_1_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm2_4x4";
    char *v1 = (char *) "../tests/test_files/Vectors/v_4";

    Vector expected4x4 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected4x4, result), false);

    freeVector(expected4x4);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_5x5_v5_1, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/5_1_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm1_5x5";
    char *v1 = (char *) "../tests/test_files/Vectors/v_5";

    Vector expected5x5 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected5x5, result), true);

    freeVector(expected5x5);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_5x5_v5_1_Wrong_Answer, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/5_2_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm1_5x5";
    char *v1 = (char *) "../tests/test_files/Vectors/v_5";

    Vector expected5x5 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected5x5, result), false);

    freeVector(expected5x5);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_5x5_v5_2, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/5_2_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm2_5x5";
    char *v1 = (char *) "../tests/test_files/Vectors/v_5";

    Vector expected5x5 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected5x5, result), true);

    freeVector(expected5x5);
    freeVector(result);
    }

    TEST(MatrixVectorMultiplyTest_5x5_v5_2_Wrong_Answer, CorrectResult){
    char *expectedV = (char *) "../tests/test_files/Vectors/5_1_Solution";
    char *m1 = (char *) "../tests/test_files/Matrices/mm2_5x5";
    char *v1 = (char *) "../tests/test_files/Vectors/v_5";

    Vector expected5x5 = createVector(expectedV);
    Vector result = runVectMatrixMult(m1, v1);
    EXPECT_EQ(vectorCompare(expected5x5, result), false);

    freeVector(expected5x5);
    freeVector(result);
    }
}