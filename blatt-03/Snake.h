// Copyright 2024, University of Freiburg
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#pragma once

// The total number of logical pixels on the screen.
extern int numPixelsX;
extern int numPixelsY;

// The position of the snake in pixels.
extern int posX;
extern int posY;

// The x and y component of the direction of the snake. vx * vx + vy * vy == 1
// must hold (the direction must be normalized), otherwise the speed is not
// correct (see moveSnake function).
extern int vx;
extern int vy;

// ___________________________________________________________________________

// Initialize the terminal for use with ncurses commands.
void initTerminal();

// Initialize the game.
void initGame();

// Draw a pixel at the position given by y and x. Note that a pixel consists of
// multiple space characters, depending on `pixelWidth` and `pixelHeight`.
void drawPixel(int y, int x, int color);

// Draw the snake (show == true: draws in black, show == true: draws in white).
void drawSnake(int color);

// Draw a border around the screen.
void drawBorder(int color);

// Return true iff the head of the snake is on our out of the border
bool collidesWithBorder();

// Update the position of the  snake when `milliseconds` have passed since the
// last call to `moveSnake`
void moveSnake();

// Update the direction and the speed of the snake given the last pressed key.
// Return false if `escape` was pressed, return true for any other key.
bool handleKey(int key);
