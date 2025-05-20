//
// Created by Paul Schaffrath on 28.07.24.
//

#pragma once

#include <NCursesTerminalManager.h>

// Config class to give the tetris class the rotation keys of the command line
// arguments
class Config {
  int rotateCW_;
  int rotateCCW_;

  static const Color BLACK;
  static const Color BLACK2;
  static const Color RED;
  static const Color GREEN;
  static const Color BLUE;
  static const Color YELLOW;
  static const Color CYAN;
  static const Color MAGENTA;
  static const Color ORANGE;
  static const Color WHITE;
  static const Color GRAY;

  static const std::vector<std::pair<Color, Color>> colors_;

public:
  explicit Config(const int argc, char *argv[]) {
    if (argc != 3) {
      throw std::runtime_error("Usage: ./tetris <rotate_counterclockwise_key> "
                               "<rotate_clockwise_key>");
    }
    rotateCCW_ = argv[1][0];
    rotateCW_ = argv[2][0];
  }

  int rotateCW() const { return rotateCW_; }
  int rotateCCW() const { return rotateCCW_; }
  static const std::vector<std::pair<Color, Color>> &colors() {
    return colors_;
  }
};