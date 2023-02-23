#pragma once

#include "tileType.h"
#include "track.h"
#include "position.h"
#include "direction.h"
#include "train.h"
#include "color.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

class MapLocation {
public:
    MapLocation();
    MapLocation(int x, int y);
    MapLocation(Position pos);
    MapLocation(int x, int y, TileType type, Direction output, Direction input, Color color = WHITE);
    MapLocation(Position pos, TileType type, Direction output, Direction input, Color color = WHITE);
    void setObject(TileType type, Direction output, Direction input, Color color = WHITE);
    void setConstants();
    void loadTrains(std::vector<Color> trains, bool hard);
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
    Color getColor();

    std::vector<Color> getTrains();
    int getTrainsLeft();

    std::string generateTrackName();

private:
    Position pos;
    TileType type;
    Direction output;
    Direction input;
    Color paint;

    std::vector<Color> trains;
    std::vector<Color> memTrains;
    std::vector<Color>::iterator currentTrain;
    int trainsDispensed;

    int numTracks;
    int trackCheckOrder;
    int memCheckOrder;
    Track tracks[2];
};
