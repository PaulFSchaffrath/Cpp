//
// Created by Paul Schaffrath on 30.07.24.
//

#include <gtest/gtest.h>
#include <ncurses.h>
#include <type_traits>

#include "./MockTerminalManager.h"
#include <Playfield.h>
#include <Tetris.h>
#include <Tetromino.h>

// ______ Tetris Tests ______

// Finished
TEST(TetrisTest, drawField) {
  MockTerminalManager mockTerminalManager(11, 30, 30);
  Tetris tetris(mockTerminalManager, 'x', 'y');

  tetris.createTestTetrominos(); // Create current and next tetromino
  tetris.drawField();            // Expect drawPixel calls for the playfield

  // Check if the playfield is drawn correctly
  for (int x = 5; x < 9; x++) {
    ASSERT_TRUE(mockTerminalManager.isPixelDrawn(x, 4));
  }
  // Rotate the current tetromino and check if the playfield is drawn correctly
  tetris.currentTetromino_->rotateCW(tetris.playfield_);

  tetris.drawField(); // Expect drawPixel calls for the rotated playfield
  ASSERT_TRUE(mockTerminalManager.isPixelDrawn(7, 4));
  ASSERT_TRUE(mockTerminalManager.isPixelDrawn(7, 5));
}

// Finished
TEST(TetrisTest, update) {
  // Testing the game Speed
  MockTerminalManager mockTerminalManager(11, 30, 30);
  Tetris tetris(mockTerminalManager, 'x', 'y');
  ASSERT_NEAR(tetris.getTimeBetweenUpdates(0), 0.8, 0.015);
  ASSERT_NEAR(tetris.getTimeBetweenUpdates(1), 0.72, 0.015);
  ASSERT_NEAR(tetris.getTimeBetweenUpdates(2), 0.64, 0.015);
  ASSERT_NEAR(tetris.getTimeBetweenUpdates(3), 0.55, 0.015);
  ASSERT_NEAR(tetris.getTimeBetweenUpdates(4), 0.47, 0.015);
  ASSERT_NEAR(tetris.getTimeBetweenUpdates(5), 0.39, 0.015);
  ASSERT_NEAR(tetris.getTimeBetweenUpdates(6), 0.30, 0.015);
  ASSERT_NEAR(tetris.getTimeBetweenUpdates(7), 0.22, 0.015);
  ASSERT_NEAR(tetris.getTimeBetweenUpdates(8), 0.13, 0.015);
}

// Not-Finished
TEST(TetrisTest, ProcessUserInputTest) {
  MockTerminalManager mockTerminalManager(11, 30, 30);
  /*Tetris tetris(mockTerminalManager, 'x', 'y');

  UserInput input;
  input.keycode_ = KEY_LEFT;
  MockTerminalManager::addUserInput(input);

  tetris.play();
  ASSERT_EQ(MockTerminalManager::drawPixelCalls.size(), 2u);
  // Weitere Assertions hier... */
}

// Finished
TEST(TetrisTest, generateNewTetrominoType) {
  // Test the generation of a new tetromino type
  // Test if the generation is a valid tetromino type
  constexpr bool test =
      std::is_same_v<decltype(Tetris::generateNewTetrominoType(
                         Tetromino::Shape::I)),
                     Tetromino::Shape>;
  ASSERT_TRUE(test);
}

// ______ Playfield Tests ______

// Finished
TEST(PlayfieldTest, isRowFull) {
  auto playfield = Playfield();
  for (int i = 0; i < 22; i++) {
    ASSERT_FALSE(playfield.isRowFull(i));
  }
  for (auto &i : playfield.playfield_) {
    i[21] = 1;
  }
  ASSERT_TRUE(playfield.isRowFull(21));

  for (auto &i : playfield.playfield_) {
    i[0] = 1;
  }
  ASSERT_TRUE(playfield.isRowFull(0));
}

