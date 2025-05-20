// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#include "./HeatMap.h"
// NcursesTerminalManager is implicitly included by HeatMap.h
// This makes replacing it by OpenGL easier.
#include <iostream>
#include <string>
#include <unistd.h>

// Parse file with WKT points and draw the heat map.
int main(int argc, char **argv) {
  // Parse the command-line arguments.
  if (argc != 2) {
    std::cout << "Usage: ./HeatMapMain [file]" << std::endl;
    std::exit(1);
  }

  NcursesTerminalManager tm;
  HeatMap heatMap;
  const size_t numRows = tm.numRows();
  const size_t numCols = tm.numCols();

  std::string filename = argv[1];

  heatMap.readPointsFromFile(filename);
  heatMap.computeHeatMap(numRows, numCols);
  heatMap.drawHeatMap(&tm);
  tm.drawString(0, 0, "Press q to exit ...");
  tm.refresh();
  while (tm.getUserInput().keycode_ != 'q') {
    usleep(100'000);
  }
}