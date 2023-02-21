#include "display.h"

Display::Display(Trainyard& game) {
    int height = game.X * tileSize + 3*tileSize/2;
    int width = game.Y * tileSize;
    sf::RenderWindow window(sf::VideoMode(width, height),"Trainyard++ - " + game.name);
    this->window = &window;
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        for (int x = 0; x < game.X; x++) {
            for (int y = 0; y < game.Y; y++) {
                drawObject(game.board[x][y]);
            }
        }
        window.display();
    }
}
void Display::load(std::string fn, int width, int height) {
    sf::Texture texture;
    texture.loadFromFile("assets/"+fn,
        sf::IntRect(0, 0, width, height));
    textures[fn]=texture;
}
void Display::place(std::string fn, int row, int col) {
    sf::Sprite s(textures[fn]);
    s.setPosition(sf::Vector2f(tileSize*col,tileSize*row));
    window->draw(s);
}
void Display::place(std::string fn, Position pos) {
    place(fn, pos.row, pos.col);
}
void Display::update(float time) {
}
void Display::drawObject(Train train) {
}
void Display::drawObject(MapLocation mapLocation) {
    std::string textureName = "tile" + mapLocation.generateTextureName() + ".png";
    if (textures.find(textureName) == textures.end()) {
        load(textureName, tileSize, tileSize);
    }
    place(textureName, mapLocation.getPosition());
}
sf::RenderWindow* Display::getWindow() {
    return window;
}
