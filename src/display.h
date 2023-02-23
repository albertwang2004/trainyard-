#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "trainyard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <math.h>

class Display {
public:
    enum Mode {
        PLAYING, PAUSED, EDIT
    };
    enum InputType {
        NONE, BOARD, PLAY, PAUSE, STOP
    };
    Display(Trainyard& game, float factor = 3.f);
    void load(std::string fn, int width, int height);
    void place(std::string fn, float row, float col);
    void place(std::string fn, Position pos);
    void loadTextures();
    void drawObject(Train* train, float diff);
    void drawObject(MapLocation mapLocation, float diff);
    sf::RenderWindow* getWindow();

private:
    Trainyard game;
    sf::RenderWindow* window;
    int tileSize = 64;
    int trainSize = 32;
    int plusSize = 16;
    bool crashed = false;
    bool solved = true;
    sf::Color background = sf::Color{64, 64, 64};
    std::map<std::string,sf::Texture> textures;
    Mode mode;
    InputType inputType;
    uint64_t unpauseTime;
    uint64_t timeElapsed;
    int timeUpdated = 0;
    float speed;
};

#endif
