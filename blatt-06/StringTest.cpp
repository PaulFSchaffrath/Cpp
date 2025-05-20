// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#include "./String.h"
#include <gtest/gtest.h>

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

// Test the copy constructor.
TEST(String, CopyConstructor) {
  String s1;
  s1 = "string1";
  String s2(s1);

  ASSERT_EQ(7u, s2.size());
  ASSERT_STREQ("string1", s2.c_str());

  ASSERT_EQ(7u, s1.size());
  ASSERT_STREQ("string1", s1.c_str());
}

// Test the copy assignment operator.
TEST(String, CopyAssignment) {
  String s1;
  s1 = "string1";
  String s2;
  s2 = s1;

  ASSERT_EQ(7u, s2.size());
  ASSERT_STREQ("string1", s2.c_str());
  ASSERT_EQ(7u, s1.size());
  ASSERT_STREQ("string1", s1.c_str());
}

// Test that self-copy works
TEST(String, SelfCopyAssignment) {
  String s1;
  s1 = "string1";
  // Note, we could simply write `s1 = s1` but the `-Wdreprecated` complains.
  const String *ptr = &s1;
  s1 = *ptr;
  ASSERT_EQ(7u, s1.size());
  ASSERT_STREQ("string1", s1.c_str());
}

// The StringSorter stores n strings and takes the number n as a
// constructor argument.
TEST(StringSorter, Constructor) {
  StringSorter sorter(5);
  ASSERT_EQ(5u, sorter.size());
}

// After construction, the StringSorter stores n empty strings
// which can be accessed via the [] operator.
TEST(StringSorter, AccessOperatorRead) {
  StringSorter sorter(5);
  for (int i = 0; i < 5; ++i) {
    ASSERT_STREQ("", sorter[i].c_str());
    ASSERT_EQ(0u, sorter[i].size());
  }
}

// Test that we can also use the operator[] to modify the contents of the
// Strings.
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
// Hint: We already swapped something in the GameOfLife, but this time it's
// Strings instead of pointers.
TEST(StringSorter, Swap) {
  StringSorter sorter(4);
  sorter[0] = "faul";
  sorter[1] = "im";
  sorter[2] = "etwas";
  sorter[3] = "ist";

  sorter.swap(0, 2);

  ASSERT_STREQ("etwas", sorter[0].c_str());
  ASSERT_STREQ("im", sorter[1].c_str());
  ASSERT_STREQ("faul", sorter[2].c_str());
  ASSERT_STREQ("ist", sorter[3].c_str());

  sorter.swap(1, 3);
  ASSERT_STREQ("etwas", sorter[0].c_str());
  ASSERT_STREQ("ist", sorter[1].c_str());
  ASSERT_STREQ("faul", sorter[2].c_str());
  ASSERT_STREQ("im", sorter[3].c_str());
}

// Sort must be implemented using BubbleSort. This is slow and shouldn't
// be used in practice, but it is simple to implement and will be useful
// in sheet-07.
// // Note: It suffices, if you are able to sort lowercase strings that only
// consist of the letters a-z correctly. `strcmp` gives the expected comparison
// results for this case.
TEST(StringSorter, Sort) {
  StringSorter sorter(4);
  sorter[1] = "der";
  sorter[0] = "rest";
  sorter[3] = "ist";
  sorter[2] = "schweigen";

  sorter.sort();

  ASSERT_STREQ("der", sorter[0].c_str());
  ASSERT_STREQ("ist", sorter[1].c_str());
  ASSERT_STREQ("rest", sorter[2].c_str());
  ASSERT_STREQ("schweigen", sorter[3].c_str());
}

// The following tests were added AFTER the sheet was finished.
// They are not required to pass for blatt-06.
TEST(StringSorter, CopyConstructor) {
  StringSorter sorter(4);
  sorter[0] = "der";
  sorter[1] = "rest";
  sorter[2] = "ist";
  sorter[3] = "schweigen";

  // Copy constructor.
  StringSorter sorter2{sorter};
  StringSorter sorter3(0);
  // Copy assignment
  sorter3 = sorter2;

  ASSERT_STREQ("der", sorter[0].c_str());
  ASSERT_STREQ("rest", sorter[1].c_str());
  ASSERT_STREQ("ist", sorter[2].c_str());
  ASSERT_STREQ("schweigen", sorter[3].c_str());

  ASSERT_STREQ("der", sorter2[0].c_str());
  ASSERT_STREQ("rest", sorter2[1].c_str());
  ASSERT_STREQ("ist", sorter2[2].c_str());
  ASSERT_STREQ("schweigen", sorter2[3].c_str());

  ASSERT_STREQ("der", sorter3[0].c_str());
  ASSERT_STREQ("rest", sorter3[1].c_str());
  ASSERT_STREQ("ist", sorter3[2].c_str());
  ASSERT_STREQ("schweigen", sorter3[3].c_str());

  ASSERT_EQ(4u, sorter.size());
  ASSERT_EQ(4u, sorter2.size());
  ASSERT_EQ(4u, sorter3.size());
}
