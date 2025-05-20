//
// Created by Paul Schaffrath on 28.07.24.
//

#pragma once

#include <Tetromino.h>
#include <gtest/gtest.h>

// ______ Tetromino Class Fastfiorward declaration ______
class Tetromino;

class Playfield {
  // ______ Playfield ______
  int playfield_[10][22] = {{}};

  // ______ Check if a row is full ______
  [[nodiscard]] bool isRowFull(int row) const;

  // ______ Clear a row ______
  void clearRow(int row);

  // ______ Tests for private member variables ______
  // ______ Playfield Tests ______
  FRIEND_TEST(PlayfieldTest, isRowFull);
  FRIEND_TEST(PlayfieldTest, clearRow);
  FRIEND_TEST(PlayfieldTest, getPlayfield);
  FRIEND_TEST(PlayfieldTest, fullRowsCleared);
  FRIEND_TEST(PlayfieldTest, lockTetromino);
  FRIEND_TEST(PlayfieldTest, isValidPosition);
  FRIEND_TEST(PlayfieldTest, clearField);
  // ______ Tetromino Tests ______
  FRIEND_TEST(TetrominoTest, canMoveLeft2);
  FRIEND_TEST(TetrominoTest, canMoveRight2);
  FRIEND_TEST(TetrominoTest, canMoveDown2);

public:
  // ______ Constructor and Destructor______
  Playfield() = default;
  ~Playfield() = default;

  // ______ Getter ______
  int getPlayfield(int x, int y) const;

  // ______ Remove all full rows _______
  int fullRowsCleared();

  // ______ Lock the tetromino _______
  void lockTetromino(const std::unique_ptr<Tetromino> &tetromino);

  // ______ Check if a tetromino can be placed at a given position _______
  [[nodiscard]] bool
  isValidPosition(const std::vector<std::vector<bool>> &blocks, int newX,
                  int newY) const;

  // ______ Clear the field ______
  void clearField();
};