// Finished
TEST(PlayfieldTest, clearRow) {
  auto playfield = Playfield();
  for (auto &i : playfield.playfield_) {
    i[5] = 1;
  }
  ASSERT_TRUE(playfield.isRowFull(5));
  playfield.clearRow(5);
  ASSERT_FALSE(playfield.isRowFull(5));
  for (auto &i : playfield.playfield_) {
    for (int &j : i) {
      j = 1;
    }
  }
  for (int i = 0; i < 22; i++) {
    ASSERT_TRUE(playfield.isRowFull(i));
  }
  for (int i = 0; i < 22; i++) {
    playfield.clearRow(i);
  }
  for (int i = 0; i < 22; i++) {
    ASSERT_FALSE(playfield.isRowFull(i));
  }
}

// Finished
TEST(PlayfieldTest, getPlayfield) {
  auto playfield = Playfield();
  ASSERT_EQ(playfield.getPlayfield(0, 0), 0);
  playfield.playfield_[5][5] = 1;
  ASSERT_EQ(playfield.getPlayfield(5, 5), 1);
  ASSERT_THROW(playfield.getPlayfield(12, 5), std::out_of_range);
}

// Finished
TEST(PlayfieldTest, fullRowsCleared) {
  auto playfield = Playfield();
  for (auto &i : playfield.playfield_) {
    for (int &j : i) {
      j = 1;
    }
  }
  for (int i = 0; i < 22; i++) {
    ASSERT_TRUE(playfield.isRowFull(i));
  }
  ASSERT_EQ(playfield.fullRowsCleared(), 22);
  for (int i = 0; i < 22; i++) {
    ASSERT_FALSE(playfield.isRowFull(i));
  }
}

// Finished
TEST(PlayfieldTest, lockTetromino) {
  auto playfield = Playfield();
  const auto tetromino = std::make_unique<Tetromino>(Tetromino::Shape::I);
  playfield.lockTetromino(tetromino);
  for (int y = 0; y < static_cast<int>(tetromino->blocks().size()); y++) {
    for (int x = 0; x < static_cast<int>(tetromino->blocks().size()); x++) {
      if (tetromino->blocks()[y][x]) {
        ASSERT_EQ(
            playfield.getPlayfield(tetromino->x() + x, tetromino->y() + y),
            tetromino->color());
      }
    }
  }
}

// Finished
TEST(PlayfieldTest, clearField) {
  auto playfield = Playfield();
  for (auto &i : playfield.playfield_) {
    for (int &j : i) {
      j = 1;
    }
  }
  playfield.clearField();
  for (auto &i : playfield.playfield_) {
    for (int &j : i) {
      ASSERT_EQ(j, 0);
    }
  }
}

// Finished
TEST(PlayfieldTest, isValidPosition) {
  auto playfield = Playfield();
  auto tetromino = Tetromino(Tetromino::I);
  ASSERT_TRUE(
      playfield.isValidPosition(tetromino.blocks(), tetromino.x() + 1, 0));
  ASSERT_TRUE(
      playfield.isValidPosition(tetromino.blocks(), tetromino.x() - 1, 0));
  ASSERT_TRUE(playfield.isValidPosition(tetromino.blocks(), tetromino.x(),
                                        tetromino.y() + 1));
  ASSERT_FALSE(
      playfield.isValidPosition(tetromino.blocks(), tetromino.x() + 1, 22));
  tetromino.x_ = 0;
  for (int i = 0; i < 20; i++) {
    playfield.playfield_[5][i] = 1;
  }
  ASSERT_TRUE(playfield.isValidPosition(tetromino.blocks(), 1, 5));
  ASSERT_FALSE(playfield.isValidPosition(tetromino.blocks(), 2, 5));
  ASSERT_TRUE(playfield.isValidPosition(tetromino.blocks(), 6, 5));
}

// ______ Tetromino Tests ______

