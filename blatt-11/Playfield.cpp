//
// Created by Paul Schaffrath on 04.07.24.
//

#include "Playfield.h"
#include "Tetromino.h"

Playfield::Playfield() {
  // Initialize the grid
  initGrid();
}

// _____________________________________________________________________________
Playfield::~Playfield() = default;

// _____________________________________________________________________________
void Playfield::initGrid() {
  field_.resize(HEIGHT, std::vector<Cell>(WIDTH, Cell(0, 0, 0, false)));
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      field_[y][x] =
          Cell(x, y, 0, false); // Initialize cells with default values
    }
  }
}

// _____________________________________________________________________________
void Playfield::updateField() {
  // Check if a line is full
  for (int y = 0; y < HEIGHT; ++y) {
    bool full = true;
    for (int x = 0; x < WIDTH; ++x) {
      if (!field_[y][x].isAlive()) {
        full = false;
        break;
      }
    }
    // If a line is full, delete it
    if (full) {
      for (int x = 0; x < WIDTH; ++x) {
        field_[y][x].setAlive(false);
      }
    }
  }
}

// _____________________________________________________________________________
bool Playfield::canMoveTo(const int x, const int y, const int id) const {
  // Check if ´the tetromino can move to the given position
  for (const auto &offset : Tetromino::tetrominoShapes[id]) {
    const int x_ = x + offset[0];
    const int y_ = y + offset[1];
    if (x_ < 0 || x_ >= WIDTH || y_ >= HEIGHT) {
      return false;
    }
    if (y_ >= 0 && field_[y_][x_].isAlive()) {
      return false;
    }
  }
  return true;
}

// _____________________________________________________________________________
int Playfield::getFieldColor(const int x, const int y) const {
  return field_[x][y].getColor();
}

// _____________________________________________________________________________
bool Playfield::isFieldAlive(const int x, const int y) const {
  return field_[x][y].isAlive();
}

// _____________________________________________________________________________
std::vector<std::vector<Cell>> Playfield::getField() const { return field_; }

// _____________________________________________________________________________
Cell Playfield::getCell(const int x, const int y) const { return field_[y][x]; }

// _____________________________________________________________________________
void Playfield::setCell(const Cell cell) { field_[cell.y()][cell.x()] = cell; }

// _____________________________________________________________________________
void Playfield::clearField() {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      field_[y][x].setAlive(false);
    }
  }
}

// _____________________________________________________________________________
bool Playfield::isFieldEmpty() const {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (field_[y][x].isAlive()) {
        return false;
      }
    }
  }
  return true;
}
