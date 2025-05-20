//
// Created by Paul Schaffrath on 28.07.24.
//

#include <Config.h>
#include <NCursesTerminalManager.h>
#include <Tetris.h>

int main(const int argc, char **argv) {
  const auto config = Config(argc, argv);
  auto terminalManager = NCursesTerminalManager(Config::colors());

  // Create the Tetris game with the provided arguments.
  Tetris tetris(terminalManager, config.rotateCW(), config.rotateCCW());
  tetris.play();
  return 0;
}
