#include "direction.h"
#include "position.h"


Position::Position() {}

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

Position Position::add(Direction dir) {
    std::pair<int,int> vec = value(dir);
    return Position(x + vec.first, y + vec.second);
}

Position Position::operator+(const Position& pos) {
    return Position(x + pos.x, y + pos.y);
}

Position Position::operator-(const Position& pos) {
    return Position(x - pos.x, y - pos.y);
}

Direction Position::directionTo(const Position& pos) {
    Position diff = *this - pos;
    return opposite(value({diff.x, diff.y}));
}
