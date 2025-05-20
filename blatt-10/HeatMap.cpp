// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//
#include "./HeatMap.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>

// __________________________________________________________________
Point HeatMap::parsePoint(const std::string &input) const {
  size_t pos1 = input.find('(');
  size_t pos2 = input.find(' ', pos1 + 1);

  // Atof takes a const char* and automatically stops when the
  // number has fully parsed, so atof("1.2 Kartoffelsalat") will
  // be parsed as 1.2.
  float lng = std::atof(input.data() + pos1 + 1);
  float lat = std::atof(input.data() + pos2 + 1);
  return Point{lng, lat};
}

// ____________________________________________________________________________
void HeatMap::readPointsFromFile(const std::string &filename) {
  std::ifstream pointsFile(filename);
  std::string line;
  while (std::getline(pointsFile, line)) {
    points_.push_back(parsePoint(line));
  }
}

// ____________________________________________________________________________
void HeatMap::computeHeatMap(size_t numRows, size_t numCols) {
  auto minMaxLongitude = std::minmax_element(
      points_.begin(), points_.end(), [](const Point &a, const Point &b) {
        return a.longitude_ < b.longitude_;
      });
  auto minMaxLatitude = std::minmax_element(
      points_.begin(), points_.end(),
      [](const Point &a, const Point &b) { return a.latitude_ < b.latitude_; });

  // std::minmax_element returns a pair [minElement, maxElement] of iterators.
  // Iterators can be treated like pointers, so *(minMaxLongitude.first) is the
  // point with the smallest longitude.

  // Store the min and max of latitude and longitude
  float minLng = minMaxLongitude.first->longitude_;
  float maxLng = minMaxLongitude.second->longitude_;

  float minLat = minMaxLatitude.first->latitude_;
  float maxLat = minMaxLatitude.second->latitude_;

  // The following block is optional: The distance (in kilometers) in the
  // latitude is always constant, but in the longitude it depends on the
  // latitude. We correct this factor in the following to get a nicer
  // display for countries that lie far from the equator.
  float averageLat = (maxLat + minLat) / 2;

  const float pi = std::acos(-1);
  const float lngScaling = std::cos((averageLat / 360.0 * 2 * pi));
  for (auto &point : points_) {
    point.longitude_ *= lngScaling;
  }
  maxLng *= lngScaling;
  minLng *= lngScaling;

  // We scale the latitude and longitude by the same factor s.t. one of them
  // completely fills the screen.
  float rowScaling = numRows / (maxLat - minLat);
  float colScaling = numCols / (maxLng - minLng);
  ;

  float scaling = std::min(rowScaling, colScaling);

  // One of the coordinates will not cover the screen, compute an offset s.t.
  // the map is centered (optional).
  size_t colOffset = (numCols - (maxLng - minLng) * scaling) / 2;
  size_t rowOffset = (numRows - (maxLat - minLat) * scaling) / 2;

  for (const Point &point : points_) {
    // Compute to which row and column the point will be mapped.
    size_t row = (point.latitude_ - minLat) * scaling + rowOffset;
    size_t col = (point.longitude_ - minLng) * scaling + colOffset;
    // The points that lie exactly on the highest latitude or longitude
    // have a row or column index that is too high now, map them back to the
    // highest row/ column.
    if (row >= numRows)
      row = numRows - 1;
    if (col >= numCols)
      col = numCols - 1;
    // Latitudes grow from south to north but rows from top to bottom.
    // Invert the row index s.t. the countries are not displayed upside down.
    row = numRows - 1 - row;
    // Add an entry for the heat map of the cell for this point.
    heatMap_[Cell{row, col}]++;
  }
}

// _____________________________________________________________________________
void HeatMap::drawHeatMap(TerminalManager *tm) const {
  if (heatMap_.empty()) {
    return;
  }
  // First compute the maximum number of points in a cell.
  // This will be used to compute the intensity between 0 and 1.
  size_t maxCellCount = 0;
  for (const auto &cellAndCount : heatMap_) {
    auto count = cellAndCount.second;
    maxCellCount = std::max(count, maxCellCount);
  }

  for (const auto &[cell, count] : heatMap_) {
    float intensity = 1.0 * count / maxCellCount;
    tm->drawPixel(cell.row_, cell.col_, true, intensity);
  }
  tm->refresh();
}