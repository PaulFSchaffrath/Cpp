// Copyright 2024, Paul Schaffrath

#include "./Snake.h"
#include <gtest/gtest.h>
#include <ncurses.h>

TEST(Snake, initGame) {
  windowWidth = 60;
  windowHeight = 30;
  initGame();
  ASSERT_EQ(xPos, 30);
  ASSERT_EQ(yPos, 15);
}

TEST(Snake, moveSnake) {
  // Test1
  xPos = 10;
  yPos = 20;
  rotation = 3;
  moveSnake();
  ASSERT_EQ(xPos, 10);
  ASSERT_EQ(yPos, 19);

  // Test2
  xPos = 10;
  yPos = 20;
  rotation = 0;
  moveSnake();
  ASSERT_EQ(xPos, 12);
  ASSERT_EQ(yPos, 20);
}

TEST(Snake, collidesWithBorder) {
  // Test1
  xPos = -3;
  yPos = 20;
  ASSERT_EQ(collidesWithBorder(), true);
  // Test2
  xPos = 3;
  yPos = 20;
  ASSERT_EQ(collidesWithBorder(), false);
  // Test3
  xPos = 3;
  yPos = 0;
  ASSERT_EQ(collidesWithBorder(), true);
}

TEST(Snake, handleKey) {
  // Test1
  rotation = 0;
  ASSERT_EQ(handleKey(KEY_DOWN), false);
  // Test2
  ASSERT_EQ(handleKey(27), true);
}