#include "trainyard.h"

Trainyard::Trainyard() {}

Trainyard::Trainyard(int X, int Y, std::string name) {
    this->X = X;
    this->Y = Y;
    board = new MapLocation*[X];
    for (int x = 0; x < X; x++) {
        board[x] = new MapLocation[Y];
        for (int y = 0; y < Y; y++) {
            board[x][y] = MapLocation(4*x + 2, 4*y + 2);
        }
    }
    trains = std::multiset<Train*>();
    this->name = name;
}

void Trainyard::reset() {
    T = 0;
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            board[x][y].reset();
        }
    }
}

bool Trainyard::simulateTick(bool debug) {
    bool crash = false;

    std::multiset<Train*> collisionQueue[X][Y];

    // queue all trains for updating
    for (Train* t : trains) {
        Position trainSquare = t->getPosition().add(t->getHeading());
        if (isValidPosition(trainSquare))
            collisionQueue[trainSquare.row][trainSquare.col].insert(t);
        else
            trains.erase(t);
    }

    // intra-square collisions
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            MapLocation zone = board[x][y];
            Position center = zone.getPosition();
            if (zone.getType() == SPLITTER) {
                for (Train* t : collisionQueue[x][y]) {
                    if (opposite(t->getHeading()) == zone.getInput()) {
                        trains.erase(t);
                        Direction heading = t->getHeading();
                        trains.insert(new Train(
                                center.add(rotateLeft(rotateLeft(heading))),
                                blue(t->getColor()),
                                rotateLeft(rotateLeft(heading))));
                        trains.insert(new Train(
                                center.add(rotateRight(rotateRight(heading))),
                                red(t->getColor()),
                                rotateRight(rotateRight(heading))));
                    } else {
                        crash = true;
                        trains.erase(t);
                        continue;
                    }
                }
            } else {
                std::map<Direction,std::vector<Color>> mixingZone;
                std::map<Direction,Color> mixingOutput;
                for (Train* t : collisionQueue[x][y]) {
                    Direction trackHeading = zone.getTrackHeading(*t);
                    if (debug) {
                        std::cout << t->getPosition().x << " " << t->getPosition().y << " ";
                        std::cout << t->getColor() << " " << t->getHeading() << std::endl;
                        std::cout << "now heading " << trackHeading << std::endl;
                    }
                    if (trackHeading == NONE) {
                        crash = true;
                        trains.erase(t);
                        continue;
                    }
                    t->setHeading(trackHeading);
                    t->advance(trackHeading);
                    Direction directionFromCenter = center.directionTo(t->getPosition());
                    mixingZone[directionFromCenter].push_back(t->getColor());
                }
                for (auto& spot : mixingZone) {
                    mixingOutput[spot.first] = mix(spot.second);
                }
                for (Train* t : collisionQueue[x][y]) {
                    Direction directionFromCenter = center.directionTo(t->getPosition());
                    t->setColor(mixingOutput[directionFromCenter]);
                    t->advance(t->getHeading());
                    directionFromCenter = center.directionTo(t->getPosition());
                    t->setHeading(directionFromCenter);
                }

            }
        }
    }

    if (debug) {
        std::cout << "done intra-square collisions" << std::endl;
        for (Train* t : trains) {
            std::cout << t->getPosition().x << " " << t->getPosition().y << " ";
            std::cout << t->getColor() << " " << t->getHeading() << std::endl;
        }
    }

    // dispense trains
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            if (board[x][y].canOutputTrain()) {
                trains.insert(board[x][y].outputTrain());
            }
        }
    }

    if (debug) {
        std::cout << "dispensed trains" << std::endl;
        for (Train* t : trains) {
            std::cout << t->getPosition().x << " " << t->getPosition().y << " ";
            std::cout << t->getColor() << " " << t->getHeading() << std::endl;
        }
    }

    // inter-square mixing
    std::map<Position,std::vector<Color>> interMixingZone;

    for (Train* t : trains) {
        interMixingZone[t->getPosition()].push_back(t->getColor());
    }

    for (Train* t : trains) {
        Color newColor = mix(interMixingZone[t->getPosition()]);
        t->setColor(newColor);
    }

    if (debug) {
        std::cout << "done inter-square collisions" << std::endl;
        for (Train* t : trains) {
            std::cout << t->getPosition().x << " " << t->getPosition().y << " ";
            std::cout << t->getColor() << " " << t->getHeading() << std::endl;
        }
    }

    // merge trains
    std::multiset<Train*> update;
    for (Train* t : trains) {
        bool unique = true;
        for (Train* u : update) {
            if ((*t) == (*u)) {
                unique = false;
            }
        }
        if (unique) update.insert(t);
    }
    this->trains = update;

    if (debug) {
        std::cout << "done merging" << std::endl;
        for (Train* t : trains) {
            std::cout << t->getPosition().x << " " << t->getPosition().y << " ";
            std::cout << t->getColor() << " " << t->getHeading() << std::endl;
        }
    }

    // update tick
    ++T;
    return crash;
}

bool Trainyard::isSolved() {
    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            if (!board[x][y].satisfied()) return false;
        }
    }
    return trains.empty();
}

bool Trainyard::isValidPosition(Position p) {
    if (p.x < 0) return false;
    if (p.x > 4*X) return false;
    if (p.y < 0) return false;
    if (p.y > 4*Y) return false;
    return true;
}
