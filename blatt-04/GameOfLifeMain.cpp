// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#include "./GameOfLife.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  // Initialize terminal and grid.
  initTerminal();
  initGame();

  if (numRows * numCols > MAX_NUM_CELLS) {
    printf("Screen too large, increase MAX_NUM_PIXELS\n");
    return 1;
  }

  while (processUserInput(getch())) {
    if (isRunning) {
      updateState();
    }
    // Draw and wait.
    showState();
    usleep(50 * 1000);
  }
  // Clean up window.
  endwin();
}
