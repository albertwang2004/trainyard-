#include "track.h"

Track::Track() {}

Track::Track(Direction end1, Direction end2) {
    this->end1 = end1;
    this->end2 = end2;
}

bool Track::operator==(const Track& t) {
    return ((end1 == t.end1) && (end2 == t.end2))
        || ((end2 == t.end1) && (end1 == t.end2));
}

std::string Track::getName() {
    return name((Direction)std::min((int)end1, (int)end2))
         + name((Direction)std::max((int)end1, (int)end2));
}
