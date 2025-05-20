//
// Created by Paul Schaffrath on 01.07.24.
//

#include "TerminalManager.h"

// Print a pixel on terminal
void TerminalManager::drawPixel(int x, int y, int intensity) {
    std::cout << "Pixel drawn at x: " << x << " y: " << y << " with intensity: " << intensity << std::endl;
}

// Print a string to the terminal
void TerminalManager::print(const std::string& str) {
    std::cout << "String printed: " << str << std::endl;
}

// Read a string from the terminal
std::string TerminalManager::read() {
    std::string str;
    std::cout << "Enter a string: ";
    std::cin >> str;
    return str;
}
