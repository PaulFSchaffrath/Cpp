// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.
//
#include "./MockTerminalManager.h"
#include <ncurses.h>

#include <algorithm>
#include <cmath>
#include <stdexcept>

static constexpr size_t systemColors = 16;

// ____________________________________________________________________________
bool UserInput::isKeyUp() { return keycode_ == KEY_UP; }
bool UserInput::isKeyDown() { return keycode_ == KEY_DOWN; }
bool UserInput::isKeyLeft() { return keycode_ == KEY_LEFT; }
bool UserInput::isKeyRight() { return keycode_ == KEY_RIGHT; }

// _____________________________________________________________
size_t MockTerminalManager::convertIntensityToColor(float intensity) const {
  intensity = 1 - std::exp(-50.0 * intensity);
  int color = (COLORS - 1 - systemColors) * std::clamp(intensity, 0.0f, 1.0f) +
              systemColors;
  return color;
}

// ____________________________________________________________________________
MockTerminalManager::MockTerminalManager() {
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  start_color();

  if (COLORS < 200) {
    endwin();
    throw std::runtime_error{
            "The TerminalManager requires a terminal with"
            " at least 200 colors. Consider setting `TERM=xterm-256color` before"
            " starting the application"};
  }
  // Define as many shades of a certain color (red in this case) as there are
  // colors.
  for (int color = systemColors; color < COLORS; ++color) {
    int max = 800;
    int intensity = max * color / (COLORS - systemColors);
    init_color(color, intensity, 0, 0);
    // init_color(color, intensity, 0, 0);
    init_pair(color, color, 0);
  }
  init_pair(0, COLOR_GREEN, COLOR_BLUE);
  numRows_ = LINES;
  numCols_ = COLS / 2;
}

// ____________________________________________________________________________
MockTerminalManager::~MockTerminalManager() { endwin(); }

// ____________________________________________________________________________
void MockTerminalManager::drawPixel(int row, int col, bool inverse,
                                       float intensity) {
  int color = convertIntensityToColor(intensity);
  if (inverse)
    attron(A_REVERSE);
  attron(COLOR_PAIR(color));
  mvprintw(row, 2 * col, "  ");
  attroff(COLOR_PAIR(color));
  if (inverse)
    attroff(A_REVERSE);
}

// ____________________________________________________________________________
void MockTerminalManager::refresh() { ::refresh(); }

// ___________________________________________________________________________
void MockTerminalManager::drawString(int row, int col, const char *output,
                                        float intensity) {
  int color = convertIntensityToColor(intensity);
  attron(COLOR_PAIR(color));
  mvaddstr(row, 2 * col, output);
  attroff(COLOR_PAIR(color));
}

// ___________________________________________________________________________
UserInput MockTerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keycode_ = getch();
  userInput.isMouseclick_ = false;
  if (userInput.keycode_ == KEY_MOUSE) {
    MEVENT mouseEvent;
    if (getmouse(&mouseEvent) == OK) {
      if (mouseEvent.bstate & BUTTON1_PRESSED) {
        userInput.isMouseclick_ = true;
        userInput.mouseX_ = mouseEvent.x / 2;
        userInput.mouseY_ = mouseEvent.y;
      }
    }
  }
  return userInput;
}

// ___________________________________________________________________________
int MockTerminalManager::numColors() { return COLORS; }