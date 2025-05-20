//
// Created by Paul Schaffrath on 28.07.24.
//

#pragma once

#include <gtest/gtest.h>
#include <vector>

#include <Playfield.h>

// ______ Playfield Class Forard declaration ______
class Playfield;

class Tetromino {
public:
  // ______ Definitions ______
  enum Shape { I, J, L, S, Z, T, O };

  // ______ Constructor ______
  explicit Tetromino(Shape shape);

  // ______ Getters ______
  std::vector<std::vector<bool>> blocks() const { return blocks_; }
  Shape shape() const { return shape_; }
  int x() const { return x_; }
  int y() const { return y_; }
  int color() const { return color_; }

  // ______ Movement ______
  void moveLeft() { x_--; }
  void moveRight() { x_++; }
  void moveDown() { y_++; }

  int hardDrop(const Playfield &playfield);

  // ______ Rotation ______
  void rotateCW();

  void rotateCW(const Playfield &playfield);

  void rotateCCW(const Playfield &playfield);

  // ______ Check for possible movement ______
  bool canMoveLeft(const Playfield &playfield) const;
  bool canMoveRight(const Playfield &playfield) const;
  bool canMoveDown(const Playfield &playfield) const;
  bool canRotateCW(const Playfield &playfield) const;
  bool canRotateCCW(const Playfield &playfield) const;

  // ______ Check for valid position ______
  bool isOutsideLeft() const;
  bool isOutsideRight() const;

  bool isValidPosition(const std::vector<std::vector<bool>> &newBlocks,
                       const Playfield &playfield, int newX, int newY) const;

  // ______ Lock Tetromino ______
  void lock(const Playfield &playfield);

private:
  // ______ Blockgrid ______
  std::vector<std::vector<bool>> blocks_;

  // _____ Shape ______
  Shape shape_;

  // ______ Position ______
  int x_;
  int y_ = 1;

  // ______ Color ______
  int color_;

  FRIEND_TEST(PlayfieldTest, isValidPosition);
  FRIEND_TEST(TetrominoTest, canMoveLeft);
  FRIEND_TEST(TetrominoTest, canMoveLeft2);
  FRIEND_TEST(TetrominoTest, canMoveRight);
  FRIEND_TEST(TetrominoTest, canMoveRight2);
  FRIEND_TEST(TetrominoTest, canMoveDown);
  FRIEND_TEST(TetrominoTest, canMoveDown2);
  FRIEND_TEST(TetrominoTest, canRotateCW);
  FRIEND_TEST(TetrominoTest, canRotateCCW);
};