// Finished
TEST(TetrominoTest, constructor) {
  // ______ Tetromino (I) ______
  const auto tetromino = Tetromino(Tetromino::I);
  ASSERT_EQ(tetromino.shape(), Tetromino::I);
  ASSERT_EQ(tetromino.y(), 0);
  ASSERT_EQ(tetromino.x(), 3);
  ASSERT_EQ(tetromino.color(), 2);

  // ______ Tetromino (O) ______
  const auto tetromino2 = Tetromino(Tetromino::O);
  ASSERT_EQ(tetromino2.shape(), Tetromino::O);
  ASSERT_EQ(tetromino2.y(), 2);
  ASSERT_EQ(tetromino2.x(), 4);
  ASSERT_EQ(tetromino2.color(), 8);

  // ______ Tetromino (T) ______
  const auto tetromino3 = Tetromino(Tetromino::T);
  ASSERT_EQ(tetromino3.shape(), Tetromino::T);
  ASSERT_EQ(tetromino3.y(), 1);
  ASSERT_EQ(tetromino3.x(), 3);
  ASSERT_EQ(tetromino3.color(), 7);
}

// Finished
TEST(TetrominoTest, moveLeft) {
  const auto playfield = Playfield();

  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);

  // Move tetromino left until it can't move anymore
  while (tetromino.canMoveLeft(playfield)) {
    tetromino.moveLeft();
  }
  ASSERT_EQ(tetromino.x(), 0);

  // ______ Tetromino (O) ______
  Tetromino tetromino2(Tetromino::O);

  // Move tetromino left until it can't move anymore
  while (tetromino2.canMoveLeft(playfield)) {
    tetromino2.moveLeft();
  }
  ASSERT_EQ(tetromino2.x(), 0);
}

// Finished
TEST(TetrominoTest, moveRight) {
  const auto playfield = Playfield();

  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);
  ASSERT_EQ(tetromino.x(), 3);

  // Move tetromino right until it can't move anymore
  while (tetromino.canMoveRight(playfield)) {
    tetromino.moveRight();
  }
  ASSERT_EQ(tetromino.x(), 10 - 4);

  // ______ Tetromino (O) ______
  Tetromino tetromino2(Tetromino::O);
  ASSERT_EQ(tetromino2.x(), 4);

  // Move tetromino right until it can't move anymore
  while (tetromino2.canMoveRight(playfield)) {
    tetromino2.moveRight();
  }
  ASSERT_EQ(tetromino2.x(), 10 - 2);
}

// Finished
TEST(TetrominoTest, moveDown) {
  const auto playfield = Playfield();

  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);

  // Move tetromino down until it can't move anymore
  while (tetromino.canMoveDown(playfield)) {
    tetromino.moveDown();
  }
  ASSERT_EQ(tetromino.y(), 19);

  // ______ Tetromino (O) ______
  Tetromino tetromino2(Tetromino::O);

  // Move tetromino down until it can't move anymore
  while (tetromino2.canMoveDown(playfield)) {
    tetromino2.moveDown();
  }
  ASSERT_EQ(tetromino2.y(), 20);
}

// Finished
TEST(TetrominoTest, hardDrop) {
  auto playfield = Playfield();
  Tetromino tetromino(Tetromino::I);
  ASSERT_EQ(tetromino.hardDrop(playfield), 19);
  ASSERT_EQ(tetromino.y(), 19);

  Tetromino tetromino2(Tetromino::I);
  tetromino2.rotateCW(playfield);
  ASSERT_EQ(tetromino2.hardDrop(playfield), 18);
  ASSERT_EQ(tetromino2.y(), 18);

  Tetromino tetromino3(Tetromino::O);
  ASSERT_EQ(tetromino3.hardDrop(playfield), 18);
  ASSERT_EQ(tetromino3.y(), 20);
}

