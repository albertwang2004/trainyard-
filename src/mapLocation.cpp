#include "maplocation.h"

MapLocation::MapLocation() {}

MapLocation::MapLocation(int x, int y) {
    this->pos = Position(x, y);
    this->setObject(NORMAL, NONE, NONE);
    numTracks = 0;
    trackCheckOrder = 0;
}

MapLocation::MapLocation(Position pos) {
    this->pos = pos;
    this->setObject(NORMAL, NONE, NONE);
    numTracks = 0;
    trackCheckOrder = 0;
}
MapLocation::MapLocation(int x, int y, TileType type, Direction output, Direction input) {
    this->pos = Position(x, y);
    this->setObject(type, output, input);
    numTracks = 0;
    trackCheckOrder = 0;
}
MapLocation::MapLocation(Position pos, TileType type, Direction output, Direction input) {
    this->pos = pos;
    this->setObject(type, output, input);
    numTracks = 0;
    trackCheckOrder = 0;
}
void MapLocation::setObject(TileType type, Direction output, Direction input) {
    this->type = type;
    this->output = output;
    this->input = input;
}
void MapLocation::loadTrains(std::multiset<Color> trains, bool hard) {
    // deep copying
    this->trains = std::multiset<Color>();
    for (Color t : trains) {
        this->trains.insert(t);
    }
    if (hard) {
        this->memTrains = std::multiset<Color>();
        for (Color t : trains) {
            this->memTrains.insert(t);
        }
    }
    this->currentTrain = this->trains.begin();
}
void MapLocation::setConstants() {
    numTracks = 0;
    trackCheckOrder = 0;
    memCheckOrder = 0;
}
void MapLocation::reset() {
    trackCheckOrder = memCheckOrder;
    loadTrains(memTrains, false);
}
bool MapLocation::switchCheckOrder(bool user) {
    if (numTracks < 2) return false;
    trackCheckOrder ^= 1;
    if (user) memCheckOrder = trackCheckOrder;
    return true;
}
bool MapLocation::popTrack() {
    if (numTracks == 0) return false;
    trackCheckOrder = 0;
    --numTracks;
    return true;
}
bool MapLocation::addTrack(Track t) {
    if (type != NORMAL) return false;
    if (numTracks == 2) return false;
    if (numTracks == 1)
        if (t == tracks[0])
            return false;
    tracks[numTracks] = t;
    ++numTracks;
    return true;
}
bool MapLocation::canOutputTrain() {
    return (type == START) && (currentTrain != trains.end());
}
Train* MapLocation::outputTrain() {
    Train* ret = new Train(pos.add(output), *currentTrain, output);
    ++currentTrain;
    return ret;
}
bool MapLocation::acceptTrain(Train t) {
    auto it = trains.find(t.getColor());
    if (it != trains.end()) {
        trains.erase(it);
        return true;
    }
    return false;
}
bool MapLocation::satisfied() {
    return (type != END) || trains.empty();
}
Direction MapLocation::getTrackHeading(Train t) {
    if (numTracks == 0) return NONE;
    for (int it = 0, curr = trackCheckOrder; it < numTracks; ++it, curr=(curr+1)%numTracks) {
        Track currentTrack = tracks[curr];
        if (currentTrack.end1 == opposite(t.getHeading())) {
            return combine(currentTrack.end2,t.getHeading());
        }
        if (currentTrack.end2 == opposite(t.getHeading())) {
            return combine(currentTrack.end1,t.getHeading());
        }
    }
    return NONE;
}
Position MapLocation::getPosition() {
    return pos;
}
TileType MapLocation::getType() {
    return type;
}
Direction MapLocation::getOutput() {
    return output;
}
Direction MapLocation::getInput() {
    return input;
}
std::string MapLocation::generateTextureName() {
    switch (type) {
    case NORMAL:
        {
            std::string out = "_track";
            for (int it = 0, curr = trackCheckOrder; it < numTracks; ++it, curr=(curr+1)%numTracks) {
                Track currentTrack = tracks[curr];
                out += "_" + currentTrack.getName();
            }
            return out;
        }
    case ROCK:
        return "_unpassable";
    case START:
        return "";
    case END:
        return "";
    case SPLITTER:
        return "";
    case PAINTER:
        return "";
    }
}
