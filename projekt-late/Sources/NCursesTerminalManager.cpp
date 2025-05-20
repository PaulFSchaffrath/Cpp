// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>

#include <NCursesTerminalManager.h>
#include <ncurses.h>

static constexpr size_t systemColors = 16;

// NOTE: We need `ncurses` stuff only in the implementation of
// `TerminalManager`, nowhere else (not even in `TerminalManager.h`, let alone
// anywhere in the files implementing the game logic).

// ____________________________________________________________________________
NCursesTerminalManager::NCursesTerminalManager(
    const std::vector<std::pair<Color, Color>> &colors)
    : numColors_(static_cast<int>(colors.size())) {
  // Initialize ncurses and some settings suitable for gaming.
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, nullptr);
  mouseinterval(0);

  // Initialize some colors.
  start_color();
  if (COLORS - systemColors < colors.size() * 2) {
    endwin();
    throw std::runtime_error{
        "The TerminalManager requires a terminal with"
        " at least 200 colors. Consider setting `TERM=xterm-256color` before"
        " starting the application"};
  }
  // Define as many shades of a certain color (red in this case) as there are
  // colors.
  auto initColor = [](const short i, const Color &color) {
    const auto r = static_cast<short>(1000 * color.red());
    const auto g = static_cast<short>(1000 * color.green());
    const auto b = static_cast<short>(1000 * color.blue());
    init_color(i, r, g, b);
  };
  for (size_t i = 0; static_cast<int>(i) < numColors_; ++i) {
    const auto &[fgColor, bgColor] = colors.at(i);
    initColor(static_cast<short>(2 * (i + systemColors)), fgColor);
    initColor(static_cast<short>(2 * (systemColors + i) + 1), bgColor);
    init_pair(static_cast<short>(i + systemColors),
              static_cast<short>(2 * (systemColors + i)),
              static_cast<short>(2 * (systemColors + i) + 1));
  }
  // Set the logical dimensions of the screen.
  numRows_ = LINES;
  numCols_ = COLS / 2;
}

// ____________________________________________________________________________
NCursesTerminalManager::~NCursesTerminalManager() { endwin(); }

// ____________________________________________________________________________
void NCursesTerminalManager::refresh() { ::refresh(); }

// ____________________________________________________________________________
void NCursesTerminalManager::drawPixel(const int col_x, const int row_y,
                                       const int color) const {
  if (color >= numColors_) {
    throw std::runtime_error("Invalid color given to drawPixel");
  }
  attron(COLOR_PAIR(color + systemColors));
  attron(A_REVERSE);
  mvprintw(row_y, 2 * col_x, "  ");
  attroff(A_REVERSE);
}

// ____________________________________________________________________________
UserInput NCursesTerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keycode_ = getch();
  MEVENT event;
  if ((userInput.keycode_ == KEY_MOUSE) && (getmouse(&event) == OK)) {
    if (event.bstate & BUTTON1_PRESSED) {
      userInput.mouseRow_ = event.y;
      userInput.mouseCol_ = event.x / 2;
    }
  }
  return userInput;
}

// ____________________________________________________________________________
void NCursesTerminalManager::drawString(const int col_x, const int row_y,
                                        const int color,
                                        const char *str) const {
  if (color >= numColors_) {
    throw std::runtime_error("Invalid color given to drawString");
  }
  attron(COLOR_PAIR(color + systemColors));
  mvprintw(row_y, 2 * col_x, "%s", str);
}
