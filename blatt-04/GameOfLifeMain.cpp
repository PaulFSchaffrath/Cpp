// Copyright 2024, Paul Schaffrath

#include "./GameOfLife.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  // Initialize Ncurses.
  initTerminal();
  initGame() if (numRows * numCols > MAX_NUM_CELLS) {
    printf("Too large gamescree. Increase MAX_NUM_CELLS or make terminal "
           "smaller\n");
    return 1;
  }

  // Main loop.
  while (true) {
    MEVENT event;
    int key = getch();
    if (getmouse(&event) == OK) {
      bool mouseClicked = processMouseClick(event);
      if (mouseClicked) {
        current_state[mouseY * numRows + mouseX] = !current_state[mouseY * numRows + mouseX]);
        drawAllPixels();
        // print coordinates
        attron(COLOR_PAIR(1));
        mvprintw(2, 2, "Mouse clicked at: %3d,%3d", mouseX, mouseY);
        attroff(COLOR_PAIR(1));
      }
    }
    if (key == 'g') {
      drawGlider(row, col);
      showState();
    }
    if (key == 'r') {
      // Noch nicht fertig
      showState();
    }
    if (key == 'q') {
      break;
    }
    if (key == ' ') {
      if (is_game_running) {
        is_game_running = false;
      } else {
        is_game_running = true;
      }
    }
    usleep(1000);
  }
  endNcurses();
}