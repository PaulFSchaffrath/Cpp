// Copyright 2024, Paul Schaffrath

#include "./TerminalManager.h"

// ____________________________________________________________________________
bool UserInput::isKey_q() { return keycode_ == 113; }
bool UserInput::isKey_c() { return keycode_ == 99; }
bool UserInput::isKey_r() { return keycode_ == 114; }
bool UserInput::isKey_s() { return keycode_ == 115; }
bool UserInput::isKey_g() { return keycode_ == 103; }
bool UserInput::isKey_G() { return keycode_ == 71; }
bool UserInput::isSpace() { return keycode_ == 32; }
bool UserInput::isMouse() {
  if (getmouse(&event) == OK) {
    if (event.bstate & BUTTON1_PRESSED) {
      return true;
    }
  }
  return false;
}

int TerminalManager::numCols() { return numCols_; }

int TerminalManager::numRows() { return numRows_; }

// ____________________________________________________________________________
void TerminalManager::setup() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  numCols_ = COLS / 2;
  numRows_ = LINES;

  if (numCols_ * numRows_ > MAX_NUM_CELLS) {
    endwin();
  }
}

// ____________________________________________________________________________
void TerminalManager::cleanup() {
  // End ncurses
  endwin();
}

void TerminalManager::printCell(int row, int col, bool getCurrent) {
  attroff(A_REVERSE);
  if (getCurrent) {
    attron(A_REVERSE);
  }
  mvprintw(row, col * 2, "  ");
}

void TerminalManager::showInfo(int numSteps, int numLivingCells,
                               bool isRunning) {
  attroff(A_REVERSE);
  mvprintw(0, 0, "Step: %9d Cells alive: %4d Running: %d", numSteps,
           numLivingCells, isRunning);
}

// _____________________________________________________________________________
UserInput TerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keycode_ = getch();
  return userInput;
}
