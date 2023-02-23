#ifndef DIRECTION_H_INCLUDED
#define DIRECTION_H_INCLUDED

#include <iostream>
#include <string>

enum Direction {
    NONE, N, S, W, E, NE, SE, SW, NW
};

std::pair<int,int> value(Direction dir);

std::string name(Direction dir);

Direction value(std::pair<int,int> vec);

Direction opposite(Direction dir);

Direction combine(Direction dir1, Direction dir2);

Direction rotateLeft(Direction dir);

Direction rotateRight(Direction dir);

float rotation(Direction dir);

#endif // DIRECTION_H_INCLUDED
