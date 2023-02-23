#include "direction.h"

std::pair<int,int> value(Direction dir) {
    switch (dir) {
    case NONE:
        return {0, 0};
    case N:
        return {-2, 0};
    case NE:
        return {-1, 1};
    case E:
        return {0, 2};
    case SE:
        return {1, 1};
    case S:
        return {2, 0};
    case SW:
        return {1, -1};
    case W:
        return {0, -2};
    case NW:
        return {-1, -1};
    }
}

std::string name(Direction dir) {
    switch (dir) {
    case NONE:
        return "";
    case N:
        return "N";
    case NE:
        return "NE";
    case E:
        return "E";
    case SE:
        return "SE";
    case S:
        return "S";
    case SW:
        return "SW";
    case W:
        return "W";
    case NW:
        return "NW";
    }
}

Direction value(std::pair<int,int> dir) {
    switch (10*dir.first+dir.second) {
    case 0:
        return NONE;
    case -20:
        return N;
    case -9:
        return NE;
    case 2:
        return E;
    case 11:
        return SE;
    case 20:
        return S;
    case 9:
        return SW;
    case -2:
        return W;
    case -11:
        return NW;
    }
}

Direction opposite(Direction dir) {
    switch (dir) {
    case NONE:
        return NONE;
    case N:
        return S;
    case NE:
        return SW;
    case E:
        return W;
    case SE:
        return NW;
    case S:
        return N;
    case SW:
        return NE;
    case W:
        return E;
    case NW:
        return SE;
    }
}

Direction combine(Direction dir1, Direction dir2) {
    if (dir1 == dir2) return dir1;
    std::pair<int,int> vec1 = value(dir1);
    std::pair<int,int> vec2 = value(dir2);
    std::pair<int,int> res = {vec1.first + vec2.first, vec1.second + vec2.second};
    if (res.first != 0 && res.second != 0) {
        res.first /= 2;
        res.second /= 2;
    }
    return value(res);
}

Direction rotateLeft(Direction dir) {
    switch (dir) {
    case NONE:
        return NONE;
    case N:
        return NW;
    case NE:
        return N;
    case E:
        return NE;
    case SE:
        return E;
    case S:
        return SE;
    case SW:
        return S;
    case W:
        return SW;
    case NW:
        return W;
    }
}

Direction rotateRight(Direction dir) {
    switch (dir) {
    case NONE:
        return NONE;
    case N:
        return NE;
    case NE:
        return E;
    case E:
        return SE;
    case SE:
        return S;
    case S:
        return SW;
    case SW:
        return W;
    case W:
        return NW;
    case NW:
        return N;
    }
}

float rotation(Direction dir) {
    switch (dir) {
    case NONE:
        return 0.f;
    case N:
        return 0.f;
    case NE:
        return 45.f;
    case E:
        return 90.f;
    case SE:
        return 135.f;
    case S:
        return 180.f;
    case SW:
        return 225.f;
    case W:
        return 270.f;
    case NW:
        return 315.f;
    }
}
