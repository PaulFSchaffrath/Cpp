// Copyright 2024, Paul Schaffrath

#include "./Snake.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  // Terminal and game Initialization
  initTerminal();
  initGame();

  // Velocity and acceleration
  int speed = 500;      // 1 / 1000 pixel per second
  int acceleration = 3; // 1 / 1000 pixel per second squared

  // Draw Borderline and starting snake
  drawBorder(1);
  drawSnake(2);

  // Game Loop
  for (int i = 0; i < 1000000; ++i) {
    bool shut_down = false;

    drawSnake(2);
    int key = getch();
    if (handleKey(key)) {
      while (true) {
        if (handleKey(getch())) {
          shut_down = true;
          break;
        }
      }
    }
    if (shut_down) {
      break;
    }
    if (i % (speed) == 0) {
      refresh();
      drawPixel(yPos, xPos, 3);
      moveSnake();
      refresh();
      if (speed - acceleration > 5) {
        speed -= acceleration;
      }
    }

    if (collidesWithBorder()) {
      break;
    }
    usleep(1000);
  }

  // Close Ncurses window
  endNcurses();

  return 0;
}
