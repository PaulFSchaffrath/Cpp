// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#pragma once

#include "./Cell.h"
#include "./TerminalManager.h"
#include <unordered_map>

// A simple struct that stores the "inversity" and the intensity
// of a drawn Pixel.
class Pixel {
public:
  bool inverse_ = false;
  float intensity_ = 0.f;

  Pixel(bool inverse, float intensity)
      : inverse_{inverse}, intensity_{intensity} {}
  Pixel() = default;
};

// An implementation of a terminal Manager that "draws" the pixels
// to a 2d-Array for testing/mocking purposes
class MockTerminalManager : public TerminalManager {
private:
  // This map stores the pixels which have been drawn using the drawPixel
  // method
  std::unordered_map<Cell, Pixel> drawnPixels_;
  int numRows_;
  int numCols_;

public:
  // Construct with the given inumber of rows and cols.
  MockTerminalManager(int numRows, int numCols)
      : numRows_{numRows}, numCols_{numCols} {};

  ~MockTerminalManager() = default;

  // Draw a "pixel" at the given position and with the given intensity between
  // The intensity has to be in [0.0, 1.0]
  void drawPixel(int row, int col, bool inverse, float intensity) override;

  // Nothing to do for "refresh"
  void refresh() override{};

  // Get the dimensions of the screen.
  int numRows() const override { return numRows_; }
  int numCols() const override { return numCols_; }

  // Returns true iff there previously was a call to
  // drawPixel(row, col).
  bool isPixelDrawn(int row, int col) const;

  // Returns the "inverse" argument of the last call to
  // drawPixel(row, col);
  // Throws an exception if there was no such call.
  bool isPixelInverse(int row, int col) const;

  // Returns the "intensity" argument of the last call to
  // drawPixel(row, col);
  // Throws an exception if there was no such call.
  float getIntensity(int row, int col) const;
};
