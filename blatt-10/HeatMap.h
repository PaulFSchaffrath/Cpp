// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#pragma once

#include "./Cell.h"
#include "./TerminalManager.h"
#include <string>
#include <unordered_map>
#include <vector>

// A 2D point with float coordinates.
class Point {
public:
  float longitude_;
  float latitude_;
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

  // Draw the heat map on the stream using the TerminalManager.
  void drawHeatMap(TerminalManager *tm) const;

  // Const access to members for testing.
  const std::vector<Point> &points() { return points_; }
  const CellToCountMap heatMap() { return heatMap_; }

private:
  // Parse a single point from a single line of input
  Point parsePoint(const std::string &input) const;
};
