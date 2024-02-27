#include <gtest/gtest.h>
#include <math.h>
#include "fib.h"

using namespace std;

namespace {
// Test functions for Fibonacci

// Check for invalid negative inputs

TEST(FibTest, HandlesNegInput) {
  EXPECT_EQ(calc_fib(-1), -1);
  EXPECT_EQ(calc_fib(-10), -1);

}
// Check for 0th fibonacci

TEST(FibTest, HandlesZeroInput) {
  EXPECT_EQ(calc_fib(0), 0);

}

// Check for positive inputs

TEST(FibTest, HandlesPosInput) {
  EXPECT_EQ(calc_fib(1), 1);
  EXPECT_EQ(calc_fib(10), 55);
  EXPECT_EQ(calc_fib(16), 987);
  EXPECT_EQ(calc_fib(20), 6765);
}
}
