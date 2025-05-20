// Copyright 2024, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//         Claudius Korzen <korzen@cs.uni-freiburg.de>.
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#include "./GameOfLife.h"
#include "./TerminalManager.h"

int main() {
  TerminalManager terminalManager;
  GameOfLife gameOfLife(&terminalManager);
  gameOfLife.play();
}
