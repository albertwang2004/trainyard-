#ifndef TRAIN_H_INCLUDED
#define TRAIN_H_INCLUDED

#include "position.h"
#include "color.h"
#include <vector>

class Train {
public:
    Train(Position pos, Color color, Direction heading);
    Color getColor();
    void setColor(Color color);
    Position getPosition();
    void setPosition(Position pos);
    Direction getHeading();
    void setHeading(Direction dir);
    void advance(Direction dir);
    void heartbeat();

    // set and multiset compatibility
    friend bool operator<(const Train& t1, const Train& t2) {
        if (t1.pos.x == t2.pos.x)
            if (t1.pos.y == t2.pos.y)
                if (t1.color == t2.color)
                    if (t1.heading == t2.heading)
                        return false;
                    else return t1.heading < t2.heading;
                else return t1.color < t2.color;
            else return t1.pos.y < t2.pos.y;
        else return t1.pos.x < t2.pos.x;
    }

    bool operator==(const Train t) {
        return (pos.x == t.pos.x)
            && (pos.y == t.pos.y)
            && (heading == t.heading)
            && (color == t.color);
    }

    std::vector<Color> colorHistory;
    std::vector<Position> posHistory;
    std::vector<Direction> headingHistory;

private:
    Position pos;
    Color color;
    Direction heading;
};

#endif
