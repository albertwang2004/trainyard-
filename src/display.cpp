#include "display.h"

Display::Display(Trainyard& game) {
    int height = game.X * tileSize + 3*tileSize/2;
    int width = game.Y * tileSize;
    sf::RenderWindow window(sf::VideoMode(width, height),"Trainyard++ - " + game.name);
    this->window = &window;
}
void Display::update(float time) {
}
void Display::loadSprites() {
}
void Display::drawObject(Train train) {
}
void Display::drawObject(MapLocation mapLocation) {
}
