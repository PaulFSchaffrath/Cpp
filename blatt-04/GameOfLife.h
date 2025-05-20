// Copyright 2024, Paul Schaffrath

#pragma once

#include <ncurses.h>

const int MAX_NUM_CELLS = 1000;  // Maximale Anzahl an Zellen.

extern bool current_state[MAX_NUM_CELLS];
extern bool next_state[MAX_NUM_CELLS];
extern bool* current_state_ptr;
extern bool* next_state_ptr;
extern int last_clicked_cell_x;
extern int last_clicked_cell_y;
extern int num_steps;
extern int num_alive_cells;
extern bool is_game_running;

extern int numRows;
extern int numCols;


// The state of all pixels on the screen + the dimensions of the screen.
const int MAX_NUM_PIXELS = 10'000;

extern bool pixels[MAX_NUM_PIXELS];

// Initialize Ncurses.
void initTerminal();

// Initialize the Game (set default values).
void initGame();

// Clean up Ncurses.
void endNcurses();

// Set pixel at given logical position.
void setPixel(int row, int col, bool value);

// Get the value of the pixel at the given logical position.
bool getPixel(int row, int col);

// Draw glider at given logical position.
void drawGlider(int row, int col);

// Draw all pixels.
void showState();

// Set all pixels to random values.
void setPixelsToRandomValues();

int numAliveNeighbors(int row, int col);

void updateState();

// Process mouse click. Return true if there was a mouse click.
bool processUserInput(int keycode);