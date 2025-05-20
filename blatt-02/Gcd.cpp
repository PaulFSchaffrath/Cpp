#include <cstdio>

void pInfo(int x, int y) {
  if (x <= y) {
    printf("= gcd(%d, %d)\n", x, y);
  } else {
    printf("= gcd(%d, %d)\n", y, x);
  }
}

int gcd(int x, int y, bool verbose) {
  while (y != 0) {
    if (verbose) {
      pInfo(x, y);
    }
    int temp = y;
    y = x % y;
    x = temp;
  }
  if (verbose) {
    pInfo(x, y);
  }
  return x;
}
