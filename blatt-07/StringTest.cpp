// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#include "./String.h"
#include <gtest/gtest.h>
#include <utility>

// After calling the default constructor, the size of a String must be 0.
TEST(String, DefaultConstructedStringHasSize0) {
  String s1;
  ASSERT_EQ(0u, s1.size());
}

// The c_str() (a const char*) returned by a default constructed string
// must be empty and terminated with a null byte.
TEST(String, DefaultConstructedStringIsNullTerminated) {
  String s1;
  ASSERT_EQ('\0', s1.c_str()[0]);
}

// Test const-correctness of the String class.
TEST(String, ConstCorrectness) {
  const String s1;
  ASSERT_EQ('\0', s1.c_str()[0]);
  ASSERT_EQ(0, s1.size());
}

// Test the assignment operator
TEST(String, Set1) {
  String s1;
  s1 = "hallo";
  ASSERT_EQ(5u, s1.size());

  const char *c = s1.c_str();
  ASSERT_EQ('h', c[0]);
  ASSERT_EQ('a', c[1]);
  ASSERT_EQ('l', c[2]);
  ASSERT_EQ('l', c[3]);
  ASSERT_EQ('o', c[4]);
  ASSERT_EQ('\0', c[5]);

  // Note: The following test is equivalent to the manual testing
  // of the bytes above, and we will use this short-hand from
  // now on:
  ASSERT_STREQ("hallo", s1.c_str());
}

// Test that the assignment operator indeed copies the string.
TEST(String, Set2) {
  char *dynamicString = new char[4]{'b', 'y', 'e', '\0'};
  String s1;
  s1 = dynamicString;
  delete[] dynamicString;
  // Now `dynamicString` does not exist anymore.
  ASSERT_STREQ("bye", s1.c_str());
}

// Test the move constructor.
TEST(String, MoveConstructor) {
  String s1;
  s1 = "string1";
  String s2(std::move(s1));

  ASSERT_EQ(7u, s2.size());
  ASSERT_STREQ("string1", s2.c_str());

  ASSERT_EQ(0, s1.size());
  ASSERT_STREQ("", s1.c_str());
}

// Test the move assignment operator.
TEST(String, MoveAssignment) {
  String s1;
  s1 = "string1";
  String s2;
  s2 = std::move(s1);

  ASSERT_EQ(7u, s2.size());
  ASSERT_STREQ("string1", s2.c_str());

  ASSERT_EQ(0, s1.size());
  ASSERT_STREQ("", s1.c_str());
}

//  ______________________________
TEST(StringSorter, Constructor) {
  StringSorter sorter(5);
  ASSERT_EQ(5, sorter.size());
}

//  ______________________________
TEST(StringSorter, AccessOperatorRead) {
  StringSorter sorter(5);
  for (int i = 0; i < 5; ++i) {
    ASSERT_STREQ("", sorter[i].c_str());
    ASSERT_EQ(0, sorter[i].size());
  }
}

//  ______________________________
TEST(StringSorter, AccessOperatorWrite) {
  StringSorter sorter(5);
  sorter[0] = "sein";
  sorter[1] = "oder";
  sorter[2] = "nicht";
  sorter[3] = "sein";

  ASSERT_STREQ("sein", sorter[0].c_str());
  ASSERT_STREQ("oder", sorter[1].c_str());
  ASSERT_STREQ("nicht", sorter[2].c_str());
  ASSERT_STREQ("sein", sorter[3].c_str());
  ASSERT_STREQ("", sorter[4].c_str());
}

// The swap method is a useful building block for sorting.
// It should be made private and you should use FRIEND_TEST for this test.
TEST(StringSorter, SwapWithCopy) {
  StringSorter sorter(4);
  sorter[0] = "faul";
  sorter[1] = "im";
  sorter[2] = "etwas";
  sorter[3] = "ist";

  sorter.swapWithCopy(0, 2);

  ASSERT_STREQ("etwas", sorter[0].c_str());
  ASSERT_STREQ("im", sorter[1].c_str());
  ASSERT_STREQ("faul", sorter[2].c_str());
  ASSERT_STREQ("ist", sorter[3].c_str());

  sorter.swapWithCopy(1, 3);
  ASSERT_STREQ("etwas", sorter[0].c_str());
  ASSERT_STREQ("ist", sorter[1].c_str());
  ASSERT_STREQ("faul", sorter[2].c_str());
  ASSERT_STREQ("im", sorter[3].c_str());
}

TEST(StringSorter, SwapWithMove) {
  StringSorter sorter(4);
  sorter[0] = "faul";
  sorter[1] = "im";
  sorter[2] = "etwas";
  sorter[3] = "ist";

  sorter.swapWithMove(0, 2);

  ASSERT_STREQ("etwas", sorter[0].c_str());
  ASSERT_STREQ("im", sorter[1].c_str());
  ASSERT_STREQ("faul", sorter[2].c_str());
  ASSERT_STREQ("ist", sorter[3].c_str());

  sorter.swapWithMove(1, 3);
  ASSERT_STREQ("etwas", sorter[0].c_str());
  ASSERT_STREQ("ist", sorter[1].c_str());
  ASSERT_STREQ("faul", sorter[2].c_str());
  ASSERT_STREQ("im", sorter[3].c_str());
}

// Tip: No matter what sorting algorithm you use, the swap method above
// comes in handy.
// Note: It suffices, if you are able to sort lowercase strings that only
// consist of the letters a-z correctly. `strcmp` gives the expected comparison
// results for this case.
TEST(StringSorter, SortWithCopy) {
  StringSorter sorter(4);
  sorter[1] = "der";
  sorter[0] = "rest";
  sorter[3] = "ist";
  sorter[2] = "schweigen";

  sorter.sortWithCopy();

  ASSERT_STREQ("der", sorter[0].c_str());
  ASSERT_STREQ("ist", sorter[1].c_str());
  ASSERT_STREQ("rest", sorter[2].c_str());
  ASSERT_STREQ("schweigen", sorter[3].c_str());
}

TEST(StringSorter, SortWithMove) {
  StringSorter sorter(4);
  sorter[1] = "der";
  sorter[0] = "rest";
  sorter[3] = "ist";
  sorter[2] = "schweigen";

  sorter.sortWithMove();

  ASSERT_STREQ("der", sorter[0].c_str());
  ASSERT_STREQ("ist", sorter[1].c_str());
  ASSERT_STREQ("rest", sorter[2].c_str());
  ASSERT_STREQ("schweigen", sorter[3].c_str());
}
