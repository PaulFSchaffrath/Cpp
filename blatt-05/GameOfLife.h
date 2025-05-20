// Copyright 2024, Paul Schaffrath

#pragma once

#include "./TerminalManager.h"

// A class for the game GameOfLife
class GameOfLife {
private:
  // The two pointers to the current and previous grid, they are switched after
  // each iteration.
  bool *previousGrid_;
  bool *currentGrid_;

  // Last coordinate clicked inside grid.
  int lastClickedCol_;
  int lastClickedRow_;

  // Additional global state
  bool isRunning_;
  int numSteps_;
  int numLivingCells_;

  // Functions that get or set the previous or current grid value at a given
  // position.
  void setPrevious(int row, int col, bool value);
  void setCurrent(int row, int col, bool value);
  bool getCurrent(int row, int col);
  bool getPrevious(int row, int col);

  // The implementation of the four functions above.
  void set(int row, int col, bool value, bool usePrevious);
  bool get(int row, int col, bool usePrevious);

  TerminalManager terminalManager_;

public:
  // PLay the game
  void play();

private:
  // Initialize the game
  void initGame();

  // Handle key and mouse presses. Change the new grid.
  bool processUserInput(UserInput userInput);

  // Calculate the next state and write it into new grid.
  void updateState();

  // Count the number of alive cells around given coordinates in the old grid.
  int numAliveNeighbours(int row, int col);

  // Draw the new grid using ncurses.
  // void showState();

  // Additional helper functions not explicitly mentioned in the sheet.
  // Returns true if the coordinates (x, y) are inside the grid
  bool isLegalPosition(int row, int col);
};
