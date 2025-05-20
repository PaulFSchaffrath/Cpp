//
// Created by Paul Schaffrath on 02.08.24.
//

#include <Config.h>

const Color Config::BLACK = Color(0.0, 0.0, 0.0);
const Color Config::BLACK2 = Color(0.1, 0.1, 0.1);
const Color Config::RED = Color(1.0, 0.0, 0.0);
const Color Config::GREEN = Color(0.0, 1.0, 0.0);
const Color Config::BLUE = Color(0.25, 0.25, 1.0);
const Color Config::YELLOW = Color(1.0, 1.0, 0.0);
const Color Config::CYAN = Color(0.0, 1.0, 1.0);
const Color Config::MAGENTA = Color(1.0, 0.0, 1.0);
const Color Config::ORANGE = Color(1.0, 0.5, 0.0);
const Color Config::WHITE = Color(1.0, 1.0, 1.0);
const Color Config::GRAY = Color(0.5, 0.5, 0.5);

// Static initialization of the colors vector in the Config class
const std::vector<std::pair<Color, Color>> Config::colors_ = {
    {BLACK, BLACK},  {BLACK2, BLACK}, {RED, BLACK},     {GREEN, BLACK},
    {YELLOW, BLACK}, {BLUE, BLACK},   {MAGENTA, BLACK}, {CYAN, BLACK},
    {ORANGE, BLACK}, {WHITE, BLACK},  {GRAY, BLACK}};