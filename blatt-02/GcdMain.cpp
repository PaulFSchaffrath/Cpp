// Copyright 2024, University of Freiburg
//                 Chair of Algorithms and Data Structures
// Author: Johannes Kalmbach (kalmbach@cs.uni-freiburg.de)

#include "./Gcd.h"
#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: ./GcdMain <x> <y>\n");
    return 1;
  }

  int x = atoi(argv[1]);
  int y = atoi(argv[2]);

  int result = gcd(x, y, true);
  printf("gcd(%d, %d) = %d\n", x, y, result);
}
