#include "maplocation.h"

MapLocation::MapLocation() {
    setConstants();
}

MapLocation::MapLocation(int x, int y) {
    this->pos = Position(x, y);
    this->setObject(NORMAL, NONE, NONE);
}

MapLocation::MapLocation(Position pos) {
    this->pos = pos;
    this->setObject(NORMAL, NONE, NONE);
}
MapLocation::MapLocation(int x, int y, TileType type, Direction output, Direction input, Color color) {
    this->pos = Position(x, y);
    this->setObject(type, output, input, color);
}
MapLocation::MapLocation(Position pos, TileType type, Direction output, Direction input, Color color) {
    this->pos = pos;
    this->setObject(type, output, input, color);
}
void MapLocation::setObject(TileType type, Direction output, Direction input, Color color) {
    this->type = type;
    this->output = output;
    this->input = input;
    this->paint = color;
    setConstants();
}
void MapLocation::loadTrains(std::vector<Color> trains, bool hard) {
    trainsDispensed = 0;
    // deep copying
    this->trains = std::vector<Color>();
    for (Color t : trains) {
        this->trains.push_back(t);
    }
    if (hard) {
        this->memTrains = std::vector<Color>();
        for (Color t : trains) {
            this->memTrains.push_back(t);
        }
    }
    this->currentTrain = this->trains.begin();
}
void MapLocation::setConstants() {
    numTracks = 0;
    trackCheckOrder = 0;
    memCheckOrder = 0;
    trainsDispensed = 0;
    loadTrains(std::vector<Color>(),true);
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
    if (numTracks == 2) {
        if (tracks[0] == t) return false;
        tracks[1] = tracks[0];
        tracks[0] = t;
        return true;
    }
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
    ++trainsDispensed;
    return ret;
}
bool MapLocation::acceptTrain(Train t) {
    auto it = find(trains.begin(), trains.end(), t.getColor());
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
Color MapLocation::getColor() {
    return paint;
}
std::vector<Color> MapLocation::getTrains() {
    return trains;
}
int MapLocation::getTrainsLeft() {
    return trainsDispensed;
}
std::string MapLocation::generateTrackName() {
    std::string out = "_track";
    for (int it = 0, curr = trackCheckOrder; it < numTracks; ++it, curr=(curr+1)%numTracks) {
        Track currentTrack = tracks[curr];
        out += "_" + currentTrack.getName();
    }
    return out;
}
