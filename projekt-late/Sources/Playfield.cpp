//
// Created by Paul Schaffrath on 28.07.24.
//

#include <Playfield.h>
#include <Tetris.h>

#include <algorithm>

bool Playfield::isRowFull(const int row) const {
  // Check if all cells in the given row are occupied (not 0)
  return std::all_of(std::begin(playfield_), std::end(playfield_),
                     [row](const auto &column) { return column[row] != 0; });
}

//______________________________________________________________________________________________________________________
void Playfield::clearRow(const int row) {
  // Shift all rows above the given row down by one position
  for (int y = row; y > 0; --y) {
    for (auto &x : playfield_) {
      x[y] = x[y - 1];
    }
  }
  // Clear the top row (it has been shifted down)
  for (auto &x : playfield_) {
    x[0] = 0;
  }
}

int Playfield::getPlayfield(const int x, const int y) const {
  // Check if the coordinates are within the playfield boundaries
  if (x < 0 || x >= 10 || y < 0 || y >= 22) {
    throw std::out_of_range("Invalid playfield coordinates");
  }
  return playfield_[x][y];
}

//______________________________________________________________________________________________________________________
int Playfield::fullRowsCleared() {
  // Iterate through each row and clear it if it's full
  int counter = 0;
  for (int y = 0; y < 22; ++y) {
    if (isRowFull(y)) {
      clearRow(y);
      counter++;
    }
  }
  // Return the number of cleared rows
  return counter;
}

//______________________________________________________________________________________________________________________
void Playfield::lockTetromino(const std::unique_ptr<Tetromino> &tetromino) {
  // Iterate through the tetromino's blocks and place them on the playfield at
  // their current position
  for (int i = 0; i < static_cast<int>(tetromino->blocks().size()); ++i) {
    for (int j = 0; j < static_cast<int>(tetromino->blocks().size()); j++) {
      if (tetromino->blocks()[j][i]) {
        // The cordinates of the playfield represent the color of the block
        playfield_[tetromino->x() + i][tetromino->y() + j] = tetromino->color();
      }
    }
  }
}

//______________________________________________________________________________________________________________________
bool Playfield::isValidPosition(const std::vector<std::vector<bool>> &blocks,
                                const int newX, const int newY) const {
  // Iterate through the blocks and check if they are within the playfield
  // boundaries and not colliding with existing blocks
  for (size_t y = 0; y < blocks.size();
       ++y) { // Iterate through each row of the block
    for (size_t x = 0; x < blocks.size();
         ++x) { // Iterate through each cell of the block (column)
      if (blocks[y][x]) {
        // Check bounds
        if (newX + x < 0 || newX + x >= 10 || newY + y < 0 || newY + y >= 22) {
          return false;
        }
        // Check collision with existing blocks - existing block means != 0
        if (playfield_[newX + x][newY + y] != 0) {
          return false; // Return false if a collision is detected
        }
      }
    }
  }
  return true; // Return true if no collision is detected
}

void Playfield::clearField() {
  // Clear the playfield by setting all cells to 0
  for (auto &x : playfield_) {
    for (auto &y : x) {
      y = 0;
    }
  }
}
