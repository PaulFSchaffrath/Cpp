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
  GameOfLife g;
  // Test empty field and border handling.
  for (int row = 0; row < g.numRows_; ++row) {
    for (int col = 0; col < g.numCols_; ++col) {
      ASSERT_EQ(0, g.numAliveNeighbours(row, col));
    }
  }

  // Test for only neigbours are counted.
  g.setPrevious(2, 1, true);
  ASSERT_EQ(1, g.numAliveNeighbours(1, 0));
  ASSERT_EQ(1, g.numAliveNeighbours(2, 0));
  ASSERT_EQ(1, g.numAliveNeighbours(3, 0));
  ASSERT_EQ(1, g.numAliveNeighbours(1, 1));
  ASSERT_EQ(0, g.numAliveNeighbours(2, 1));
  ASSERT_EQ(1, g.numAliveNeighbours(3, 1));
  ASSERT_EQ(1, g.numAliveNeighbours(1, 2));
  ASSERT_EQ(1, g.numAliveNeighbours(2, 2));
  ASSERT_EQ(1, g.numAliveNeighbours(3, 2));
}

TEST(GameOfLife, numAliveNeighboursMultiple) {
  GameOfLife g;

  // Test for only neigbours are counted.
  g.setPrevious(4, 4, true);
  g.setPrevious(4, 5, true);
  g.setPrevious(5, 4, true);
  g.setPrevious(5, 5, true);
  ASSERT_EQ(1, g.numAliveNeighbours(3, 3));
  ASSERT_EQ(2, g.numAliveNeighbours(3, 4));
  ASSERT_EQ(2, g.numAliveNeighbours(3, 5));
  ASSERT_EQ(1, g.numAliveNeighbours(3, 6));
  ASSERT_EQ(2, g.numAliveNeighbours(4, 3));
  ASSERT_EQ(3, g.numAliveNeighbours(4, 4));
  ASSERT_EQ(3, g.numAliveNeighbours(4, 5));
  ASSERT_EQ(2, g.numAliveNeighbours(4, 6));
  ASSERT_EQ(2, g.numAliveNeighbours(5, 3));
  ASSERT_EQ(3, g.numAliveNeighbours(5, 4));
  ASSERT_EQ(3, g.numAliveNeighbours(5, 5));
  ASSERT_EQ(2, g.numAliveNeighbours(5, 6));
  ASSERT_EQ(1, g.numAliveNeighbours(6, 3));
  ASSERT_EQ(2, g.numAliveNeighbours(6, 4));
  ASSERT_EQ(2, g.numAliveNeighbours(6, 5));
  ASSERT_EQ(1, g.numAliveNeighbours(6, 6));
}

TEST(GameOfLife, processUserInputQuit) {
  GameOfLife g;
  UserInput u;
  u.keycode_ = 'q';
  ASSERT_FALSE(g.processUserInput(u));
}

TEST(GameOfLife, processUserInputSpace) {
  GameOfLife g;
  g.isRunning_ = false;
  UserInput u;
  u.keycode_ = ' ';
  ASSERT_TRUE(g.processUserInput(u));
  ASSERT_TRUE(g.isRunning_);
  ASSERT_TRUE(g.processUserInput(u));
  ASSERT_FALSE(g.isRunning_);
}

TEST(GameOfLife, processUserInputSmallS) {
  GameOfLife g;
  g.numSteps_ = 0;
  UserInput u;
  u.keycode_ = 's';
  ASSERT_TRUE(g.processUserInput(u));
  ASSERT_EQ(g.numSteps_, 1);
}

TEST(GameOfLife, processUserInputSmallG) {
  GameOfLife g;
  // Glider is 3x3

  g.lastClickedRow_ = 3;
  g.lastClickedCol_ = 3;
  UserInput u;
  u.keycode_ = 'g';
  ASSERT_TRUE(g.processUserInput(u));
  int count = 0;
  for (int row = g.lastClickedRow_; row < g.lastClickedRow_ + 3; ++row) {
    for (int col = g.lastClickedCol_; col < g.lastClickedCol_ + 3; ++col) {
      count += g.getCurrent(row, col);
    }
  }
  ASSERT_EQ(5, count);
}

