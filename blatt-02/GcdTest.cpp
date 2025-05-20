// Copyright 2024, University of Freiburg
//                 Chair of Algorithms and Data Structures
// Author: Johannes Kalmbach (kalmbach@cs.uni-freiburg.de)

#include "Gcd.h"
#include <gtest/gtest.h>

TEST(gcd, coprimeNumbers) {
  ASSERT_EQ(gcd(1, 3, false), 1);
  ASSERT_EQ(gcd(4, 3, false), 1);
  ASSERT_EQ(gcd(26, 81, false), 1);
}

TEST(gcd, multiples) {
  ASSERT_EQ(gcd(33, 3, false), 3);
  ASSERT_EQ(gcd(11, 44, false), 11);
}

TEST(gcd, complex) {
  ASSERT_EQ(gcd(12, 9, false), 3);
  ASSERT_EQ(gcd(16, 36, false), 4);
}

// The generic main function for GCD test.
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
