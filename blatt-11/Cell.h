//
// Created by Paul Schaffrath on 04.07.24.
//

#pragma once

class Cell {
private:
  int x_;
  int y_;
  int color_;
  bool alive_;

public:
  // Constructor
  Cell(int x, int y, int color, bool alive);

  // Getter
  int getColor() const { return color_; };
  bool isAlive() const { return alive_; };
  int x() const { return x_; };
  int y() const { return y_; };

  // Setter
  void setColor(int color);
  void setAlive(bool alive);
};
