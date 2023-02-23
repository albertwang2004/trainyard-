#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <algorithm>
#include <vector>
#include <iostream>

enum Color {
    WHITE = 0,
    RED = 3,
    YELLOW = 4,
    BLUE = 5,
    ORANGE = 7,
    PURPLE = 8,
    GREEN = 9,
    BROWN = 10
};

Color mix(Color c1, Color c2);

Color mix(std::vector<Color>& colors);

Color blue(Color c);

Color red(Color c);

std::string getName(Color c);

#endif // COLOR_H_INCLUDED
