// Copyright 2024, University of Freiburg
//                 Chair of Algorithms and Data Structures
// Author: Johannes Kalmbach (kalmbach@cs.uni-freiburg.de)

#include "./Gcd.h"
#include <cstdio>

// ______________________________________________________
int gcd(int x, int y, bool verbose) {
  if (x <= 0 || y <= 0) {
    printf("both inputs to gcd must be > 0, but were %d and %d\n", x, y);
    return -1;
  }
  while (true) {
    if (x > y) {
      int tmp = x;
      x = y;
      y = tmp;
    }
    if (verbose) {
      printf("= gcd(%d, %d)\n", x, y);
    }
    if (x == 0) {
      return y;
    }
    y = y % x;
  }
}
