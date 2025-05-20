// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//

#include "./String.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

// Convert two results of `clock()` to the number of seconds that lie between
// these measurements.
float clocksToSecond(clock_t start, clock_t end) {
  return static_cast<float>(end - start) / CLOCKS_PER_SEC;
}

int main() {
  size_t size = 10000;
  printf("Initializing %zu random strings\n", size);
  StringSorter sorter(size);
  StringSorter sorter2(size);

  const int stringSize = 100;
  char buffer[stringSize + 1] = {};
  for (size_t i = 0; i < size; ++i) {
    // Create random strings.
    for (size_t j = 0; j < stringSize; ++j) {
      // Sample a random number and store it in buffer[j]
      // repeat until we have sampled a number that is not
      // zero.
      do {
        buffer[j] = lrand48();
      } while (!buffer[j]);
    }
    sorter[i] = buffer;
    sorter2[i] = buffer;
  }

  clock_t t1 = clock();
  printf("Sorting %zu random strings with move\n", size);
  sorter.sortWithMove();
  clock_t t2 = clock();
  printf("Sorting finished, took %.2f seconds\n", clocksToSecond(t1, t2));

  printf("Sorting %zu random strings using copies\n", size);
  sorter2.sortWithCopy();
  clock_t t3 = clock();
  printf("Sorting finished, took %.2f seconds\n", clocksToSecond(t2, t3));
}
