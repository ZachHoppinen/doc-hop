#include <gtest/gtest.h>
#include <math.h>
#include "pi_mc.h"
#include "pi_leibniz.h"
#include "utilities.h"
using namespace std;

namespace {
// Test functions used in pi_mc and pi_leibniz estimations

TEST(LeibnizSerial, CorrectValues) {
  // Check for approximately right estimates of pi
  EXPECT_NEAR(M_PI, calc_pi_leibniz(1000),  0.01);
  EXPECT_NEAR(M_PI, calc_pi_leibniz(10000),  0.001);
  EXPECT_NEAR(M_PI, calc_pi_leibniz(100000),  0.0001);
}

TEST(LeibnizSerial, InvalidArg) {
  // Check for error messages with negative number of terms
  EXPECT_EQ(-1, calc_pi_leibniz(0));
  EXPECT_EQ(-1, calc_pi_leibniz(-1));
}

TEST(LeibnizParralel, CorrectValues) {
  // Check for approximately right estimates of pi
  EXPECT_NEAR(M_PI, openMP_pi_leibniz(1000),  0.01);
  EXPECT_NEAR(M_PI, openMP_pi_leibniz(10000),  0.001);
  EXPECT_NEAR(M_PI, openMP_pi_leibniz(100000),  0.0001);
}

TEST(LeibnizParralel, InvalidArg) {
  // Check for error messages with negative number of terms
  EXPECT_EQ(-1, openMP_pi_leibniz(0));
  EXPECT_EQ(-1, openMP_pi_leibniz(-1));
}

// Test for correct pi calculations.
TEST(MonteCarloSerial, CorrectValues) {
  // Check for approximately right estimates of pi
  EXPECT_NEAR(M_PI, calc_pi_mc(10000),  0.5);
  EXPECT_NEAR(M_PI, calc_pi_mc(100000),  0.1);
  EXPECT_NEAR(M_PI, calc_pi_mc(1000000),  0.01);
}

TEST(MonteCarloSerial, InvalidArg) {
  // Check for error messages with negative number of terms
  EXPECT_EQ(-1, calc_pi_mc(0));
  EXPECT_EQ(-1, calc_pi_mc(-1));
}

// Test for correct pi calculations.
TEST(MonteCarloParralel, CorrectValues) {
  // Check for approximately right estimates of pi
  EXPECT_NEAR(M_PI, openMP_pi_mc(10000),  0.5);
  EXPECT_NEAR(M_PI, openMP_pi_mc(100000),  0.1);
  EXPECT_NEAR(M_PI, openMP_pi_mc(1000000),  0.01);
}

TEST(MonteCarlParralel, InvalidArg) {
  // Check for error messages with negative number of terms
  EXPECT_EQ(-1, openMP_pi_mc(0));
  EXPECT_EQ(-1, openMP_pi_mc(-1));
}

TEST(PiFuncsTest, StringIsInt) {
  // Checking if string evaluates to integer or not.
  EXPECT_TRUE(stringIsInt("1"));
  EXPECT_TRUE(stringIsInt("3"));
  EXPECT_TRUE(stringIsInt("10"));
}

TEST(PiFuncsTest, StringNotInt) {
  EXPECT_FALSE(stringIsInt("10.1"));
  EXPECT_FALSE(stringIsInt("-1"));
  EXPECT_FALSE(stringIsInt("A"));
  EXPECT_FALSE(stringIsInt("ABC"));
  EXPECT_FALSE(stringIsInt("true"));
  EXPECT_FALSE(stringIsInt("1.3"));  
}

TEST(PiFuncsTest, SuccessfulArgParser) {
    // succesful parsing
    const char * a[] = {"pgname.cpp","10"};
    char **b = const_cast<char **>(a);

    EXPECT_EQ(parseInput(2, b), 10);

    a[1] = "20";
    b = const_cast<char **>(a);
    EXPECT_EQ(parseInput(2, b), 20);

    const char * c[] = {"pgname.cpp"};
    b = const_cast<char **>(c);
    EXPECT_EQ(parseInput(1, b), 1000);
}

TEST(PiFuncsTest, Exceptions) {
    // wrong term or too many
    const char * a[] = {"pgname.cpp","10.1"};
    char **b = const_cast<char **>(a);
    EXPECT_THROW(parseInput(2, b), invalid_argument);

    a[1] = "-20";
    b = const_cast<char **>(a);
    EXPECT_THROW(parseInput(2, b), invalid_argument);

    a[1] = "hello";
    b = const_cast<char **>(a);
    EXPECT_THROW(parseInput(2, b), invalid_argument);

    const char * c[] = {"pgname.cpp","10","incorrect-other-term"};
    b = const_cast<char **>(c);
    EXPECT_THROW(parseInput(3, b), range_error);

}

}