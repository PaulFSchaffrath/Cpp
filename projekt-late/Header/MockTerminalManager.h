// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//         Paul Schaffrath <ps609tudents.uni-freiburg.de>

#pragma once

#include <NCursesTerminalManager.h>

#include "./TerminalManager.h"
#include <string> // for std::string
#include <vector>

// An implementation of a terminal Manager that "draws" the pixels
// to a 2d-Array for testing/mocking purposes
class MockTerminalManager final : public TerminalManager {
  // This map stores the pixels which have been drawn using the drawPixel
  // method
  mutable int drawnPixels_[25][30] = {{}};
  // This

  // This map stores the strings which have been drawn using the drawString
  // method
  mutable std::pair<std::string, int> drawnStrings_[25][30] = {{}};

  int nmColors_;
  int numRows_;
  int numCols_;

public:
  // Construct with the given inumber of rows and cols.
  MockTerminalManager(const int numColors, const int numRows, const int numCols)
      : nmColors_(numColors), numRows_(numRows), numCols_(numCols) {}

  ~MockTerminalManager() override = default;

  // Draw a "pixel" at the given position and with the given color
  void drawPixel(int col_x, int row_y, int color) const override;

  // Draw a string at the given logical position and color.
  void drawString(int col_x, int row_y, int color,
                  const char *str) const override;

  // Nothing to do for "refresh"
  void refresh() override {};

  // Get the dimensions of the screen.
  int numRows() const override { return numRows_; }
  int numCols() const override { return numCols_; }

  // Returns true if there previously was a call to
  // drawPixel(col_x, row_y).
  bool isPixelDrawn(int col_x, int row_y) const;

  // Returns the color of the pixel at the given position.
  int getPixelColor(int col_x, int row_y) const;

  // Returns true if there previously was a call to
  // drawString(col_x, row_y).
  bool isStringDrawn(int col_x, int row_y) const;

  // Returns the string at the given position.
  const char *getString(int col_x, int row_y) const;

  // Returns Color for the given string at the given position.
  int getStringColor(int col_x, int row_y) const;
};