//
// Created by Paul Schaffrath on 03.07.24.
//

#pragma once

#include "Cell.h"
#include <utility>
#include <vector>

enum TetrominoType { I, L, J, Z, S, O, T };

class Tetromino {
private:
  static int nextId;
  int id_;
  int shape_;
  std::pair<int, int> position_;
  bool locked_;
  bool alive_;
  int color_;
  int rotationState_;
  std::vector<Cell> cells_;
  int width_;

  // Set random shape and color for the specific shape
  void setRandomShape(TetrominoType lastType);

public:
  // Constructor
  explicit Tetromino(TetrominoType type);

  // Destructor
  ~Tetromino();

  // Move the Tetromino to the left
  void moveLeft();

  // Move the Tetromino to the right
  void moveRight();

  // Move the Tetromino down
  void moveDown();

  // Drop the Tetromino
  void drop();

  // Rotate the Tetromino clockwise
  void rotate();

  // Reset the Tetromino
  void reset(TetrominoType type);

  // Get the cells of the Tetromino
  const std::vector<Cell> &getCells() const;

  // Static tetromino shapes
  static const std::vector<std::vector<std::vector<int>>> tetrominoShapes;

  bool isTouchingLeftWall() const;
  bool isTouchingRightWall() const;

  void initShape();

  // Getter
  int shape() const { return shape_; };            // Between 0 and 6
  int x() const { return position_.first; };       // Between 0 and 9
  int y() const { return position_.second; };      // Between 0 and 19
  int width() const { return width_; };            // Between 1 and 4
  int color() const { return color_; };            // Between 0 and 6
  int rotation() const { return rotationState_; }; // Between 0 and 3
  bool isLocked() const { return locked_; }; // True if the Tetromino is locked
  bool isAlive() const { return alive_; };   // True if the Tetromino is alive

  // Setter
  void setLocked(const bool locked) { locked_ = locked; };
  void setAlive(const bool alive) { alive_ = alive; };
};
