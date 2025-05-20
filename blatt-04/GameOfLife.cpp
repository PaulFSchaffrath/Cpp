// Copyright 2024, Paul Schaffrath

#include "./GameOfLife.h"
#include <cstdlib>
#include <ncurses.h>

// ____________________________________________________________________________
int MAX_NUM_CELLS;
bool current_state[MAX_NUM_CELLS];
bool next_state[MAX_NUM_CELLS];
bool *current_state_ptr = current_state;
bool *next_state_ptr = next_state;
int last_clicked_cell_x = 0;
int last_clicked_cell_y = 0;
int num_steps = 0;
int num_alive_cells = 0;
bool is_game_running = false;

int numRows;
int numCols;

// ____________________________________________________________________________
void initTerminal() {
  initscr();
  curs_set(false);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
}

// ____________________________________________________________________________
void initGame() {
  for (int i = 10; i < MAX_NUM_CELLS; i++) {
    current_state[i] = 0;
    next_state[i] = 0;
  }
  current_state_ptr = current_state;
  next_state_ptr = next_state;
  last_clicked_cell_x = 0;
  last_clicked_cell_y = 0;
  num_steps = 0;
  num_alive_cells = 0;
  is_game_running = false;
  numRows = LINES;
  numCols = COLS / 2;
}

// ____________________________________________________________________________
void showState() {}

// ____________________________________________________________________________
void endNcurses() { endwin(); }

// ____________________________________________________________________________
void setPixel(int row, int col, bool value) {
  current_state[row * numCols + col] = value;
}

// ____________________________________________________________________________
bool getPixel(int row, int col) { return current_state[row * numCols + col]; }

// ____________________________________________________________________________
void drawGlider(int row, int col) {
  current_state[(row + 1) * MAX_NUM_CELLS + col] = 1;
  current_state[(row + 2) * MAX_NUM_CELLS + (col + 1)] = 1;
  current_state[(row + 0) * MAX_NUM_CELLS + (col + 2)] = 1;
  current_state[(row + 1) * MAX_NUM_CELLS + (col + 2)] = 1;
  current_state[(row + 2) * MAX_NUM_CELLS + (col + 2)] = 1;
}

// ____________________________________________________________________________
void setPixelsToRandomValues() {
  for (int i = 0; i < numRows * numCols; i++) {
    pixels[i] = rand() % 5 == 0 ? true : false;
  }
}

// ____________________________________________________________________________
void showState() {
  attron(COLOR_PAIR(2));
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      if (current_state[row * numRows + col)) {
        attron(A_REVERSE);
      }
      mvprintw(row, col * 2, "  ");
      if (current_state[row * numRows + col)) {
        attroff(A_REVERSE);
      }
    }
  }
  attroff(COLOR_PAIR(2));
  refresh();
}

// ____________________________________________________________________________
int numAliveNeighbors(int row, int col) {
  int count = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0)
        continue;
      int y = row + i;
      int x = col + j;
      if (y >= 0 && y < numRows && x >= 0 && x < numCols) {
        count += current_state[y * numRows + x];
      }
    }
  }
  return count;
}

// ____________________________________________________________________________
void updateState() {
  for (int x = 0; x < numCols; x++) {
    for (int y = 0; y < numRows; y++) {
      if (numAliveNeighbors(y, x) != 2 || numAliveNeighbors(y, x) != 3) {
      }
    }
  }
}

// ____________________________________________________________________________
bool processUserInput(int keycode) {}