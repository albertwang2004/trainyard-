#ifndef DIRECTION_H_INCLUDED
#define DIRECTION_H_INCLUDED

#include <iostream>

enum Direction {
    NONE, N, NE, E, SE, S, SW, W, NW
};

std::pair<int,int> value(Direction dir);

Direction value(std::pair<int,int> vec);

Direction opposite(Direction dir);

Direction combine(Direction dir1, Direction dir2);

Direction rotateLeft(Direction dir);

Direction rotateRight(Direction dir);

#endif // DIRECTION_H_INCLUDED
