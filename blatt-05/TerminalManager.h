// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>

#pragma once

// Class to represent user input (key or mouse events).
class UserInput {
public:
  // Functions that check for particular keys.
  bool isEscape();
  bool isKeyLeft();
  bool isKeyRight();
  bool isKeyUp();
  bool isKeyDown();
  bool isMouseclick();
  // The code of the key that was pressed.
  int keycode_;
  int mouseRow_ = -1;
  int mouseCol_ = -1;
};

// A class to draw pixels on or read input from the terminal, using ncurses.
class TerminalManager {
public:
  // Available colors.
  static int White;
  static int Red;
  static int Green;

  // Constructor: Set up the terminal for use with ncurses commands.
  TerminalManager();

  // Destructor: Clean up the terminal after use.
  ~TerminalManager();

  // Draw a pixel at the given logical position in the given color.
  void drawPixel(int row, int col, int color);

  // Draw a string at the given logical position
  void drawString(int row, int col, const char *str);

  // Show the contents of the screen.
  void refresh();

  // Return the logical dimensions of the screen.
  int numRows() { return numRows_; }
  int numCols() { return numCols_; }

  // Get user input.
  UserInput getUserInput();

private:
  // The logical dimensions of the screen.
  int numRows_;
  int numCols_;
};
