//
// Created by Paul Schaffrath on 28.07.24.
//

#pragma once

#include <NCursesTerminalManager.h>
#include <Playfield.h>
#include <Tetromino.h>

class Tetris {
  // ______ Keybinds ______
  int keyRotateCW_;
  int keyRotateCCW_;

  // ______ Terminal Manager ______
  TerminalManager &terminalManager_;

  // ______ Playfield ______
  Playfield playfield_;

  // ______ Current Tetromino ______
  std::unique_ptr<Tetromino> currentTetromino_;

  // ______ Next Tetromino ______
  std::unique_ptr<Tetromino> nextTetromino_;

  // ______ Game data ______
  int score_ = 0;            // Current score
  int level_ = 0;            // Current level
  int linesCleared_ = 0;     // Number of lines cleared in the current level
  static const int SPEEDS[]; // Velocity in frames per gridcell for the levels
  bool isRunning_ = true;    // Flag indicating whether the game is running
  bool gameOver_ = false;    // Flag indicating whether the game is over

  // ______ TEST ______
  FRIEND_TEST(TetrisTest, drawField);

public:
  // ______ Constants ______
  static constexpr int WIDTH = 10;
  static constexpr int HEIGHT = 22;
  static constexpr int DISTANCE_TO_TOP = 2;
  static constexpr int DISTANCE_TO_SIDE = 2;

  // ______ Constructor ______
  explicit Tetris(TerminalManager &terminalManager, int keyRotateCW,
                  int keyRotateCCW);

  // ______ Getters ______
  [[nodiscard]] int score() const { return score_; }
  [[nodiscard]] int level() const { return level_; }
  [[nodiscard]] int linesCleared() const { return linesCleared_; }
  [[nodiscard]] bool isRunning() const { return isRunning_; }
  [[nodiscard]] bool gameOver() const { return gameOver_; }

  // ______ Initialize and run the game ______
  void play();

  // ______ Update the game state ______
  void update();

  // ______ Method for generating a new tetromino ______
  static Tetromino::Shape generateNewTetrominoType(Tetromino::Shape shape);

  // ______ Method for processing user input ______
  bool processUserInput(int keycode);

  // ______ Draw the game ______
  void drawGame() const;
  void drawGameData() const; // Draw the score, level and linesCleared
  void drawField() const;    // Draw the playfield  and the current tetromino
  void drawNextTetromino() const; // Draw the next tetromino
  void drawBorder() const;        // Draw the border around the game
  void drawCountDown() const;     // Draw a countdown before the game starts

  // ______ Testing ______
  void createTestTetrominos();
  double getTimeBetweenUpdates(int level);
};
