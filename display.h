#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "trainyard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Display {
public:
    Display(Trainyard& game);
    void update(float time);
    void loadSprites();
    void drawObject(Train train);
    void drawObject(MapLocation mapLocation);
private:
    Trainyard game;
    sf::RenderWindow* window;
    int tileSize = 64;
};

#endif
