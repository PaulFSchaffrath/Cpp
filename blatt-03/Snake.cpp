// Copyright 2024, Paul Schaffrath

#include "./Snake.h"
#include <ncurses.h>

int xPos;
int yPos;
int rotation = 0;

int windowWidth = 60;
int windowHeight = 30;

// ___________________________________________________________________________
void initTerminal() {
  initscr();
  curs_set(false);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
}

// ___________________________________________________________________________
void initGame() {
  xPos = windowWidth / 2;
  yPos = windowHeight / 2;
  rotation = 0;
}

// ___________________________________________________________________________
void drawPixel(int row, int column, int color) {
  attron(COLOR_PAIR(color) | A_REVERSE);
  mvprintw(row, column, "  ");
  attroff(COLOR_PAIR(color) | A_REVERSE);
  refresh();
}

// ___________________________________________________________________________
void drawBorder(int color) {
  for (int x = 0; x <= windowWidth; x++) {
    drawPixel(0, x, color);
    drawPixel(windowHeight, x, color);
  }
  for (int y = 0; y <= windowHeight; y++) {
    drawPixel(y, 0, color);
    drawPixel(y, windowWidth, color);
  }
}

// ___________________________________________________________________________
void drawSnake(int color) { drawPixel(yPos, xPos, color); }

// ___________________________________________________________________________
bool collidesWithBorder() {
  if (0 > xPos - 1 || xPos >= windowWidth - 1 || 0 > yPos - 1 ||
      yPos > windowHeight - 1) {
    return true;
  }
  return false;
}

// ___________________________________________________________________________
void moveSnake() {
  switch (rotation) {
  case 0:
    xPos += 2;
    break;
  case 1:
    yPos++;
    break;
  case 2:
    xPos -= 2;
    break;
  case 3:
    yPos--;
    break;
  }
}

// ___________________________________________________________________________
bool handleKey(int key) {
  switch (key) {
  case KEY_RIGHT:
    if (rotation == 0 || rotation == 2) {
      break;
    } else {
      rotation = 0;
      return false;
    }
    break;
  case KEY_DOWN:
    if (rotation == 1 || rotation == 3) {
      break;
    } else {
      rotation = 1;
      return false;
    }
    break;
  case KEY_LEFT:
    if (rotation == 2 || rotation == 0) {
      break;
    } else {
      rotation = 2;
      return false;
    }
    break;
  case KEY_UP:
    if (rotation == 3 || rotation == 1) {
      break;
    } else {
      rotation = 3;
      return false;
    }
    break;
  case 27:
    return true;
  }
  return false;
}

// ___________________________________________________________________________
void endNcurses() { endwin(); }
