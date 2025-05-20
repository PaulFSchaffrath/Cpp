// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#pragma once

// An abstract base class that defines an interface for drawing pixels
// on a screen.
class TerminalManager {
public:
  // Virtual destructor.
  virtual ~TerminalManager() = default;

  // Draw a "pixel" at the given position and with the given intensity between
  // The intensity has to be in [0.0, 1.0]
  virtual void drawPixel(int row, int col, bool inverse, float intensity) = 0;

  // Refresh the screen.
  virtual void refresh() = 0;

  // Get the dimensions of the screen.
  virtual int numRows() const = 0;
  virtual int numCols() const = 0;
};
