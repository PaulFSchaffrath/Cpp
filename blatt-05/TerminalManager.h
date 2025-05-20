// Copyright 2024, Paul Schaffrath

#include <ncurses.h>

class UserInput {
public:
  int keycode_;
  MEVENT event;
  bool isKey_q();
  bool isKey_c();
  bool isKey_r();
  bool isKey_s();
  bool isKey_g();
  bool isKey_G();
  bool isSpace();
  bool isMouse();
};

class TerminalManager {
private:
  // the actual number of cells that are shown on screen
  int numCols_;
  int numRows_;

public:
  static const int MAX_NUM_CELLS = 1'000'000;

  int numCols();
  int numRows();

  // Setup the terminal for the use with ncurses
  void setup();

  // Cleanup when finished
  void cleanup();

  // Show cells
  void printCell(int row, int col, bool getCurrent);

  // Show information
  void showInfo(int numSteps, int numLivingCells, bool isRunning);

  // Get input from the user.
  UserInput getUserInput();
};