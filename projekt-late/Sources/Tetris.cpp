//
// Created by Paul Schaffrath on 28.07.24.
//

#include <ctime>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <unistd.h>

#include <NCursesTerminalManager.h>
#include <Tetris.h>
#include <chrono>
#include <thread>

//_______________________________________________________________________________________________________________________
const int Tetris::SPEEDS[] = {
    // Game speeds for different levels
    48, 43, 38, 33, 28, 23, 18, 13, 8, 6, // Level 0-9
    5,  5,  5,  4,  4,  4,  3,  3,  3, 2, // Level 10-19
    2,  2,  2,  2,  2,  2,  2,  2,  2, 1, // Level 20-29
    1                                     // Level 30+
};

//______________________________________________________________________________________________________________________
Tetris::Tetris(TerminalManager &terminalManager, const int keyRotateCW,
               const int keyRotateCCW)
    : keyRotateCW_(keyRotateCW), keyRotateCCW_(keyRotateCCW),
      terminalManager_(terminalManager), currentTetromino_(nullptr),
      nextTetromino_(nullptr) {
  srand48(time(nullptr)); // Seed the random number generator
}

//______________________________________________________________________________________________________________________
void Tetris::play() {
  int frameCounter = 0; // Frame counter for controlling game speed
  // ______ Create first and second Tetrominoes ______
  auto shape = static_cast<Tetromino::Shape>(time(nullptr) % 7);
  currentTetromino_ = std::make_unique<Tetromino>(shape);
  nextTetromino_ = std::make_unique<Tetromino>(
      generateNewTetrominoType(currentTetromino_->shape()));
  // ________________________________________________________________
  drawBorder();               // Draw the game border
  drawGame();                 // Draw the game and all its parts
  terminalManager_.refresh(); // Refresh the terminal to show the game
  drawCountDown();            // Draw the countdown
  // ______ MAIN GAME LOOP ______
  while (processUserInput(NCursesTerminalManager::getUserInput().keycode_) &&
         !gameOver_) {
    // Update game state at the current game speed
    if (const int framesPerGridcell = SPEEDS[level_ < 30 ? level_ : 29];
        frameCounter % framesPerGridcell == 0) {
      update();
    }
    drawGame(); // Draw the game and all its parts
    frameCounter++;
    usleep(
        14'550); // Wait for 14.7 milliseconds to achieve the desired game speed
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
  if (isRunning_) { // Check if game is running and not paused
    if (keycode == KEY_LEFT &&
        currentTetromino_->canMoveLeft(playfield_)) { // Move left if possible
      currentTetromino_->moveLeft();
    } else if (keycode == KEY_RIGHT &&
               currentTetromino_->canMoveRight(
                   playfield_)) { // Move right if possible
      currentTetromino_->moveRight();
    } else if (keycode == KEY_DOWN &&
               currentTetromino_->canMoveDown(
                   playfield_)) { // Move down if possible
      currentTetromino_->moveDown();
      score_++; // Increment score by 1 for pushing down
    } else if (keycode ==
               keyRotateCCW_) { // Rotate counter-clockwise if possible
      currentTetromino_->rotateCCW(playfield_);
    } else if (keycode == keyRotateCW_) { // Rotate clockwise if possible
      currentTetromino_->rotateCW(playfield_);
    } else if (keycode == ' ') { // Hard drop if possible
      score_ += currentTetromino_->hardDrop(playfield_);
    }
  }
  if (keycode == 'p') { // Pause the game if 'p' is pressed
    isRunning_ = !isRunning_;
  }
  if (keycode == 'q') { // Quit the game if 'q' is pressed
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
      playfield_.lockTetromino(currentTetromino_); // Lock the current Tetromino
      const int clearedRows =
          playfield_.fullRowsCleared(); // Clear potential lines
      linesCleared_ +=
          clearedRows; // Number of cleared rows is added to linesCleared
      // ______ SCORE ______
      // Increase score based on cleared lines and current level
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
      // ______ NEW TETROMINO ______
      // CurrentTetromino is set as the next one
      currentTetromino_ = std::move(nextTetromino_);
      // Generate new tetromino for nextTetromino
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
    // ______ LEVEL UP ______
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
  // Generate a new Tetromino with a random shape´
  auto newShape = static_cast<Tetromino::Shape>(lrand48() % 7);
  if (newShape ==
      shape) { // If the new shape is the same as the last one, generate again
    newShape = static_cast<Tetromino::Shape>(lrand48() % 7);
  }
  return newShape;
}

//______________________________________________________________________________________________________________________
void Tetris::drawGame() const {
  // Draw all parts of the game
  drawField();
  drawGameData();
  drawNextTetromino();
}

//______________________________________________________________________________________________________________________
void Tetris::drawField() const {
  int counter = 0; // Counter to make the playfield look more like a grid
  // Draw the playfield -> 0 means empty, > 0 means occupied and the nmber is
  // the color
  for (int x = 0; x < WIDTH; ++x) {
    for (int y = 2; y < HEIGHT;
         ++y) { // Draw the playfield without the top 2 rows
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

  // ______ Draw the current tetromino ______
  // Check if the current tetromino is available
  if (currentTetromino_ == nullptr) {
    return;
  }
  // Draw the current tetromino
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
  // Check if the next tetromino is available
  if (nextTetromino_ == nullptr) {
    return;
  }
  // Draw the "Next:" text
  terminalManager_.drawString(WIDTH + 2 + DISTANCE_TO_SIDE, 4, 9, "Next:");
  // Clear the next tetromino area
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      terminalManager_.drawPixel(WIDTH + 2 + DISTANCE_TO_SIDE + x, 5 + y, 0);
    }
  }
  // Draw the next tetromino
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
  // Draw the border on left-right-bottom
  for (int x = 1; x <= 10 + 2; ++x) {
    for (int y = 3; y <= 21 + 3; ++y) {
      if (x == 1 || x == 12 || y == 24) {
        terminalManager_.drawPixel(x, y, 10);
      }
    }
  }
}

//______________________________________________________________________________________________________________________
void Tetris::drawCountDown() const {
  // Draw the countdown text and wait 1 second
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

//______________________________________________________________________________________________________________________
void Tetris::createTestTetrominos() {
  currentTetromino_ = std::make_unique<Tetromino>(Tetromino::Shape::I);
  nextTetromino_ = std::make_unique<Tetromino>(Tetromino::Shape::O);
}

double Tetris::getTimeBetweenUpdates(const int level) {
  double totalElapsed = 0;
  int updateCount = 0;
  createTestTetrominos(); // Create Test-Tetrominos

  // Get the level-speed
  const int framesPerGridcell = SPEEDS[level];

  // Variables for time measurement
  auto lastUpdate = std::chrono::high_resolution_clock::now();

  // Start test game lop
  for (int i = 0; i < 1000; i++) {
    // Check for update (tetromino moves down)
    if (i % framesPerGridcell == 0) {
      auto now = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> elapsed = now - lastUpdate;
      totalElapsed += elapsed.count();
      lastUpdate = now;
      update();
      updateCount++;
    }
    // Time between frames
    std::this_thread::sleep_for(std::chrono::microseconds(
        14'550)); // 16.667 Mikroseconds = 1/60 seconds

    // Eigentlich entspricht 16.667 dem richtigen Wert, jedoch habe ich durch
    // die Tests erfahren, dass dadurch das Tetromino langsamer fällt als es
    // sollte, deswegen habe ich diesen Wert so weit angepasst, dass das Tempo
    // nun stimmt. (ca .14.700) Zumindst läuft es jetzt so auf meinem Computer
    // richtig.
  }

  // Calculate the average time between update() calls.
  const double averageElapsed = totalElapsed / updateCount;
  return averageElapsed;
}
