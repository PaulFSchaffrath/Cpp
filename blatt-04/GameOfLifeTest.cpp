// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

// IMPORTANT:
// You are not required to write this many tests in your solution.

#include "./GameOfLife.h"
#include <gtest/gtest.h>

TEST(GameOfLife, numAliveNeighboursSingle) {
  initGame();
  // Test empty field and border handling.
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      ASSERT_EQ(0, numAliveNeighbours(row, col));
    }
  }

  // Test for only neigbours are counted.
  setPrevious(2, 1, true);
  ASSERT_EQ(1, numAliveNeighbours(1, 0));
  ASSERT_EQ(1, numAliveNeighbours(2, 0));
  ASSERT_EQ(1, numAliveNeighbours(3, 0));
  ASSERT_EQ(1, numAliveNeighbours(1, 1));
  ASSERT_EQ(0, numAliveNeighbours(2, 1));
  ASSERT_EQ(1, numAliveNeighbours(3, 1));
  ASSERT_EQ(1, numAliveNeighbours(1, 2));
  ASSERT_EQ(1, numAliveNeighbours(2, 2));
  ASSERT_EQ(1, numAliveNeighbours(3, 2));
}

TEST(GameOfLife, numAliveNeighboursMultiple) {
  initGame();

  // Test for only neigbours are counted.
  setPrevious(4, 4, true);
  setPrevious(4, 5, true);
  setPrevious(5, 4, true);
  setPrevious(5, 5, true);
  ASSERT_EQ(1, numAliveNeighbours(3, 3));
  ASSERT_EQ(2, numAliveNeighbours(3, 4));
  ASSERT_EQ(2, numAliveNeighbours(3, 5));
  ASSERT_EQ(1, numAliveNeighbours(3, 6));
  ASSERT_EQ(2, numAliveNeighbours(4, 3));
  ASSERT_EQ(3, numAliveNeighbours(4, 4));
  ASSERT_EQ(3, numAliveNeighbours(4, 5));
  ASSERT_EQ(2, numAliveNeighbours(4, 6));
  ASSERT_EQ(2, numAliveNeighbours(5, 3));
  ASSERT_EQ(3, numAliveNeighbours(5, 4));
  ASSERT_EQ(3, numAliveNeighbours(5, 5));
  ASSERT_EQ(2, numAliveNeighbours(5, 6));
  ASSERT_EQ(1, numAliveNeighbours(6, 3));
  ASSERT_EQ(2, numAliveNeighbours(6, 4));
  ASSERT_EQ(2, numAliveNeighbours(6, 5));
  ASSERT_EQ(1, numAliveNeighbours(6, 6));
}

TEST(GameOfLife, processUserInputQuit) { ASSERT_FALSE(processUserInput('q')); }

TEST(GameOfLife, processUserInputSpace) {
  isRunning = false;
  ASSERT_TRUE(processUserInput(' '));
  ASSERT_TRUE(isRunning);
  ASSERT_TRUE(processUserInput(' '));
  ASSERT_FALSE(isRunning);
}

TEST(GameOfLife, processUserInputSmallS) {
  initGame();
  numSteps = 0;
  ASSERT_TRUE(processUserInput('s'));
  ASSERT_EQ(numSteps, 1);
}

TEST(GameOfLife, processUserInputSmallG) {
  initGame();
  // Glider is 3x3

  lastClickedRow = 3;
  lastClickedCol = 3;
  ASSERT_TRUE(processUserInput('g'));
  int count = 0;
  for (int row = lastClickedRow; row < lastClickedRow + 3; ++row) {
    for (int col = lastClickedCol; col < lastClickedCol + 3; ++col) {
      count += getCurrent(row, col);
    }
  }
  ASSERT_EQ(5, count);
}

TEST(GameOfLife, processUserInputSmallR) {
  initGame();
  ASSERT_TRUE(processUserInput('r'));
  int count = 0;
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      count += getCurrent(row, col);
    }
  }
  // Chance is 1/5, so we shall have more than 1/6 ...
  ASSERT_LT((numRows * numCols / 6), count);
  // but less than 1/4 of total cells numAlive.
  ASSERT_GT((numRows * numCols / 4), count);
}

TEST(GameOfLife, updateStateEmptyGrid) {
  // Empty stays empty
  initGame();
  updateState();
  ASSERT_EQ(0, numLivingCells);
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      ASSERT_FALSE(getPrevious(row, col));
      ASSERT_FALSE(getCurrent(row, col));
    }
  }
}

TEST(GameOfLife, updateStateStaticObject) {
  initGame();
  setCurrent(4, 4, true);
  setCurrent(4, 5, true);
  setCurrent(5, 4, true);
  setCurrent(5, 5, true);
  updateState();
  ASSERT_EQ(4, numLivingCells);
  ASSERT_FALSE(getCurrent(3, 3));
  ASSERT_FALSE(getCurrent(3, 4));
  ASSERT_FALSE(getCurrent(3, 5));
  ASSERT_FALSE(getCurrent(3, 6));
  ASSERT_FALSE(getCurrent(4, 3));
  ASSERT_TRUE(getCurrent(4, 4));
  ASSERT_TRUE(getCurrent(4, 5));
  ASSERT_FALSE(getCurrent(4, 6));
  ASSERT_FALSE(getCurrent(5, 3));
  ASSERT_TRUE(getCurrent(5, 4));
  ASSERT_TRUE(getCurrent(5, 5));
  ASSERT_FALSE(getCurrent(5, 6));
  ASSERT_FALSE(getCurrent(6, 3));
  ASSERT_FALSE(getCurrent(6, 4));
  ASSERT_FALSE(getCurrent(6, 5));
  ASSERT_FALSE(getCurrent(6, 6));
}

TEST(GameOfLife, updateStateP2Blinker) {
  // Tests updateState function with a period 2 blinker.
  initGame();
  // -
  setCurrent(4, 4, true);
  setCurrent(4, 5, true);
  setCurrent(4, 6, true);
  // |
  updateState();
  ASSERT_EQ(3, numLivingCells);
  ASSERT_FALSE(getCurrent(3, 4));
  ASSERT_TRUE(getCurrent(3, 5));
  ASSERT_FALSE(getCurrent(3, 6));
  ASSERT_FALSE(getCurrent(4, 4));
  ASSERT_TRUE(getCurrent(4, 5));
  ASSERT_FALSE(getCurrent(4, 6));
  ASSERT_FALSE(getCurrent(5, 4));
  ASSERT_TRUE(getCurrent(5, 5));
  ASSERT_FALSE(getCurrent(5, 6));
  // -
  updateState();
  ASSERT_EQ(3, numLivingCells);
  ASSERT_FALSE(getCurrent(3, 4));
  ASSERT_FALSE(getCurrent(3, 5));
  ASSERT_FALSE(getCurrent(3, 6));
  ASSERT_TRUE(getCurrent(4, 4));
  ASSERT_TRUE(getCurrent(4, 5));
  ASSERT_TRUE(getCurrent(4, 6));
  ASSERT_FALSE(getCurrent(5, 4));
  ASSERT_FALSE(getCurrent(5, 5));
  ASSERT_FALSE(getCurrent(5, 6));
}
