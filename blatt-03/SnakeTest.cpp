// Copyright 2024, University of Freiburg
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
#include <gtest/gtest.h>
#include <ncurses.h>

#include "./Snake.h"

// NOTE: We can't use "initTerminal" inside the test, so we have to manually
// set numPixelsX and numPixelsY in the test cases.

// ___________________________________________________________________________
TEST(SnakeTest, initGame) {
  numPixelsX = 100;
  numPixelsY = 100;

  initGame();
  ASSERT_EQ(posX, 50);
  ASSERT_EQ(posY, 50);

  ASSERT_EQ(vx, 1);
  ASSERT_EQ(vy, 0);
}

// ___________________________________________________________________________
TEST(SnakeTest, moveSnake) {
  numPixelsX = 100;
  numPixelsY = 100;

  // Default direction is right
  moveSnake();
  // All y-coordinates are the same, all x-coordinates one more than initially.
  ASSERT_EQ(posX, 51);
  ASSERT_EQ(posY, 50);

  // Manually set the direction.
  vx = 0;
  vy = 1;
  moveSnake();
  // the head moves y+1, the other elements are shifted.
  //
  ASSERT_EQ(posX, 51);
  ASSERT_EQ(posY, 51);
}

// ___________________________________________________________________________
TEST(SnakeTest, handleKey) {
  initGame();
  // The snake is moving right because of the default in `initGame`
  ASSERT_EQ(vx, 1);
  ASSERT_EQ(vy, 0);

  // Press KEY_RIGHT, snake is still moving right.
  ASSERT_TRUE(handleKey(KEY_RIGHT));
  ASSERT_EQ(vx, 1);
  ASSERT_EQ(vy, 0);

  // Press KEY_LEFT, snake is still moving right (the direction change would be
  // illega)
  ASSERT_TRUE(handleKey(KEY_LEFT));
  ASSERT_EQ(vx, 1);
  ASSERT_EQ(vy, 0);

  // Press KEY_UP
  ASSERT_TRUE(handleKey(KEY_UP));
  ASSERT_EQ(vx, 0);
  ASSERT_EQ(vy, -1);

  // Press KEY_DOWN (nothing happens again
  ASSERT_TRUE(handleKey(KEY_DOWN));
  ASSERT_EQ(vx, 0);
  ASSERT_EQ(vy, -1);

  // now we can move left.
  // Press KEY_LEFT_
  ASSERT_TRUE(handleKey(KEY_LEFT));
  ASSERT_EQ(vx, -1);
  ASSERT_EQ(vy, 0);

  // but no right
  // Press KEY_LEFT_
  ASSERT_TRUE(handleKey(KEY_RIGHT));
  ASSERT_EQ(vx, -1);
  ASSERT_EQ(vy, 0);

  // Press KEY_DOWN
  ASSERT_TRUE(handleKey(KEY_DOWN));
  ASSERT_EQ(vx, 0);
  ASSERT_EQ(vy, 1);

  // Press KEY_UP, no change indirection
  ASSERT_TRUE(handleKey(KEY_UP));
  ASSERT_EQ(vx, 0);
  ASSERT_EQ(vy, 1);

  // Pressing no key doesn't change anything.
  ASSERT_TRUE(handleKey(-1));
  ASSERT_EQ(vx, 0);
  ASSERT_EQ(vy, 1);

  // Pressing any unsupported key doesn't change anything.
  ASSERT_TRUE(handleKey('a'));
  ASSERT_EQ(vx, 0);
  ASSERT_EQ(vy, 1);

  // Pressing ESCAPE returns false.
  ASSERT_FALSE(handleKey(27));
}

// ____________________________________________________________________________
TEST(SnakeTest, collidesWithBorder) {
  numPixelsX = 100;
  numPixelsY = 100;

  initGame();
  ASSERT_EQ(posX, 50);
  // The snake is moving right, so after 48 moves we are at pixel 98
  // which is the last legal one (pixels are from 0 to 99, and 99 is
  // the border.
  ASSERT_FALSE(collidesWithBorder());
  for (int i = 0; i < 48; i++) {
    moveSnake();
    ASSERT_FALSE(collidesWithBorder());
  }

  // One more move and we collide.
  moveSnake();
  ASSERT_TRUE(collidesWithBorder());
}
