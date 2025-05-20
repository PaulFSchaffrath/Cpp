//
// Created by Paul Schaffrath on 03.07.24.
//

#pragma once

#include <vector>

class TetrominoShape {
public:
  static std::vector<std::vector<std::vector<int>>> shapes;

  static void initializeShapes() {
    shapes = {// I Shape
              {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
              // O Shape
              {{1, 1}, {1, 1}},
              // T Shape
              {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}},
              // S Shape
              {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}},
              // Z Shape
              {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}},
              // J Shape
              {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}},
              // L Shape
              {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}};
  }
};

// Initialize static member
std::vector<std::vector<std::vector<int>>> TetrominoShape::shapes;