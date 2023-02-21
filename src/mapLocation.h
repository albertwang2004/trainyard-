#pragma once

#include "tileType.h"
#include "track.h"
#include "position.h"
#include "direction.h"
#include "train.h"
#include "color.h"
#include <iostream>
#include <iterator>
#include <set>

class MapLocation {
public:
    MapLocation();
    MapLocation(int x, int y);
    MapLocation(Position pos);
    MapLocation(int x, int y, TileType type, Direction output, Direction input);
    MapLocation(Position pos, TileType type, Direction output, Direction input);
    void setObject(TileType type, Direction output, Direction input);
    void setConstants();
    void loadTrains(std::multiset<Color> trains, bool hard);
    void reset();

    bool switchCheckOrder(bool user);
    bool popTrack();
    bool addTrack(Track t);

    bool canOutputTrain();
    Train* outputTrain();

    bool acceptTrain(Train t);
    bool satisfied();

    Direction getTrackHeading(Train t);
    Position getPosition();
    TileType getType();
    Direction getOutput();
    Direction getInput();

    std::string generateTextureName();

private:
    Position pos;
    TileType type;
    Direction output;
    Direction input;

    std::multiset<Color> trains;
    std::multiset<Color> memTrains;
    std::multiset<Color>::iterator currentTrain;

    int numTracks;
    int trackCheckOrder;
    int memCheckOrder;
    Track tracks[2];
};
