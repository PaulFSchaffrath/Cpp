#include "./Gcd.h"

#include <cstdio>
#include <cstdlib>

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: You need to set two arguments for a valid result.\n");
    return 1;
  }
  int x = atoi(argv[1]);
  int y = atoi(argv[2]);
  printf("gcd(%d, %d) = %d", x, y, gcd(x, y, true));
  return 0;
}