// Finished
TEST(TetrominoTest, rotateCW) {
  const auto playfield = Playfield();
  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);

  tetromino.rotateCW(playfield);
  std::vector<std::vector<bool>> expectedBlocks = {{false, false, true, false},
                                                   {false, false, true, false},
                                                   {false, false, true, false},
                                                   {false, false, true, false}};
  const bool test = (tetromino.blocks() == expectedBlocks);
  ASSERT_TRUE(test);
  tetromino.rotateCW(playfield);
  tetromino.rotateCW(playfield);
  expectedBlocks = {{false, false, true, false},
                    {false, false, true, false},
                    {false, false, true, false},
                    {false, false, true, false}};
  const bool test2 = (tetromino.blocks() == expectedBlocks);
  ASSERT_TRUE(test2);

  // ______ Tetromino (L) ______
  Tetromino tetromino2(Tetromino::L);

  tetromino2.rotateCW(playfield);
  // clang-format off
  const std::vector<std::vector<bool>> expectedBlocks2 = {
      {true, true, false},
      {false, true, false},
      {false, true, false}};
  const bool test3 = (tetromino2.blocks() == expectedBlocks2);
  ASSERT_TRUE(test3);

  // ______ Tetromino (J) ______
  Tetromino tetromino3(Tetromino::J);

  tetromino3.rotateCW(playfield);
  const std::vector<std::vector<bool>> expectedBlocks3 = {
      {false, true, false},
      {false, true, false},
      {true, true, false}};
  // clang-format on
  const bool test4 = (tetromino3.blocks() == expectedBlocks3);
  ASSERT_TRUE(test4);
}

// Finished
TEST(TetrominoTest, rotateCCW) {
  const auto playfield = Playfield();
  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);
  // print the blocks before rotation
  tetromino.rotateCCW(playfield);
  std::vector<std::vector<bool>> expectedBlocks = {{false, false, true, false},
                                                   {false, false, true, false},
                                                   {false, false, true, false},
                                                   {false, false, true, false}};
  const bool test = (tetromino.blocks() == expectedBlocks);
  ASSERT_TRUE(test);

  tetromino.rotateCCW(playfield);
  tetromino.rotateCCW(playfield);
  expectedBlocks = {{false, false, true, false},
                    {false, false, true, false},
                    {false, false, true, false},
                    {false, false, true, false}};
  const bool test2 = (tetromino.blocks() == expectedBlocks);
  ASSERT_TRUE(test2);

  // ______ Tetromino (L) ______
  Tetromino tetromino2(Tetromino::L);
  tetromino2.rotateCCW(playfield);
  // clang-format off
  const std::vector<std::vector<bool>> expectedBlocks2 = {
      {false, true, false},
      {false, true, false},
      {false, true, true}};
  const bool test3 = (tetromino2.blocks() == expectedBlocks2);
  ASSERT_TRUE(test3);

  // ______ Tetromino (J) ______
  Tetromino tetromino3(Tetromino::J);
  tetromino3.rotateCCW(playfield);
  const std::vector<std::vector<bool>> expectedBlocks3 = {
      {false, true, true},
      {false, true, false},
      {false, true, false}};
  // clang-format on
  const bool test4 = (tetromino3.blocks() == expectedBlocks3);
  ASSERT_TRUE(test4);
}

// Finished
TEST(TetrominoTest, canMoveLeft) {
  const auto playfield = Playfield();

  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);
  ASSERT_TRUE(tetromino.canMoveLeft(playfield));
  tetromino.x_ = 0;
  ASSERT_FALSE(tetromino.canMoveLeft(playfield));

  // ______ Different Rotation ______
  tetromino.rotateCW(playfield);

  // ______ Tetromino (O) ______
  Tetromino tetromino2(Tetromino::O);
  ASSERT_TRUE(tetromino2.canMoveLeft(playfield));
  tetromino2.x_ = 0;
  ASSERT_FALSE(tetromino2.canMoveLeft(playfield));
  ASSERT_TRUE(tetromino.canMoveLeft(playfield));
  while (tetromino.canMoveLeft(playfield)) {
    tetromino.moveLeft();
  }
  ASSERT_EQ(tetromino.x(), -2);
}

// Finished
TEST(TetrominoTest, canMoveLeft2) {
  // Test canMoveLeft if blocks are in the way
  auto playfield = Playfield();
  for (int i = 0; i < 10; ++i) {
    playfield.playfield_[2][i] = 1;
  }

  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);
  tetromino.x_ = 6;
  while (tetromino.canMoveLeft(playfield)) {
    tetromino.moveLeft();
  }
  ASSERT_EQ(tetromino.x(), 3);

  // ______ Different Rotation ______
  Tetromino tetromino2(Tetromino::I);
  tetromino2.x_ = 6;
  tetromino2.rotateCW(playfield);
  while (tetromino2.canMoveLeft(playfield)) {
    tetromino2.moveLeft();
  }
  ASSERT_EQ(tetromino2.x(), 1);
}

