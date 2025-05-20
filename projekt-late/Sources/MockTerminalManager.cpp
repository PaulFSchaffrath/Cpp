#include "./MockTerminalManager.h"

// _________________________________________________________________________
void MockTerminalManager::drawPixel(const int col_x, const int row_y,
                                    const int color) const {
  // This also "draws" Pixels that are outside of the screen, but this
  // behavior is consistent with NCurses which also does not crash
  // in this case.
  // Make the entry at the position the color of the pixel
  drawnPixels_[col_x][row_y] = color;
}

// _________________________________________________________________________
bool MockTerminalManager::isPixelDrawn(const int col_x, const int row_y) const {
  return drawnPixels_[col_x][row_y] > 1;
}

// _________________________________________________________________________
int MockTerminalManager::getPixelColor(const int col_x, const int row_y) const {
  return drawnPixels_[col_x][row_y];
}

// _________________________________________________________________________
void MockTerminalManager::drawString(const int col_x, const int row_y,
                                     int color, const char *str) const {
  // Store the string in the map with the position as the key.
  drawnStrings_[col_x][row_y] = {std::string(str), color};
}

//__________________________________________________________________________
bool MockTerminalManager::isStringDrawn(const int col_x,
                                        const int row_y) const {
  return !drawnStrings_[col_x][row_y].first.empty();
}

// _________________________________________________________________________
const char *MockTerminalManager::getString(const int col_x,
                                           const int row_y) const {
  return drawnStrings_[col_x][row_y].first.c_str();
}
