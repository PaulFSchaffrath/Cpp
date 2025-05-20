//
//  Copyright 2024, Paul Schaffrath.
//  <ps609@students.uni-freiburg.de>
//

#include "TerminalManager.h"
#include "Tetris.h"

// Global colors
static const Color black(0.0f, 0.0f, 0.0f);
static const Color white(1.0f, 1.0f, 1.0f);
static const Color red(1.0f, 0.0f, 0.0f);
static const Color green(0.0f, 1.0f, 0.0f);
static const Color blue(0.0f, 0.0f, 1.0f);
static const Color yellow(1.0f, 1.0f, 0.0f);
static const Color magenta(1.0f, 0.0f, 1.0f);
static const Color cyan(0.0f, 1.0f, 1.0f);

int main() {

  // Colorpairs for the terminal
  const std::vector<std::pair<Color, Color>> colors = {
      {black, white},  {red, white},     {green, white}, {blue, white},
      {yellow, white}, {magenta, white}, {cyan, white},  {white, black}};

  auto terminalManager = TerminalManager(colors);
  const Tetris tetris(&terminalManager);
  tetris.play();

  return 0;
}
