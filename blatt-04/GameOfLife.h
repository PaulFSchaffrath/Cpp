// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#pragma once
// The maximal number of cells, and the actual number of cells that is used by
// the game.
const int MAX_NUM_CELLS = 1'000'000;
extern int numCols;
extern int numRows;

// The two pointers to the current and previous grid, they are switched after
// each iteration.
extern bool *previousGrid;
extern bool *currentGrid;

// Last coordinate clicked inside grid.
extern int lastClickedCol;
extern int lastClickedRow;

// Additional global state
extern bool isRunning;
extern int numSteps;
extern int numLivingCells;

// Functions that get or set the previous or current grid value at a given
// position.
void setPrevious(int row, int col, bool value);
void setCurrent(int row, int col, bool value);
bool getCurrent(int row, int col);
bool getPrevious(int row, int col);

// The implementation of the four functions above.
void set(int row, int col, bool value, bool usePrevious);
bool get(int row, int col, bool usePrevious);

// Initialize the terminal
void initTerminal();

// Initialize the game
void initGame();

// Handle key and mouse presses. Change the new grid.
bool processUserInput(int keycode);

// Calculate the next state and write it into new grid.
void updateState();

// Count the number of alive cells around given coordinates in the old grid.
int numAliveNeighbours(int row, int col);

// Draw the new grid using ncurses.
void showState();

// Additional helper functions not explicitly mentioned in the sheet.
// Returns true if the coordinates (x, y) are inside the grid
bool isLegalPosition(int row, int col);
