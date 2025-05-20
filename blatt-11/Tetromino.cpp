//
// Created by Paul Schaffrath on 03.07.24.
//

#include "Tetromino.h"
#include <random>

int Tetromino::nextId = 0;

// Zufallszahlengenerator initialisieren
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 6);

// Definition der statischen Member-Variable tetrominoShapes
const std::vector<std::vector<std::vector<int>>> Tetromino::tetrominoShapes = {
    // I
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
    // J
    {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
    // L
    {{2, 0}, {0, 1}, {1, 1}, {2, 1}},
    // O
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
    // S
    {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
    // T
    {{1, 0}, {0, 1}, {1, 1}, {2, 1}},
    // Z
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}}};

//______________________________________________________________________________
Tetromino::Tetromino(const TetrominoType type)
    : shape_(type), position_{5, 0}, locked_(false), alive_(true),
      rotationState_(0) {
  id_ = nextId++;
  width_ = 0;
  color_ = static_cast<int>(type);
  initShape();
}

//______________________________________________________________________________
Tetromino::~Tetromino() = default;

//______________________________________________________________________________
void Tetromino::moveLeft() { position_.first--; }

//______________________________________________________________________________
void Tetromino::moveRight() { position_.first++; }

//______________________________________________________________________________
void Tetromino::moveDown() { position_.second++; }

//______________________________________________________________________________
// TODO: Implement the drop function
void Tetromino::drop() { position_.second = 19; }

//______________________________________________________________________________
void Tetromino::rotate() {
  rotationState_++;
  rotationState_ %= 4;
}

//______________________________________________________________________________
const std::vector<Cell> &Tetromino::getCells() const { return cells_; }

//______________________________________________________________________________
bool Tetromino::isTouchingLeftWall() const { return position_.first == 0; }

//______________________________________________________________________________
bool Tetromino::isTouchingRightWall() const { return position_.first == 9; }

//______________________________________________________________________________
void Tetromino::initShape() {
  cells_.clear();
  for (const auto &offset : tetrominoShapes[shape_]) {
    cells_.emplace_back(position_.first + offset[0],
                        position_.second + offset[1], color_, true);
  }
}

//______________________________________________________________________________
void Tetromino::setRandomShape(const TetrominoType lastType) {
  auto type = static_cast<TetrominoType>(dis(gen));
  if (type == lastType) {
    type = static_cast<TetrominoType>(dis(gen));
  }
  shape_ = type;
  initShape();
}

//______________________________________________________________________________
void Tetromino::reset(const TetrominoType type) {
  position_.first = 0;
  position_.second = 0;
  rotationState_ = 0;
  locked_ = false;
  color_ = type;
  alive_ = true;

  setRandomShape(type);
  width_ = 0;
}
