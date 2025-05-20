// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.
//          Paul Schaffrath <ps609@students.uni-freiburg.de>.

#pragma once

// An abstract base class that defines an interface for drawing pixels and
// strings to the terminal.
class TerminalManager {
public:
  // Virtual destructor.
  virtual ~TerminalManager() = default;

  // Draw a "pixel" at the given position and with the given color.
  virtual void drawPixel(int col_x, int row_y, int color) const = 0;

  // Draw the given string at the given position and with the given color.
  virtual void drawString(int col_x, int row_y, int color,
                          const char *str) const = 0;

  // Refresh the screen.
  virtual void refresh() = 0;

  // Get the dimensions of the screen.
  [[nodiscard]] virtual int numRows() const = 0;
  [[nodiscard]] virtual int numCols() const = 0;
};
