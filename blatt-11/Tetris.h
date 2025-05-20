//
// Created by Paul Schaffrath on 04.07.24.
//

#pragma once

#include "Playfield.h"
#include "TerminalManager.h"
#include "Tetromino.h"

class Tetris {
private:
  // The terminal manager
  TerminalManager *terminalManager_ = nullptr;
  // The playfield
  Playfield *playfield_;

  Tetromino *currentTetromino_; // The current Tetromino

  // Size of the grid; one half of the grid is the playfield, the other half are
  // the next Tetrominos
  int numCols_;
  int numRows_;

  // State of the game
  bool isRunning_ = false;

public:
  // Constructor
  explicit Tetris(TerminalManager *terminalManager);

  // Destructor
  ~Tetris();

  // Play the game
  void play() const;

  // Initialize the terminal
  void initTerminal();

  // Handle key and mouse presses. Change the new grid.
  bool processUserInput(UserInput userInput) const;

  // Move the current Tetromino to the left
  void moveLeft() const;

  // Move the current Tetromino to the right
  void moveRight() const;

  // Move the current Tetromino down
  void moveDown() const;

  // Rotate the current Tetromino
  void rotate() const;

  // Drop the current Tetromino
  void drop() const;

  // Calculate the next state and write it into new grid.
  void updateState() const;

  void spawnNewTetromino() const;

  // Draw the new grid using ncurses.
  void showState() const;

  // Returns true if the coordinates (x, y) are inside the grid
  bool isLegalPosition(int row, int col);
};
