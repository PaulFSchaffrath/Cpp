//
// Created by Paul Schaffrath on 04.07.24.
//

#include "Tetris.h"

#include "Playfield.h"
#include "TerminalManager.h"
#include "Tetromino.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

// _____________________________________________________________________________
Tetris::Tetris(TerminalManager *terminalManager)
    : terminalManager_(terminalManager), playfield_(new Playfield()),
      currentTetromino_(new Tetromino(I)) {

  if (terminalManager_ == nullptr) {
    std::cerr << "TerminalManager is nullptr" << std::endl;
    return;
  }
  numRows_ = terminalManager_->numRows();
  numCols_ = terminalManager_->numCols();
}

// _____________________________________________________________________________
Tetris::~Tetris() {
  delete currentTetromino_;
  delete playfield_;
}

// _____________________________________________________________________________
void Tetris::play() const {
  if (terminalManager_ == nullptr) {
    return;
  }
  while (processUserInput(TerminalManager::getUserInput())) {
    if (isRunning_) {
      // if (currentTetromino_ == nullptr) {
      //   currentTetromino_ = new Tetromino(TetrominoType::I);
      // }
      // Making the tetromino fall down slowly but the game is still running
      updateState();
    }
    // Draw and wait.
    showState();
    usleep(20'000);
  }
}

// _____________________________________________________________________________
bool Tetris::processUserInput(const UserInput userInput) const {
  if (currentTetromino_ == nullptr) {
    return false;
  }

  if (userInput.isKeyLeft()) {
    moveLeft();
  } else if (userInput.isKeyRight()) {
    moveRight();
  } else if (userInput.isKeyDown()) {
    moveDown();
  } else if (userInput.isKeyUp()) {
    rotate();
  } else if (userInput.isSpace()) {
    drop();
  } else if (userInput.isEscape()) {
    std::cout << "Game exit" << std::endl;
    return false; // Exit the game
  }

  return true;
}

// _____________________________________________________________________________
void Tetris::updateState() const {
  if (currentTetromino_ == nullptr) {
    return;
  }
  // Overall gamespeed and reaction is 20ms.
  // The tetromino falls down every one second
  static int counter = 0;
  if (counter++ % 50 == 0 && !currentTetromino_->isLocked()) {
    moveDown();
  }

  if (currentTetromino_->isAlive()) {
    // Check if tetromino is locked
    if (!currentTetromino_->isLocked()) {
      // Check if the tetromino is on the ground
      if (currentTetromino_->y() == 19) {
        currentTetromino_->setLocked(true);
      }
    }
  } else {
    delete currentTetromino_;
  }
}

// _____________________________________________________________________________
// ____________________________________________________________________________
void Tetris::showState() const {
  // Only draw visible cells.
  for (int row = 0; row < numRows_; ++row) {
    for (int col = 0; col < numCols_; ++col) {
      int color;
      if (playfield_->isFieldAlive(row, col)) {
        color = playfield_->getFieldColor(row, col);
      } else {
        color = 0;
      }
      terminalManager_->drawPixel(row, col, color);
    }
  }
  TerminalManager::refresh();
}

// _____________________________________________________________________________
void Tetris::spawnNewTetromino() const { currentTetromino_->reset(I); }

// _____________________________________________________________________________
void Tetris::moveLeft() const {
  if (currentTetromino_) {
    currentTetromino_->moveLeft();
  }
}

// _____________________________________________________________________________
void Tetris::moveRight() const {
  if (currentTetromino_) {
    currentTetromino_->moveRight();
  }
}

// _____________________________________________________________________________
void Tetris::moveDown() const {
  if (currentTetromino_) {
    currentTetromino_->moveDown();
  }
}

// _____________________________________________________________________________
void Tetris::drop() const {
  if (currentTetromino_) {
    currentTetromino_->drop();
  }
}

// _____________________________________________________________________________
void Tetris::rotate() const {
  if (currentTetromino_) {
    currentTetromino_->rotate();
  }
}
