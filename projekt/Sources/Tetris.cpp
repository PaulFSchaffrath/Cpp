//
// Created by Paul Schaffrath on 28.07.24.
//

#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include <NCursesTerminalManager.h>
#include <Tetris.h>

//_______________________________________________________________________________________________________________________
const int Tetris::SPEEDS[] = {
    48, 43, 38, 33, 28, 23, 18, 13, 8, 6, // Level 0-9
    5,  5,  5,  4,  4,  4,  3,  3,  3, 2, // Level 10-19
    2,  2,  2,  2,  2,  2,  2,  2,  2, 1, // Level 20-29
    1                                     // Level 30+
};

//______________________________________________________________________________________________________________________
Tetris::Tetris(NCursesTerminalManager &terminalManager, const int keyRotateCW,
               const int keyRotateCCW)
    : keyRotateCW_(keyRotateCW), keyRotateCCW_(keyRotateCCW),
      terminalManager_(terminalManager), currentTetromino_(nullptr),
      nextTetromino_(nullptr) {
  srand48(time(nullptr));
}

//______________________________________________________________________________________________________________________
void Tetris::play() {
  int frameCounter = 0;
  // Create first and second Tetrominoes
  auto shape = static_cast<Tetromino::Shape>(time(nullptr) % 7);
  currentTetromino_ = std::make_unique<Tetromino>(shape);
  nextTetromino_ = std::make_unique<Tetromino>(
      generateNewTetrominoType(currentTetromino_->shape()));
  drawBorder();
  drawGame();
  terminalManager_.refresh();
  drawCountDown();
  while (processUserInput(NCursesTerminalManager::getUserInput().keycode_) &&
         !gameOver_) {
    if (const int framesPerGridcell = SPEEDS[level_ < 30 ? level_ : 29];
        frameCounter % framesPerGridcell == 0) {
      update();
    }
    drawGame();
    frameCounter++;
    usleep(16'667);
  }
  // ______ Game Over ______
  playfield_.clearField(); // Clear the field
  drawField();
  terminalManager_.drawString(5, 8, 9, "Game Over!"); // Draw Game Over
  terminalManager_.refresh();
  usleep(3'500'000); // Wait for 3.5 seconds before exiting
}

//______________________________________________________________________________________________________________________
bool Tetris::processUserInput(const int keycode) {
  if (isRunning_) {
    if (keycode == KEY_LEFT && currentTetromino_->canMoveLeft(playfield_)) {
      currentTetromino_->moveLeft();
    } else if (keycode == KEY_RIGHT &&
               currentTetromino_->canMoveRight(playfield_)) {
      currentTetromino_->moveRight();
    } else if (keycode == KEY_DOWN &&
               currentTetromino_->canMoveDown(playfield_)) {
      currentTetromino_->moveDown();
      score_++; // increment score by 1 for pushing down
    } else if (keycode == keyRotateCCW_) {
      currentTetromino_->rotateCCW(playfield_);
    } else if (keycode == keyRotateCW_) {
      currentTetromino_->rotateCW(playfield_);
    } else if (keycode == ' ') {
      score_ += currentTetromino_->hardDrop(playfield_);
    }
  }
  if (keycode == 'p') {
    isRunning_ = !isRunning_;
  }
  if (keycode == 'q') {
    return false;
  }
  return true;
}

//______________________________________________________________________________________________________________________
void Tetris::update() {
  if (isRunning_) {
    // Test if Tetromino reached the bottom or the last playe to move down
    // the lock the Tetromino and check for lines to clear
    if (!currentTetromino_->canMoveDown(playfield_)) {
      playfield_.lockTetromino(currentTetromino_); // lock the current Tetromino
      const int clearedRows =
          playfield_.fullRowsCleared(); // Clear potential lines
      linesCleared_ += clearedRows;     // Clear potential lines
      // Increase score
      switch (clearedRows) {
      case 1:
        score_ += 40 * (level_ + 1);
        break;
      case 2:
        score_ += 100 * (level_ + 1);
        break;
      case 3:
        score_ += 300 * (level_ + 1);
        break;
      case 4:
        score_ += 1200 * (level_ + 1);
        break;
      default:
        break;
      }
      // nextTetromino is set as the next one
      currentTetromino_ = std::move(nextTetromino_);
      // generate new tetromino for nextTetromino
      nextTetromino_ = std::make_unique<Tetromino>(
          generateNewTetrominoType(currentTetromino_->shape()));

      // ______ GAME OVER ______
      // Test if new Tetromino is overlaping with blocks that are already placed
      for (int i = 0; i < static_cast<int>(currentTetromino_->blocks().size());
           ++i) {
        for (int j = 0;
             j < static_cast<int>(currentTetromino_->blocks().size()); ++j) {
          if (currentTetromino_->blocks()[i][j] &&
              playfield_.getPlayfield(currentTetromino_->x() + j,
                                      currentTetromino_->y() + i) != 0) {
            gameOver_ = true;
            return;
          }
        }
      }
    }
    // Add level if cleared 10 ore more lines
    if (linesCleared_ >= 10) {
      level_++;
      linesCleared_ %= 10;
    }

    // Move the current Tetromino down with the current game speed
    if (currentTetromino_->canMoveDown(playfield_)) {
      currentTetromino_->moveDown();
    }
  }
}

//______________________________________________________________________________________________________________________
Tetromino::Shape
Tetris::generateNewTetrominoType(const Tetromino::Shape shape) {
  auto newShape = static_cast<Tetromino::Shape>(lrand48() % 7);
  if (newShape == shape) {
    newShape = static_cast<Tetromino::Shape>(lrand48() % 7);
  }
  return newShape;
}

//______________________________________________________________________________________________________________________
void Tetris::drawGame() const {
  drawField();
  drawGameData();
  drawNextTetromino();
}

//______________________________________________________________________________________________________________________
void Tetris::drawField() const {
  int counter = 0;
  // Draw the playfield -> 0 means empty, > 0 means occupied and the nmber is
  // the color
  for (int x = 0; x < WIDTH; ++x) {
    for (int y = 2; y < HEIGHT; ++y) {
      if (counter % 2 == 0 && playfield_.getPlayfield(x, y) == 0) {
        terminalManager_.drawPixel(x + DISTANCE_TO_SIDE, y + DISTANCE_TO_TOP,
                                   0);
      } else if (playfield_.getPlayfield(x, y) == 0) {
        terminalManager_.drawPixel(x + DISTANCE_TO_SIDE, y + DISTANCE_TO_TOP,
                                   1);
      } else {
        terminalManager_.drawPixel(x + DISTANCE_TO_SIDE, y + DISTANCE_TO_TOP,
                                   playfield_.getPlayfield(x, y));
      }
      counter++;
    }
    counter++;
  }

  // Draw the current tetromino
  if (currentTetromino_ == nullptr) {
    return;
  }
  for (int y = 0; y < static_cast<int>(currentTetromino_->blocks().size());
       ++y) {
    for (int x = 0; x < static_cast<int>(currentTetromino_->blocks().size());
         ++x) {
      if (currentTetromino_->blocks()[y][x] &&
          currentTetromino_->y() + y >= 2) {
        terminalManager_.drawPixel(currentTetromino_->x() + x +
                                       DISTANCE_TO_SIDE,
                                   currentTetromino_->y() + y + DISTANCE_TO_TOP,
                                   currentTetromino_->color());
      }
    }
  }
}

//______________________________________________________________________________________________________________________
void Tetris::drawGameData() const {
  // Draw the score
  terminalManager_.drawString(WIDTH + 2 + DISTANCE_TO_SIDE, 10, 9,
                              ("Score: " + std::to_string(score_)).c_str());
  // Draw the level
  terminalManager_.drawString(WIDTH / 2, 1, 9,
                              ("Level: " + std::to_string(level_)).c_str());
  // Draw the lines cleared
  terminalManager_.drawString(
      WIDTH + 2 + DISTANCE_TO_SIDE, 12, 9,
      ("Lines cleared: " + std::to_string(linesCleared_)).c_str());
}

//______________________________________________________________________________________________________________________
void Tetris::drawNextTetromino() const {
  if (nextTetromino_ == nullptr) {
    return;
  }
  terminalManager_.drawString(WIDTH + 2 + DISTANCE_TO_SIDE, 4, 9, "Next:");
  // Clear the next tetromino area
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      terminalManager_.drawPixel(WIDTH + 2 + DISTANCE_TO_SIDE + x, 5 + y, 0);
    }
  }

  for (int y = 0; y < static_cast<int>(nextTetromino_->blocks().size()); ++y) {
    for (int x = 0; x < static_cast<int>(nextTetromino_->blocks().size());
         ++x) {
      if (nextTetromino_->blocks()[y][x]) {
        terminalManager_.drawPixel(WIDTH + 2 + DISTANCE_TO_SIDE + x, 5 + y,
                                   nextTetromino_->color());
      }
    }
  }
}

//______________________________________________________________________________________________________________________
void Tetris::drawBorder() const {
  // Draw the border
  for (int x = 1; x <= 10 + 2; ++x) {
    for (int y = 3; y <= 21 + 3; ++y) {
      if (x == 1 || x == 12 || y == 24) {
        terminalManager_.drawPixel(x, y, 10);
      }
    }
  }
}

void Tetris::drawCountDown() const {
  terminalManager_.drawString(WIDTH / 2 + 1, HEIGHT / 2 + 2, 9, "- 3 -");
  terminalManager_.refresh();
  usleep(1'000'000);
  terminalManager_.drawString(WIDTH / 2 + 1, HEIGHT / 2 + 2, 9, "- 2 -");
  terminalManager_.refresh();
  usleep(1'000'000);
  terminalManager_.drawString(WIDTH / 2 + 1, HEIGHT / 2 + 2, 9, "- 1 -");
  terminalManager_.refresh();
  usleep(1'000'000);
  terminalManager_.drawString(WIDTH / 2 + 1, HEIGHT / 2 + 2, 8, "START");
  terminalManager_.refresh();
  usleep(800'000);
}
