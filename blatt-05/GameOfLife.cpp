// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>,
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#include "./GameOfLife.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ____________________________________________________________________________
GameOfLife::GameOfLife(TerminalManager *terminalManager)
    : terminalManager_{terminalManager} {
  if (terminalManager_ == nullptr) {
    return;
  }
  numRows_ = terminalManager_->numRows();
  numCols_ = terminalManager_->numCols();
}

// ____________________________________________________________________________
void GameOfLife::play() {
  if (terminalManager_ == nullptr) {
    return;
  }
  while (processUserInput(terminalManager_->getUserInput())) {
    if (isRunning_) {
      updateState();
    }
    // Draw and wait.
    showState();
    usleep(20'000);
  }
}

// ____________________________________________________________________________
bool GameOfLife::processUserInput(UserInput userInput) {

  if (userInput.isMouseclick()) {
    lastClickedCol_ = userInput.mouseCol_;
    lastClickedRow_ = userInput.mouseRow_;
    bool prev = getCurrent(lastClickedRow_, lastClickedCol_);
    setCurrent(lastClickedRow_, lastClickedCol_, !prev);
    return true;
  }
  switch (userInput.keycode_) {
  case 'q':
    // Exit
    return false;
  case ' ':
    // Toggle run
    isRunning_ = !isRunning_;
    break;
  case 's':
    // Execute step
    updateState();
    break;
  case 'c':
    // Clear all
    for (int row = 0; row < numRows_; ++row) {
      for (int col = 0; col < numCols_; ++col) {
        setCurrent(row, col, false);
      }
    }
    break;
  case 'r':
    // Fill randomly
    for (int row = 0; row < numRows_; ++row) {
      for (int col = 0; col < numCols_; ++col) {
        setCurrent(row, col, drand48() > 0.8);
      }
    }
    break;
  case 'g':
    // Generate glider
    setCurrent(lastClickedRow_, lastClickedCol_, false);
    for (int i = 0; i < 5; ++i) {
      int row = lastClickedRow_ + GLIDER[i][0];
      int col = lastClickedCol_ + GLIDER[i][1];
      setCurrent(row, col, true);
    }
    break;
  }
  return true;
}

// ____________________________________________________________________________
void GameOfLife::updateState() {
  numLivingCells_ = 0;

  // Exchange the grid pointers without copying the grids.
  bool *tempGrid = currentGrid_;
  currentGrid_ = previousGrid_;
  previousGrid_ = tempGrid;

  for (int row = 0; row < numRows_; ++row) {
    for (int col = 0; col < numCols_; ++col) {
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
      numLivingCells_ += isAlive;
      setCurrent(row, col, isAlive);
    }
  }

  // Update the step counter.
  ++numSteps_;
}

// ____________________________________________________________________________
int GameOfLife::numAliveNeighbours(int row, int col) {
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
void GameOfLife::showState() {
  // Only draw visible cells.
  for (int row = 0; row < numRows_; ++row) {
    for (int col = 0; col < numCols_; ++col) {
      int color =
          getCurrent(row, col) ? TerminalManager::Red : TerminalManager::White;
      terminalManager_->drawPixel(row, col, color);
    }
  }
  // Print the statistics, optional for sheet-05
  const int bufSize = 100;
  char buffer[bufSize];
  snprintf(buffer, bufSize, "Step: %9d Cells alive: %4d Running: %d", numSteps_,
           numLivingCells_, isRunning_);
  terminalManager_->drawString(0, 0, buffer);
  terminalManager_->refresh();
}

// __________________________________________________________________________
bool GameOfLife::isLegalPosition(int row, int col) {
  return (row >= 0) && (col >= 0) && (row < numRows_) && (col < numCols_);
}

// __________________________________________________________________________
bool GameOfLife::get(int row, int col, bool isPrevious) {
  // return false for out-of-bounds access.
  if (!isLegalPosition(row, col)) {
    return false;
  }
  int idx = row * numCols_ + col;
  bool *grid = isPrevious ? previousGrid_ : currentGrid_;
  return grid[idx];
}

bool GameOfLife::getPrevious(int row, int col) { return get(row, col, true); }

bool GameOfLife::getCurrent(int row, int col) { return get(row, col, false); }

// __________________________________________________________________________
void GameOfLife::set(int row, int col, bool value, bool isPrevious) {
  // do nothing for out of bounds acces.
  if (!isLegalPosition(row, col)) {
    return;
  }
  int idx = row * numCols_ + col;
  bool *grid = isPrevious ? previousGrid_ : currentGrid_;
  grid[idx] = value;
}

void GameOfLife::setPrevious(int row, int col, bool value) {
  set(row, col, value, true);
}

void GameOfLife::setCurrent(int row, int col, bool value) {
  set(row, col, value, false);
}
