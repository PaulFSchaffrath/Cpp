// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#pragma once

#include "./NcursesTerminalManager.h"
// Replace the previous line by the following lines to use
// OpenGL
// #include "OpenGL/OpenGLTerminalManager.h"
// using NcursesTerminalManager = OpenGLTerminalManager;
#include <string>
#include <unordered_map>
#include <vector>

// A 2D point with float coordinates.
class Point {
public:
  float longitude_;
  float latitude_;
};

// A 2D cell with size_t coordinates.
class Cell {
public:
  size_t row_;
  size_t col_;
  // To store the Cells in a hashMap we have
  // to define the equality == between Cells.
  bool operator==(const Cell &other) const {
    return row_ == other.row_ && col_ == other.col_;
  }
};

// We use Cell as the key type to a hash map, so we have to define
// a hash function
template <> struct std::hash<Cell> {
  size_t operator()(const Cell &p) const {
    auto hash1 = std::hash<size_t>{}(p.row_);
    auto hash2 = std::hash<size_t>{}(p.col_);
    return 2 * hash1 ^ hash2;
  }
};

class HeatMap {
private:
  // CellToCountMap becomes an alternative name for the complicated unordered
  // map type.
  using CellToCountMap = std::unordered_map<Cell, size_t>;
  std::vector<Point> points_;
  CellToCountMap heatMap_;

public:
  // Read all the points from the tsv file with the given filename and store
  // them in points_.
  void readPointsFromFile(const std::string &filename);

  // Compute the heat map using the points_ and the given number of rows and
  // columns.
  void computeHeatMap(size_t numRows, size_t numCols);

  // Draw the heat map on the stream using the NcursesTerminalManager.
  void drawHeatMap(NcursesTerminalManager *tm) const;

  // Const access to members for testing.
  const std::vector<Point> &points() { return points_; }
  const CellToCountMap heatMap() { return heatMap_; }

private:
  // Parse a single point from a single line of input
  Point parsePoint(const std::string &input) const;
};