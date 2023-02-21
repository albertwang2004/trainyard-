#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include "direction.h"

class Position {
public:
    Position();
    Position(int x, int y);
    Position add(Direction dir);
    int x, y;
    int row, col;
    Position operator+(const Position& pos);
    Position operator-(const Position& pos);
    Direction directionTo(const Position& pos);

    // set and multiset compatibility
    friend bool operator<(const Position& t1, const Position& t2) {
        if (t1.x == t2.x)
            if (t1.y == t2.y)
                return false;
            else return t1.y < t2.y;
        else return t1.x < t2.x;
    }
    static int convert(int a);
};

#endif // POSITION_H_INCLUDED