// Finished
TEST(TetrominoTest, canMoveRight) {
  const auto playfield = Playfield();
  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);
  ASSERT_TRUE(tetromino.canMoveRight(playfield));
  tetromino.x_ = 10 - 4;
  ASSERT_FALSE(tetromino.canMoveRight(playfield));

  // ______ Different Rotation ______
  tetromino.rotateCW(playfield);
  ASSERT_TRUE(tetromino.canMoveRight(playfield));
  while (tetromino.canMoveRight(playfield)) {
    tetromino.moveRight();
  }
  ASSERT_EQ(tetromino.x(), 10 - 3);
}

// Finished
TEST(TetrominoTest, canMoveRight2) {
  // Test canMoveRight if blocks are in the way
  auto playfield = Playfield();
  for (int i = 0; i < 10; ++i) {
    playfield.playfield_[8][i] = 1;
  }

  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);
  tetromino.x_ = 1;
  while (tetromino.canMoveRight(playfield)) {
    tetromino.moveRight();
  }
  ASSERT_EQ(tetromino.x(), 4);

  // ______ Different Rotation ______
  Tetromino tetromino2(Tetromino::I);
  tetromino2.x_ = 1;
  tetromino2.rotateCW(playfield);
  while (tetromino2.canMoveRight(playfield)) {
    tetromino2.moveRight();
  }
  ASSERT_EQ(tetromino2.x(), 8 - 3);
}

// Finished
TEST(TetrominoTest, canMoveDown) {
  const auto playfield = Playfield();
  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);
  ASSERT_TRUE(tetromino.canMoveDown(playfield));
  while (tetromino.canMoveDown(playfield)) {
    tetromino.moveDown();
  }
  ASSERT_EQ(tetromino.y(), 19);

  // ______ Different Rotation ______
  Tetromino tetromino2(Tetromino::I);
  tetromino2.rotateCW(playfield);
  ASSERT_TRUE(tetromino2.canMoveDown(playfield));
  while (tetromino2.canMoveDown(playfield)) {
    tetromino2.moveDown();
  }
  ASSERT_EQ(tetromino2.y(), 22 - 4);

  // ______ Tetromino (L) ______
  Tetromino tetromino3(Tetromino::L);
  ASSERT_TRUE(tetromino3.canMoveDown(playfield));
  while (tetromino3.canMoveDown(playfield)) {
    tetromino3.moveDown();
  }
  ASSERT_EQ(tetromino3.y(), 22 - 3);

  Tetromino tetromino4(Tetromino::L);
  tetromino4.rotateCW(playfield);
  tetromino4.rotateCW(playfield);
  ASSERT_TRUE(tetromino4.canMoveDown(playfield));
  while (tetromino4.canMoveDown(playfield)) {
    tetromino4.moveDown();
  }
  ASSERT_EQ(tetromino4.y(), 22 - 2);
}

// Finished
TEST(TetrominoTest, canMoveDown2) {
  // Test canMoveDown if blocks are in the way
  auto playfield = Playfield();
  for (auto &i : playfield.playfield_) {
    i[20] = 1;
  }

  // ______ Tetromino (I) ______
  Tetromino tetromino(Tetromino::I);
  while (tetromino.canMoveDown(playfield)) {
    tetromino.moveDown();
  }
  ASSERT_EQ(tetromino.y(), 20 - 3);

  // ______ Different Rotation ______
  Tetromino tetromino2(Tetromino::I);
  tetromino2.rotateCW(playfield);
  while (tetromino2.canMoveDown(playfield)) {
    tetromino2.moveDown();
  }
  ASSERT_EQ(tetromino2.y(), 20 - 4);
}