To use the OpenGL-based TerminalManager, you have to

1. Install GLFW and Freetype (Instructions for Ubuntu)
sudo apt install libglfw3 libglfw3-dev libfreetype6-dev
2. In your code, include the `OpenGLTerminalManager.h` instead of `TerminalManager.h`.
3. Below this include, add the line
using TerminalManager = OpenGLTerminalManager;

4. In the Makefile, uncomment the line with the additional `LIBS`.

Please let us know if you run into any trouble, we'll try to help you, 
but first solve the actual task using the ncurses-based TerminalManager.


