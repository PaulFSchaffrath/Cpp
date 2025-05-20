#include "./Gcd.h"
#include <gtest/gtest.h>

TEST(GcdTest, gcd) {
  ASSERT_EQ(gcd(12, 20, false), 4);
  ASSERT_EQ(gcd(7, 13, false), 1);
  ASSERT_EQ(gcd(81, 27, false), 27);
  ASSERT_EQ(gcd(81, 18, false), 9);
  ASSERT_EQ(gcd(1000, 30, false), 10);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
