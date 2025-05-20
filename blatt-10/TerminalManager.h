//
// Created by Paul Schaffrath on 01.07.24.
//

#ifndef BLATT_10_TERMINALMANAGER_H
#define BLATT_10_TERMINALMANAGER_H

#include <iostream>

// Abstract class for the terminal manager
class TerminalManager {
public:
    // Destructor
    virtual ~TerminalManager() = default;

    // Print a pixel on terminal
    virtual void drawPixel(int x, int y, int intensity) = 0;

    // Print a string to the terminal
    virtual void print(const std::string& str) = 0;

    // Read a string from the terminal
    virtual std::string read() = 0;

};

#endif //BLATT_10_TERMINALMANAGER_H
