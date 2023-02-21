#include "train.h"

Train::Train(Position pos, Color color, Direction heading) {
    this->pos = pos;
    this->color = color;
    this->heading = heading;
}

Color Train::getColor() {
    return color;
}

void Train::setColor(Color color) {
    this->color = color;
}

Position Train::getPosition() {
    return pos;
}

void Train::setPosition(Position pos) {
    this->pos = pos;
}

Direction Train::getHeading() {
    return heading;
}

void Train::setHeading(Direction dir) {
    this->heading = dir;
}

void Train::advance(Direction dir) {
    this->setPosition(this->pos.add(dir));
}
