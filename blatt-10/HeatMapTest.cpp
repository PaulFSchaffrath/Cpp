// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>
//

#include "./HeatMap.h"
#include "./MockTerminalManager.h"
#include <gtest/gtest.h>

TEST(HeatMap, ReadPointsFromFile) {
  HeatMap heatMap;
  heatMap.readPointsFromFile("testPoints.tsv");

  const auto &p = heatMap.points();
  ASSERT_EQ(3u, p.size());
  ASSERT_FLOAT_EQ(0.0, p[0].longitude_);
  ASSERT_FLOAT_EQ(2.5, p[0].latitude_);
  ASSERT_FLOAT_EQ(5.0, p[1].longitude_);
  ASSERT_FLOAT_EQ(2.5, p[1].latitude_);
  ASSERT_FLOAT_EQ(5.0, p[2].longitude_);
  ASSERT_FLOAT_EQ(2.5, p[2].latitude_);
}

TEST(HeatMap, ComputeHeatMap) {
  HeatMap heatMap;
  heatMap.readPointsFromFile("testPoints.tsv");
  heatMap.computeHeatMap(9, 9);

  const auto &m = heatMap.heatMap();
  // Two of the three points have exactly the same coordinates,
  // so there are only 2 points.
  ASSERT_EQ(2u, m.size());

  // We have two different row coordinates, we expect them to scale to the full
  // range, rows 0 and 8.
  // We have only one col coordinate, we expect this to be centered at
  // the middle (column 4);
  ASSERT_TRUE(m.count(Cell{4, 0}));
  ASSERT_TRUE(m.count(Cell{4, 8}));

  auto c = Cell{4, 0};
  ASSERT_EQ(1u, m.at(c));
  c = Cell{4, 8};
  ASSERT_EQ(2u, m.at(c));

  // These tests currently don't test the scaling of the longitude, but only the
  // behavior that was expected in the exercise sheet
}

TEST(HeatMap, DrawHeatMap) {
  HeatMap heatMap;
  heatMap.readPointsFromFile("testPoints.tsv");
  MockTerminalManager tm(9, 9);
  heatMap.computeHeatMap(tm.numRows(), tm.numCols());
  heatMap.drawHeatMap(&tm);

  for (int i = 0; i < tm.numRows(); ++i) {
    for (int j = 0; j < tm.numCols(); ++j) {
      if (i != 4 || (j != 0 && j != 8)) {
        ASSERT_FALSE(tm.isPixelDrawn(i, j));
      }
    }
  }

  int row = 4;
  int col = 0;
  ASSERT_TRUE(tm.isPixelDrawn(row, col));
  ASSERT_TRUE(tm.isPixelInverse(row, col));
  ASSERT_FLOAT_EQ(0.5, tm.getIntensity(row, col));
  col = 8;
  ASSERT_TRUE(tm.isPixelDrawn(row, col));
  ASSERT_TRUE(tm.isPixelInverse(row, col));
  ASSERT_FLOAT_EQ(1.0, tm.getIntensity(row, col));
}
