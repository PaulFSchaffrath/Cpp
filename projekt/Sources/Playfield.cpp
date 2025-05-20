//
// Created by Paul Schaffrath on 28.07.24.
//

#include <Playfield.h>
#include <Tetris.h>

//______________________________________________________________________________________________________________________
bool Playfield::isRowFull(const int row) const {
  for (const auto &i : playfield_) {
    if (i[row] == 0) {
      return false;
    }
  }
  return true;
}

//______________________________________________________________________________________________________________________
void Playfield::clearRow(const int row) {
  for (int y = row; y > 0; --y) {
    for (int x = 0; x < 10; ++x) {
      playfield_[x][y] = playfield_[x][y - 1];
    }
  }
  // Clear the top row (it has been shifted down)
  for (int x = 0; x < 10; ++x) {
    playfield_[x][0] = 0;
  }
}

int Playfield::getPlayfield(const int x, const int y) const {
  if (x < 0 || x >= 10 || y < 0 || y >= 22) {
    throw std::out_of_range("Invalid playfield coordinates");
  }
  return playfield_[x][y];
}

//______________________________________________________________________________________________________________________
int Playfield::fullRowsCleared() {
  int counter = 0;
  for (int y = 0; y < 22; ++y) {
    if (isRowFull(y)) {
      clearRow(y);
      counter++;
    }
  }
  return counter;
}

//______________________________________________________________________________________________________________________
void Playfield::lockTetromino(const std::unique_ptr<Tetromino> &tetromino) {
  for (int i = 0; i < static_cast<int>(tetromino->blocks().size()); ++i) {
    for (int j = 0; j < static_cast<int>(tetromino->blocks().size()); j++) {
      if (tetromino->blocks()[j][i]) {
        playfield_[tetromino->x() + i][tetromino->y() + j] = tetromino->color();
      }
    }
  }
}

//______________________________________________________________________________________________________________________
bool Playfield::isValidPosition(const std::vector<std::vector<bool>> &blocks,
                                const int newX, const int newY) const {
  for (size_t x = 0; x < blocks.size(); ++x) {
    for (size_t y = 0; y < blocks.size(); ++y) {
      if (blocks[x][y]) {
        // Check bounds
        if (newX + y < 0 || newX + y >= 10 || newY + x < 0 || newY + x >= 22) {
          return false;
        }
        // Check collision with existing blocks
        if (playfield_[newX + y][newY + x] != 0) {
          return false;
        }
      }
    }
  }
  return true;
}

void Playfield::clearField() {
  for (auto &x : playfield_) {
    for (auto &y : x) {
      y = 0;
    }
  }
}
