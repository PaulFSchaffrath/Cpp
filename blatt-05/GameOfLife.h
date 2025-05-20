// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#pragma once

#include "./TerminalManager.h"
#include <gtest/gtest.h>
//#include "./OpenGLTerminalManager.h"
// using TerminalManager = OpenGLTerminalManager;

class GameOfLife {
private:
  // The maximal number of cells, and the actual number of cells that is used by
  // the game.
  static const int MAX_NUM_CELLS = 1'000'000;
  // Glider.
  static constexpr int GLIDER[5][2] = {{1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}};

  int numCols_ = 100;
  int numRows_ = 100;

  // The two grids used to store the current and next state
  //
  bool gridA_[MAX_NUM_CELLS] = {};
  bool gridB_[MAX_NUM_CELLS] = {};
  // The two pointers to the current and previous grid, they are switched after
  // each iteration.
  bool *previousGrid_ = gridA_;
  bool *currentGrid_ = gridB_;

  // Last coordinate clicked inside grid.
  int lastClickedCol_ = -1;
  int lastClickedRow_ = -1;

  // Additional global state
  bool isRunning_ = false;
  int numSteps_ = 0;
  int numLivingCells_ = 0;

  TerminalManager *terminalManager_ = nullptr;

public:
  GameOfLife(TerminalManager *terminalManager = nullptr);
  void play();

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

  // Handle key and mouse presses. Change the new grid.
  bool processUserInput(UserInput userInput);

  // Calculate the next state and write it into new grid.
  void updateState();

  // Count the number of alive cells around given coordinates in the old grid.
  int numAliveNeighbours(int row, int col);

  // Draw the new grid using ncurses.
  void showState();

  // Additional helper functions not explicitly mentioned in the sheet.
  // Returns true if the coordinates (x, y) are inside the grid
  bool isLegalPosition(int row, int col);

  // friend declarations for Gtest
  // friend declarations for Gtest
  // friend declarations for Gtest
  // friend declarations for Gtest
  // friend declarations for Gtest
  // friend declarations for Gtest
  // friend declarations for Gtest
  // friend declarations for Gtest
  FRIEND_TEST(GameOfLife, numAliveNeighboursSingle);
  FRIEND_TEST(GameOfLife, numAliveNeighboursMultiple);
  FRIEND_TEST(GameOfLife, numAliveNeighboursSingle);
  FRIEND_TEST(GameOfLife, processUserInputQuit);
  FRIEND_TEST(GameOfLife, processUserInputSpace);
  FRIEND_TEST(GameOfLife, processUserInputSmallS);
  FRIEND_TEST(GameOfLife, processUserInputSmallG);
  FRIEND_TEST(GameOfLife, processUserInputSmallR);
  FRIEND_TEST(GameOfLife, updateStateEmptyGrid);
  FRIEND_TEST(GameOfLife, updateStateStaticObject);
  FRIEND_TEST(GameOfLife, updateStateP2Blinker);
  FRIEND_TEST(GameOfLife, processUserInputSmallR);
};
