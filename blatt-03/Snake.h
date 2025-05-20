// Copyright 2024, Paul Schaffrath

// Position of the box
extern int xPos;
extern int yPos;
extern int rotation;

extern int windowHeight;
extern int windowWidth;

//Initialize Ncurses
void initTerminal();

// Initialize Game
void initGame();

// Draw Pixel
void drawPixel(int row, int column, int color);

// Draw Borderline
void drawBorder(int color);

// Draw Snake
void drawSnake(int color);

// Returns if Snake out of gamefield
bool collidesWithBorder();

// Move Snake
void moveSnake();

// Set rotation or end game with ESC
bool handleKey(int key);

// Clean up Ncurses
void endNcurses();
