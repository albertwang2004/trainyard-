#ifndef TRACK_H_INCLUDED
#define TRACK_H_INCLUDED

#include "position.h"
#include "direction.h"
#include <string>
#include <algorithm>

class Track {
public:
    Track();
    Track(Direction end1, Direction end2);
    bool operator==(const Track& t);
    Direction end1;
    Direction end2;

    std::string getName();
};


#endif
