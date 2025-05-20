// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>,
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#include "./GameOfLife.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// The grid, alternated used to store the current and previous state.
bool grid1[MAX_NUM_CELLS];
bool grid2[MAX_NUM_CELLS];
bool *previousGrid;
bool *currentGrid;
// The initial values are used by the tests. In the game the are overwritten by
// the initTerminal function.
int numRows = 100;
int numCols = 100;

// Glider.
int glider[5][2] = {{1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}};

const int GLIDER_FACTORY_SIZE = 36;
int gliderFactory[GLIDER_FACTORY_SIZE][2] = {
    {0, 24}, {1, 22}, {1, 24}, {2, 12}, {2, 13}, {2, 20}, {2, 21}, {2, 34},
    {2, 35}, {3, 11}, {3, 15}, {3, 20}, {3, 21}, {3, 34}, {3, 35}, {4, 0},
    {4, 1},  {4, 10}, {4, 16}, {4, 20}, {4, 21}, {5, 0},  {5, 1},  {5, 10},
    {5, 14}, {5, 16}, {5, 17}, {5, 22}, {5, 24}, {6, 10}, {6, 16}, {6, 24},
    {7, 11}, {7, 15}, {8, 12}, {8, 13}};

// Last click, used to generate glider.
int lastClickedRow;
int lastClickedCol;

// Global state
bool isRunning;
int numSteps;
int numLivingCells;

// ____________________________________________________________________________
void initTerminal() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  numCols = COLS / 2;
  numRows = LINES;
}

// ____________________________________________________________________________
void initGame() {
  previousGrid = grid1;
  currentGrid = grid2;
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      setCurrent(row, col, false);
      setPrevious(row, col, false);
    }
  }

  lastClickedRow = -1;
  lastClickedCol = -1;

  isRunning = false;
  numSteps = 0;
  numLivingCells = 0;
}

// ____________________________________________________________________________
bool processUserInput(int keycode) {
  MEVENT event;
  switch (keycode) {
  case 'q':
    // Exit
    return false;
  case ' ':
    // Toggle run
    isRunning = !isRunning;
    break;
  case 's':
    // Execute step
    updateState();
    break;
  case 'c':
    // Clear all
    for (int row = 0; row < numRows; ++row) {
      for (int col = 0; col < numCols; ++col) {
        setCurrent(row, col, false);
      }
    }
    break;
  case 'r':
    // Fill randomly
    for (int row = 0; row < numRows; ++row) {
      for (int col = 0; col < numCols; ++col) {
        setCurrent(row, col, drand48() > 0.8);
      }
    }
    break;
  case 'g':
    // Generate glider
    setCurrent(lastClickedRow, lastClickedCol, false);
    for (int i = 0; i < 5; ++i) {
      int row = lastClickedRow + glider[i][0];
      int col = lastClickedCol + glider[i][1];
      setCurrent(row, col, true);
    }
    break;
  case 'G':
    // Generate glider factory
    setCurrent(lastClickedRow, lastClickedCol, false);
    for (int i = 0; i < GLIDER_FACTORY_SIZE; ++i) {
      int row = lastClickedRow + gliderFactory[i][0];
      int col = lastClickedCol + gliderFactory[i][1];
      setCurrent(row, col, true);
    }
    break;
  case KEY_MOUSE:
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_PRESSED) {
        // Store position of click and invert cell.
        // Check if the click was inside the grid:
        //
        lastClickedCol = event.x / 2;
        lastClickedRow = event.y;
        bool prev = getCurrent(lastClickedRow, lastClickedCol);
        setCurrent(lastClickedRow, lastClickedCol, !prev);
      }
    }
    break;
  }
  return true;
}

// ____________________________________________________________________________
void updateState() {
  numLivingCells = 0;

  // Exchange the grid pointers without copying the grids.
  bool *tempGrid = currentGrid;
  currentGrid = previousGrid;
  previousGrid = tempGrid;

  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      int neighbours = numAliveNeighbours(row, col);
      bool isAlive = false;
      if (getPrevious(row, col)) {
        // Stay alive if 2 or 3 neighbours are alive, die otherwise.
        isAlive = neighbours > 1 && neighbours < 4;
      } else if (neighbours == 3) {
        // Birth of a cell if exactly 3 neighbours are alive.
        isAlive = true;
      }
      // Count cells which are alive.
      numLivingCells += isAlive;
      setCurrent(row, col, isAlive);
    }
  }

  // Update the step counter.
  ++numSteps;
}

// ____________________________________________________________________________
int numAliveNeighbours(int row, int col) {
  int result = 0;
  // Check the 3x3 around the given cell.
  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      // Ignore the given cell itself
      if (dr == 0 && dc == 0) {
        continue;
      }
      result += getPrevious(row + dr, col + dc);
    }
  }
  return result;
}

// ____________________________________________________________________________
void showState() {
  // Only draw visible cells.
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      attroff(A_REVERSE);
      if (getCurrent(row, col)) {
        attron(A_REVERSE);
      }
      mvprintw(row, col * 2, "  ");
    }
  }
  attroff(A_REVERSE);
  mvprintw(0, 0, "Step: %9d Cells alive: %4d Running: %d", numSteps,
           numLivingCells, isRunning);
}

// __________________________________________________________________________
bool isLegalPosition(int row, int col) {
  return (row >= 0) && (col >= 0) && (row < numRows) && (col < numCols);
}

// __________________________________________________________________________
bool get(int row, int col, bool isPrevious) {
  // return false for out-of-bounds access.
  if (!isLegalPosition(row, col)) {
    return false;
  }
  int idx = row * numCols + col;
  bool *grid = isPrevious ? previousGrid : currentGrid;
  return grid[idx];
}

bool getPrevious(int row, int col) { return get(row, col, true); }

bool getCurrent(int row, int col) { return get(row, col, false); }

// __________________________________________________________________________
void set(int row, int col, bool value, bool isPrevious) {
  // do nothing for out of bounds acces.
  if (!isLegalPosition(row, col)) {
    return;
  }
  int idx = row * numCols + col;
  bool *grid = isPrevious ? previousGrid : currentGrid;
  grid[idx] = value;
}

void setPrevious(int row, int col, bool value) { set(row, col, value, true); }

void setCurrent(int row, int col, bool value) { set(row, col, value, false); }
