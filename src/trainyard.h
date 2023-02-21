#ifndef TRAINYARD_H_INCLUDED
#define TRAINYARD_H_INCLUDED

#include "maplocation.h"
#include "train.h"
#include "track.h"

#include <vector>
#include <map>
#include <iostream>

class Trainyard {
public:
    Trainyard();
    Trainyard(int X, int Y, std::string name);
    void reset();
    // returns 1 if error occurred, 0 if fine
    bool simulateTick(bool debug = false);
    bool isSolved();

    bool isValidPosition(Position p);

    int X, Y, T;
    MapLocation** board;
    std::multiset<Train*> trains;
    std::string name;
};

#endif
