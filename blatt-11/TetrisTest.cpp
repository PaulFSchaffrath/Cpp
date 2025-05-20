//
// Created by Paul Schaffrath on 03.07.24.
//

#include "Tetris.h"
#include "Playfield.h"
#include "Tetromino.h"
#include "TetrominoShapes.h"
#include <gtest/gtest.h>

// Test the TetrominoShape class

// Test the initializeShapes method (size should be 7)
TEST(TetrominoShapes, InitializeShapes) {
  TetrominoShape::initializeShapes();
  const std::vector<std::vector<std::vector<int>>> shapes =
      TetrominoShape::shapes;
  ASSERT_EQ(shapes.size(), 7u);
}

// Test the constructor
TEST(Tetromino, Constructor) {
  const Tetromino tetromino(I);
  ASSERT_EQ(tetromino.shape(), I);
  ASSERT_EQ(tetromino.rotation(), 0);
  ASSERT_EQ(tetromino.x(), 5);
  ASSERT_EQ(tetromino.y(), 0);
}

// Test the move methods
TEST(Tetromino, MoveLeft) {
  Tetromino tetromino(I);
  tetromino.moveLeft();
  ASSERT_EQ(tetromino.x(), 4);
}
TEST(Tetromino, MoveRight) {
  Tetromino tetromino(I);
  tetromino.moveRight();
  ASSERT_EQ(tetromino.x(), 6);
}
TEST(Tetromino, MoveDown) {
  Tetromino tetromino(I);
  tetromino.moveDown();
  ASSERT_EQ(tetromino.y(), 1);
}

// Test the rotate method
TEST(Tetromino, Rotate) {
  Tetromino tetromino(I);
  tetromino.rotate();
  ASSERT_EQ(tetromino.rotation(), 1);
  tetromino.rotate();
  ASSERT_EQ(tetromino.rotation(), 2);
  tetromino.rotate();
  ASSERT_EQ(tetromino.rotation(), 3);
  tetromino.rotate();
  ASSERT_EQ(tetromino.rotation(), 0);
}

// Test the Playfield class
TEST(Playfield, Constructor) {
  Playfield playfield;
  ASSERT_EQ(playfield.WIDTH, 10);
  ASSERT_EQ(playfield.HEIGHT, 20);
}

// Test the isFieldEmpty method
TEST(Playfield, IsFieldEmpty) {
  Playfield playfield;
  ASSERT_TRUE(playfield.isFieldEmpty());
  playfield.setCell(Cell(5, 5, 1, true));
  ASSERT_FALSE(playfield.isFieldEmpty());
}

// Test the clear method
TEST(Playfield, Clear) {
  Playfield playfield;
  playfield.setCell(Cell(5, 5, 1, true));
  ASSERT_FALSE(playfield.isFieldEmpty());
  playfield.clearField();
  ASSERT_TRUE(playfield.isFieldEmpty());
}

// Test the set method
TEST(Playfield, Set) {
  Playfield playfield;
  playfield.setCell(Cell(5, 5, 1, true));
  ASSERT_EQ(playfield.getCell(5, 5).getColor(), 1);
}