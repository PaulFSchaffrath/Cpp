// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>

#include "./TerminalManager.h"
#include <ncurses.h>

// NOTE: We need `ncurses` stuff only in the implementation of
// `TerminalManager`, nowhere else (not even in `TerminalManager.h`, let alone
// anywhere in the files implementing the game logic).

// ____________________________________________________________________________
int TerminalManager::White = COLOR_WHITE;
int TerminalManager::Red = COLOR_RED;
int TerminalManager::Green = COLOR_GREEN;

// ____________________________________________________________________________
bool UserInput::isEscape() { return keycode_ == 27; }
bool UserInput::isKeyLeft() { return keycode_ == KEY_LEFT; }
bool UserInput::isKeyRight() { return keycode_ == KEY_RIGHT; }
bool UserInput::isKeyUp() { return keycode_ == KEY_UP; }
bool UserInput::isKeyDown() { return keycode_ == KEY_DOWN; }
bool UserInput::isMouseclick() { return mouseRow_ != -1; }

// ____________________________________________________________________________
TerminalManager::TerminalManager() {
  // Initialize ncurses and some settings suitable for gaming.
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);

  // Initialize some colors.
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);

  // Set the logical dimensions of the screen.
  numRows_ = LINES;
  numCols_ = COLS / 2;
}

// ____________________________________________________________________________
TerminalManager::~TerminalManager() { endwin(); }

// ____________________________________________________________________________
void TerminalManager::refresh() { ::refresh(); }

// ____________________________________________________________________________
void TerminalManager::drawPixel(int row, int col, int color) {
  if (color == White) {
    attron(COLOR_PAIR(1));
  } else if (color == Red) {
    attron(COLOR_PAIR(2));
  } else if (color == Green) {
    attron(COLOR_PAIR(3));
  }
  attron(A_REVERSE);
  mvprintw(row, 2 * col, "  ");
}

// ____________________________________________________________________________
UserInput TerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keycode_ = getch();
  MEVENT event;
  if ((userInput.keycode_ == KEY_MOUSE) && (getmouse(&event) == OK)) {
    if (event.bstate & BUTTON1_PRESSED) {
      userInput.mouseRow_ = event.y;
      userInput.mouseCol_ = event.x / 2;
    }
  }
  return userInput;
}

// ____________________________________________________________________________
void TerminalManager::drawString(int row, int col, const char *str) {
  mvprintw(row, col, "%s", str);
}
