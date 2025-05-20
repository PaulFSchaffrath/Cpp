//
// Created by Paul Schaffrath on 28.07.24.
//

#include <Tetromino.h>

//______________________________________________________________________________________________________________________
Tetromino::Tetromino(const Shape shape)
    : shape_(shape), color_(static_cast<int>(shape_) + 2) {
  // positioning of the tetromino
  if (shape == O) {
    x_ = 4;
    y_ = 2;
  } else if (shape == I) {
    x_ = 3;
    y_ = 0;
  } else {
    x_ = 3;
    y_ = 1;
  }
  // Initialization of the tetromino blocks
  // clang-format off
    switch (shape_) {
        case I:
            blocks_ = {{false, false, false, false},
                         {false, false, false, false},
                         {true, true, true, true},
                         {false, false, false, false}};
        break;
        case J:
            blocks_ = {{false, false, false},
                         {true, true, true},
                         {false, false, true}};
        break;
        case L:
            blocks_ = {{false, false, false},
                         {true, true, true},
                         {true, false, false}};
        break;
        case O:
            blocks_ = {{true, true},
                         {true, true}};
        break;
        case S:
            blocks_ = {{false, false, false},
                         {false, true, true},
                         {true, true, false}};
        break;
        case T:
            blocks_ = {{false, false, false},
                         {true, true, true},
                         {false, true, false}};
        break;
        case Z:
            blocks_ = {{false, false, false},
                         {true, true, false},
                         {false, true, true}};
        break;
        default:
            throw std::invalid_argument("Invalid shape");
    // clang-format on
  }
}

//______________________________________________________________________________________________________________________
int Tetromino::hardDrop(const Playfield &playfield) {
  // Move the tetromino down and lock it if it collides with the bottom or
  // another block
  int steps = 0;
  while (canMoveDown(playfield)) {
    y_++;
    steps++;
  }
  return steps;
}

//______________________________________________________________________________________________________________________
void Tetromino::rotateCW(const Playfield &playfield) {
  // Virtual rotation of the tetromino 90 degrees clockwise
  std::vector rotatedBlocks(blocks_.size(), std::vector<bool>(blocks_.size()));
  // Test for shape I
  // If Shape == I, exchange the 3 row and 3 column
  if (shape_ == I) {
    if (blocks_[2][0]) { // currently horizontal
      rotatedBlocks = {{false, false, true, false},
                       {false, false, true, false},
                       {false, false, true, false},
                       {false, false, true, false}};

    } else { // currently vertical
      rotatedBlocks = {{false, false, false, false},
                       {false, false, false, false},
                       {true, true, true, true},
                       {false, false, false, false}};
    }
  } else {
    for (size_t x = 0; x < blocks_.size(); ++x) {
      for (size_t y = 0; y < blocks_.size(); ++y) {
        rotatedBlocks[y][blocks_.size() - 1 - x] = blocks_[x][y];
      }
    }
  }

  // Prüfen, ob die neue Position gültig ist
  if (playfield.isValidPosition(rotatedBlocks, x_, y_)) {
    blocks_ = rotatedBlocks;
    return;
  }
  // Prüfen, ob Verschieben nach links oder rechts die Position gültig macht
  if (playfield.isValidPosition(rotatedBlocks, x_ + 1, y_)) {
    x_++;
    blocks_ = rotatedBlocks;
    return;
  }
  if (shape_ == I && playfield.isValidPosition(rotatedBlocks, x_ + 2, y_)) {
    x_ += 2;
    blocks_ = rotatedBlocks;
    return;
  }
  if (playfield.isValidPosition(rotatedBlocks, x_ - 1, y_)) {
    x_--;
    blocks_ = rotatedBlocks;
  }
}

//______________________________________________________________________________________________________________________
void Tetromino::rotateCCW(const Playfield &playfield) {
  // Rotate the tetromino 90 degrees counterclockwise
  std::vector rotatedBlocks(blocks_.size(), std::vector<bool>(blocks_.size()));
  // Test for shape I
  // If Shape == I, exchange the 3 row and 3 column
  if (shape_ == I) {
    if (blocks_[2][0]) { // currently horizontal
      rotatedBlocks = {{false, false, true, false},
                       {false, false, true, false},
                       {false, false, true, false},
                       {false, false, true, false}};
    } else {
      // currently vertical
      rotatedBlocks = {{false, false, false, false},
                       {false, false, false, false},
                       {true, true, true, true},
                       {false, false, false, false}};
    }
  } else {
    for (size_t y = 0; y < blocks_.size(); ++y) {
      for (size_t x = 0; x < blocks_.size(); ++x) {
        rotatedBlocks[blocks_.size() - 1 - x][y] = blocks_[y][x];
      }
    }
  }

  // Prüfen, ob die neue Position gültig ist
  if (playfield.isValidPosition(rotatedBlocks, x_, y_)) {
    blocks_ = rotatedBlocks;
    return;
  }

  // Prüfen, ob Verschieben nach links oder rechts die Position gültig macht
  if (playfield.isValidPosition(rotatedBlocks, x_ + 1, y_)) {
    x_++;
    blocks_ = rotatedBlocks;
    return;
  }
  if (shape_ == I && playfield.isValidPosition(rotatedBlocks, x_ + 2, y_)) {
    x_ += 2;
    blocks_ = rotatedBlocks;
    return;
  }
  if (playfield.isValidPosition(rotatedBlocks, x_ - 1, y_)) {
    x_--;
    blocks_ = rotatedBlocks;
  }
}

//______________________________________________________________________________________________________________________
bool Tetromino::canMoveLeft(const Playfield &playfield) const {
  return playfield.isValidPosition(blocks_, x_ - 1, y_);
}

//______________________________________________________________________________________________________________________
bool Tetromino::canMoveRight(const Playfield &playfield) const {
  return playfield.isValidPosition(blocks_, x_ + 1, y_);
}

//______________________________________________________________________________________________________________________
bool Tetromino::canMoveDown(const Playfield &playfield) const {
  return playfield.isValidPosition(blocks_, x_, y_ + 1);
}

//______________________________________________________________________________________________________________________
bool Tetromino::isOutsideLeft() const {
  for (size_t y = 0; y < blocks_.size(); ++y) {
    for (size_t x = 0; x < blocks_.size(); ++x) {
      if (blocks_[y][x]) {
        if (x_ + x < 0) {
          return true;
        }
      }
    }
  }
  return false;
}

//______________________________________________________________________________________________________________________
bool Tetromino::isOutsideRight() const {
  for (size_t y = 0; y < blocks_.size(); ++y) {
    for (size_t x = 0; x < blocks_.size(); ++x) {
      if (blocks_[y][x]) {
        if (x_ + x >= 10) {
          return true;
        }
      }
    }
  }
  return false;
}