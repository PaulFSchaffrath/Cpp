//
// Created by Paul Schaffrath on 04.07.24.
//

#include "Cell.h"

// ___________________________________________________________________________
Cell::Cell(const int x, const int y, const int color, const bool alive) {
  x_ = x;
  y_ = y;
  color_ = color;
  alive_ = alive;
}

// ___________________________________________________________________________
void Cell::setColor(const int color) { color_ = color; }

// ___________________________________________________________________________
void Cell::setAlive(const bool alive) { alive_ = alive; }