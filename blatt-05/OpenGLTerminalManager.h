// Copyright 2022, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.
//

#pragma once

#include <GLFW/glfw3.h>
#include <array>
#include <cstddef>
#include <ft2build.h>
#include <queue>
#include <string_view>
#include <unordered_map>
#include FT_FREETYPE_H

// Class for the input from the user.
class UserInput {
public:
  bool isEscape();
  bool isKeyUp();
  bool isKeyDown();
  bool isKeyLeft();
  bool isKeyRight();
  // The code of the key pressed.
  int keycode_;
  // Was the event a mousecklick.
  bool isMouseclick_;
  bool isMouseclick() { return isMouseclick_; }
  // If the event was a mousecklick, then the coordinates
  // of the mouseclick are stored here.
  int mouseRow_ = -1;
  int mouseCol_ = -1;
};

// A class managing the input and output via the terminal, using ncurses.
class OpenGLTerminalManager {
public:
  // Available colors.
  static int Black;
  static int White;
  static int Red;
  static int Green;

  // Constructor: initialize the terminal for use with ncurses.
  OpenGLTerminalManager();

  // Destructor: Clean up the screen.
  ~OpenGLTerminalManager();

  // Get input from the user.
  UserInput getUserInput();

  // Draw a "pixel" at the given position and with the given intensity between
  // The intensity has to be in [0.0, 1.0]
  void drawPixel(int row, int col, int color);

  // Draw a string at the given position and with the given intensity.
  // The intensity has to be in [0.0, 1.0]
  void drawString(int row, int col, const char *output);

  // Refresh the screen.
  void refresh();

  // Get the dimensions of the screen.
  int numRows() const { return numRows_; }
  int numCols() const { return numCols_; }

private:
  // The number of "logical" rows and columns of the screen.
  int numRows_ = 400;
  int numCols_ = 400;
  GLFWwindow *window;
  std::queue<unsigned int> keypresses;
  std::queue<std::pair<int, int>> mouseClicks;
  // texture buffer with RGB values
  using RGB = std::array<float, 3>;
  std::vector<RGB> pixels;
  std::unordered_map<int, RGB> colorMap_;
  GLuint texture;
  FT_Library ft;
  FT_Face face;
  struct Character {
    unsigned int textureID; // ID handle of the glyph texture
    std::tuple<unsigned int, unsigned int> size; // Size of glyph
    std::tuple<unsigned int, unsigned int>
        bearing;    // Offset from baseline to left/top of glyph
    FT_Pos advance; // Offset to advance to next glyph
  };
  // Hash function for std::pair<size_t, size_t>.
  struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const {
      return std::hash<T1>{}(pair.first) ^ std::hash<T2>{}(pair.second);
    }
  };
  std::unordered_map<char, Character> characters;
  std::unordered_map<std::pair<size_t, size_t>, char, pair_hash> charsToDraw;

  void renderText(std::string_view, int col, int row);
};
