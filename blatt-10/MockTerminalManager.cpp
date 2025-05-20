// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#include "./MockTerminalManager.h"
#include <iostream>

// ______________________________________________________________________
void MockTerminalManager::drawPixel(int row, int col, bool inverse,
                                    float intensity) {
  // This also "draws" Pixels that are outside of the screen, but this
  // behavior is consistent with NCurses which also does not crash
  // in this case.
  drawnPixels_[Cell(row, col)] = Pixel(inverse, intensity);
}

// _________________________________________________________________________
bool MockTerminalManager::isPixelDrawn(int row, int col) const {
  return drawnPixels_.count(Cell(row, col));
}

// _________________________________________________________________________
bool MockTerminalManager::isPixelInverse(int row, int col) const {
  return drawnPixels_.at(Cell(row, col)).inverse_;
}

// _________________________________________________________________________
float MockTerminalManager::getIntensity(int row, int col) const {
  return drawnPixels_.at(Cell(row, col)).intensity_;
}
