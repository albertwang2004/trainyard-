#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "trainyard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Display {
public:
    Display(Trainyard& game);
    void load(std::string fn, int width, int height);
    void place(std::string fn, int row, int col);
    void place(std::string fn, Position pos);
    void update(float time);
    void loadTextures();
    void drawObject(Train train);
    void drawObject(MapLocation mapLocation);
    sf::RenderWindow* getWindow();
private:
    Trainyard game;
    sf::RenderWindow* window;
    int tileSize = 64;
    std::map<std::string,sf::Texture> textures;
};

#endif
