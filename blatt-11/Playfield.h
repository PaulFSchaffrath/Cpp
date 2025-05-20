//
// Created by Paul Schaffrath on 04.07.24.
//

#pragma once
#include "Cell.h"

#include <vector>

class Playfield {
public:
  // Constructor and Destructor
  explicit Playfield();
  ~Playfield();

  // Return the color of the field
  int getFieldColor(int x, int y) const;

  // Return true if the field is filled with square, false if it is empty
  bool isFieldAlive(int x, int y) const;

  // Test if the tetromino can move to the given position
  bool canMoveTo(int x, int y, int id) const;

  // Update the field (e.g. delete full lines, etc.)
  void updateField();

  // Field size
  const int WIDTH = 10;
  const int HEIGHT = 20;

  // Get the field
  std::vector<std::vector<Cell>> getField() const;

  // Getter for the field
  Cell getCell(int x, int y) const;

  // Setter for the field
  void setCell(Cell cell);

  // Clear the field
  void clearField();

  // Check if the field is empty
  bool isFieldEmpty() const;

private:
  // The field is a 2D vector of cells
  std::vector<std::vector<Cell>> field_;

  // Initialize the grid
  void initGrid();
};
