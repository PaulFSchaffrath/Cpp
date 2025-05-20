// Copyright 2024, University of Freiburg
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#include "./Snake.h"
#include <ncurses.h>

// ____________________________________________________________________________
// Global variables. See the header for documentation.
//
int posX;
int posY;

int vx;
int vy;

int numPixelsX;
int numPixelsY;

// ____________________________________________________________________________
void initTerminal() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);

  start_color();
  // Initialize one color pair for each color.
  // For simplicity reasons we only use the foreground
  // colors.
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);

  // COLS and LINES are global variables from ncurses (dimensions of screen).
  numPixelsX = COLS / 2;
  numPixelsY = LINES;
}

// ____________________________________________________________________________
void initGame() {
  posX = numPixelsX / 2;
  posY = numPixelsY / 2;

  vx = 1;
  vy = 0;
}

// _____________________________________________________________________________
void drawPixel(int y, int x, int color) {
  int colorPairNum = 1;
  if (color == COLOR_RED) {
    colorPairNum = 2;
  } else if (color == COLOR_BLACK) {
    colorPairNum = 3;
  } else if (color == COLOR_BLUE) {
    colorPairNum = 4;
  }
  attron(COLOR_PAIR(colorPairNum));
  for (int j = 0; j < 2; j++) {
    mvprintw(y, x * 2 + j, " ");
  }
}

// ____________________________________________________________________________
void drawBorder(int color) {
  for (int x = 0; x < numPixelsX; x++) {
    drawPixel(0, x, color);
    drawPixel(numPixelsY - 1, x, color);
  }

  for (int y = 0; y < numPixelsY; y++) {
    drawPixel(y, 0, color);
    drawPixel(y, numPixelsX - 1, color);
  }
}

// ____________________________________________________________________________
void drawSnake(int color) { drawPixel(posY, posX, color); }

// ____________________________________________________________________________
bool collidesWithBorder() {
  int x = posX;
  int y = posY;
  return x <= 0 || x >= numPixelsX - 1 || y <= 0 || y >= numPixelsY - 1;
}

// ____________________________________________________________________________
void moveSnake() {
  posX = posX + vx;
  posY = posY + vy;
}

// ____________________________________________________________________________
bool handleKey(int key) {
  int oldVx = vx;
  int oldVy = vy;
  switch (key) {
  case 27: // ESC
    return false;
  case KEY_DOWN:
    vx = 0;
    vy = 1;
    break;
  case KEY_UP:
    vx = 0;
    vy = -1;
    break;
  case KEY_LEFT:
    vx = -1;
    vy = 0;
    break;
  case KEY_RIGHT:
    vx = 1;
    vy = 0;
    break;
  default:
    break;
  }
  // Ignore the change of direction if it is illegal
  if (oldVx + vx == 0 && oldVy + vy == 0) {
    vx = oldVx;
    vy = oldVy;
  }

  return true;
}
