// Copyright 2024, Paul Schaffrath, all rights reserved.
// <ps609@students.uni-freiburg.de>

#include "./String.h"
#include <ctime>

// Test runtime of the String class. Measure runtime of sortWithCopy() and
// sortWithMove()
// main with one argument (number of strings to sort)
int main(int argc, char **argv) {
  // Create two StringSorter objects with n random strings (Both have the same
  // strings) the strings are 100 characters long.
  if (argc != 2) {
    printf("Usage: %s <number of strings>\n", argv[0]);
    return 1;
  }
  size_t n = argv[1] ? atoi(argv[1]) : 1000;
  StringSorter sorter1(n);
  StringSorter sorter2(n);
  for (size_t i = 0; i < n; ++i) {
    char *s = new char[101];
    for (size_t j = 0; j < 100; ++j) {
      s[j] = 'a' + rand() % 26;
    }
    s[100] = '\0';
    sorter1.strings_[i] = s;
    sorter2.strings_[i] = s;
  }
  clock_t start_time_move = clock();
  sorter2.sortWithMove();
  clock_t end_time_move = clock();

  float time_move = (float)(end_time_move - start_time_move) / CLOCKS_PER_SEC;
  printf("sortWithMove() took %f seconds\n", time_move);

  clock_t start_time_copy = clock();
  sorter1.sortWithCopy();
  clock_t end_time_copy = clock();
  float time_copy = (float)(end_time_copy - start_time_copy) / CLOCKS_PER_SEC;

  printf("sortWithCopy() took %f seconds\n", time_copy);
  return 0;
}
