// Copyright 2024, University of Freiburg
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#include "./Snake.h"
#include <ncurses.h>
#include <unistd.h>

// Speed in pixels per second.
double speed = 1;
// Acceleration in pixel per second squared.
double acceleration = 1;

// Main function.
int main() {
  initTerminal();
  initGame();
  drawBorder(COLOR_BLUE);
  drawSnake(COLOR_GREEN);
  refresh();

  // The absolute distance moved since the last call to moveSnake(). If it
  // becomes > 1 we have to move the snake by one pixel.
  double distance = 0;
  while (true) {
    while (true) {
      if (!handleKey(getch())) {
        endwin();
        return 0;
      }
      usleep(1000);
      distance += speed / 1000;
      speed += acceleration / 1000;
      if (distance >= 1.0) {
        distance -= 1.0;
        break;
      }
    }
    drawSnake(COLOR_BLACK);
    moveSnake();
    drawSnake(COLOR_GREEN);
    refresh();
    if (collidesWithBorder()) {
      // Game over, wait for the escape key to be pressed.
      while (handleKey(getch())) {
      }
      endwin();
      return 0;
    }
  }
}