TEST(GameOfLife, processUserInputSmallR) {
  GameOfLife g;
  UserInput u;
  u.keycode_ = 'r';
  ASSERT_TRUE(g.processUserInput(u));
  int count = 0;
  for (int row = 0; row < g.numRows_; ++row) {
    for (int col = 0; col < g.numCols_; ++col) {
      count += g.getCurrent(row, col);
    }
  }
  // Chance is 1/5, so we shall have more than 1/6 ...
  ASSERT_LT((g.numRows_ * g.numCols_ / 6), count);
  // but less than 1/4 of total cells numAlive.
  ASSERT_GT((g.numRows_ * g.numCols_ / 4), count);
}

TEST(GameOfLife, updateStateEmptyGrid) {
  GameOfLife g;
  // Empty stays empty
  g.updateState();
  ASSERT_EQ(0, g.numLivingCells_);
  for (int row = 0; row < g.numRows_; ++row) {
    for (int col = 0; col < g.numRows_; ++col) {
      ASSERT_FALSE(g.getPrevious(row, col));
      ASSERT_FALSE(g.getPrevious(row, col));
    }
  }
}

TEST(GameOfLife, updateStateStaticObject) {
  GameOfLife g;
  g.setCurrent(4, 4, true);
  g.setCurrent(4, 5, true);
  g.setCurrent(5, 4, true);
  g.setCurrent(5, 5, true);
  g.updateState();
  ASSERT_EQ(4, g.numLivingCells_);
  ASSERT_FALSE(g.getCurrent(3, 3));
  ASSERT_FALSE(g.getCurrent(3, 4));
  ASSERT_FALSE(g.getCurrent(3, 5));
  ASSERT_FALSE(g.getCurrent(3, 6));
  ASSERT_FALSE(g.getCurrent(4, 3));
  ASSERT_TRUE(g.getCurrent(4, 4));
  ASSERT_TRUE(g.getCurrent(4, 5));
  ASSERT_FALSE(g.getCurrent(4, 6));
  ASSERT_FALSE(g.getCurrent(5, 3));
  ASSERT_TRUE(g.getCurrent(5, 4));
  ASSERT_TRUE(g.getCurrent(5, 5));
  ASSERT_FALSE(g.getCurrent(5, 6));
  ASSERT_FALSE(g.getCurrent(6, 3));
  ASSERT_FALSE(g.getCurrent(6, 4));
  ASSERT_FALSE(g.getCurrent(6, 5));
  ASSERT_FALSE(g.getCurrent(6, 6));
}

TEST(GameOfLife, updateStateP2Blinker) {
  GameOfLife g;
  // Tests updateState function with a period 2 blinker.
  // -
  g.setCurrent(4, 4, true);
  g.setCurrent(4, 5, true);
  g.setCurrent(4, 6, true);
  // |
  g.updateState();
  ASSERT_EQ(3, g.numLivingCells_);
  ASSERT_FALSE(g.getCurrent(3, 4));
  ASSERT_TRUE(g.getCurrent(3, 5));
  ASSERT_FALSE(g.getCurrent(3, 6));
  ASSERT_FALSE(g.getCurrent(4, 4));
  ASSERT_TRUE(g.getCurrent(4, 5));
  ASSERT_FALSE(g.getCurrent(4, 6));
  ASSERT_FALSE(g.getCurrent(5, 4));
  ASSERT_TRUE(g.getCurrent(5, 5));
  ASSERT_FALSE(g.getCurrent(5, 6));
  // -
  g.updateState();
  ASSERT_EQ(3, g.numLivingCells_);
  ASSERT_FALSE(g.getCurrent(3, 4));
  ASSERT_FALSE(g.getCurrent(3, 5));
  ASSERT_FALSE(g.getCurrent(3, 6));
  ASSERT_TRUE(g.getCurrent(4, 4));
  ASSERT_TRUE(g.getCurrent(4, 5));
  ASSERT_TRUE(g.getCurrent(4, 6));
  ASSERT_FALSE(g.getCurrent(5, 4));
  ASSERT_FALSE(g.getCurrent(5, 5));
  ASSERT_FALSE(g.getCurrent(5, 6));
}
