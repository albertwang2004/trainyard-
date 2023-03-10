#include "display.h"

bool inRange(int a, int x, int y) {
    return a >= x && a < y;
}

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

float smoothRotate(float a, float b, float t) {
    if ((int)(b - a + 360) % 360 == 270) return a - t*90.f;
    return a + t*90.f;
}

Display::Display(Trainyard& game, float factor) {
    speed = factor;
    int height = game.X * tileSize + 3*tileSize/2;
    int width = game.Y * tileSize;
    sf::RenderWindow window(sf::VideoMode(width, height),"Trainyard++ - " + game.name);
    this->window = &window;
    crashed = false;
    solved = true;
    mode = EDIT;
    inputType = NONE;
    float diff = 0.f;
    timeElapsed = 0;
    diff = 0;
    game.reset();
    mode = EDIT;
    int prevShRow = -1;
    int prevShCol = -1;
    bool isRemoval = true;
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
            else if (e.type == sf::Event::MouseButtonPressed) {
                int x = e.mouseButton.x;
                int y = e.mouseButton.y;
                int trueRow = y/tileSize;
                int trueCol = x/tileSize;
                int subRow = y*2/tileSize;
                int subCol = x*2/tileSize;
                switch (inputType) {
                case NONE: {
                    prevShRow = -1;
                    prevShCol = -1;
                    if (inRange(subRow, 2*game.X+1, 2*game.X+3) && inRange(subCol, 0, 2)) {
                        inputType = PLAY;
                    }
                    else if (inRange(subRow, 2*game.X+1, 2*game.X+3) && inRange(subCol, 2, 4)) {
                        inputType = PAUSE;
                    }
                    else if (inRange(subRow, 2*game.X+1, 2*game.X+3) && inRange(subCol, 4, 6)) {
                        inputType = STOP;
                    }
                    else {
                        inputType = BOARD;
                        isRemoval = true;
                    }
                    break;
                }
                }
            } else if (e.type == sf::Event::MouseButtonReleased) {
                switch (inputType) {
                case BOARD:
                    if (isRemoval && mode == EDIT) {
                        int x = e.mouseButton.x;
                        int y = e.mouseButton.y;
                        int trueRow = y/tileSize;
                        int trueCol = x/tileSize;
                        if (inRange(trueRow, 0, game.X) && inRange(trueCol, 0, game.Y)) {
                            game.board[trueRow][trueCol].popTrack();
                            game.board[trueRow][trueCol].popTrack();
                        }
                    }
                    break;
                case PLAY:
                    if (mode == EDIT) {
                        unpauseTime = timeSinceEpochMillisec();
                        timeUpdated = 0;
                    }
                    if (mode == PAUSED) {
                        unpauseTime = timeSinceEpochMillisec();
                    }
                    mode = PLAYING;
                    break;
                case PAUSE:
                    if (mode == PLAYING) {
                        timeElapsed += difftime(timeSinceEpochMillisec(), unpauseTime) * speed;
                    }
                    mode = PAUSED;
                    break;
                case STOP:
                    timeElapsed = 0;
                    diff = 0;
                    game.reset();
                    mode = EDIT;
                    break;
                }
                inputType = NONE;
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mode == EDIT){
                sf::Vector2i v = sf::Mouse::getPosition(window);
                int x = v.x;
                int y = v.y;
                int shRow = (y + tileSize/4)*2/tileSize;
                int shCol = (x + tileSize/4)*2/tileSize;
                if (inputType == BOARD) {
                    //std::cout << x << " " << y << " : " << shRow << " " << shCol << std::endl;
                    if (inRange(shRow, 0, 2*game.Y+1) && inRange(shCol, 0, 2*game.X+1)) if ((shRow + shCol) & 1) {
                        if (prevShRow != -1) { // is this a valid spot to draw?
                            int taxi = abs(prevShRow - shRow)  + abs(prevShCol - shCol);
                            if (taxi != 0) isRemoval = false;
                            if (taxi == 2) if (!(prevShRow % 2 == 0 && prevShRow == shRow) && !(prevShCol % 2 == 0 && prevShCol == shCol))
                            {
                                if (prevShRow == shRow) {
                                    int mid = (prevShCol + shCol)/2;
                                    game.board[shRow / 2][mid / 2].addTrack(Track(W, E));
                                    //std::cout << shRow/2 << " " << mid/2 << " WE" << std::endl;
                                } else if (prevShCol == shCol) {
                                    int mid = (prevShRow + shRow)/2;
                                    game.board[mid / 2][shCol / 2].addTrack(Track(N, S));
                                    //std::cout << mid/2 << " " << shCol/2 << " NS" << std::endl;
                                } else {
                                    int midRow = (prevShRow + shRow)/2;
                                    int midCol = (prevShCol + shCol)/2;
                                    if (midRow % 2 == 0) midRow++;
                                    if (midCol % 2 == 0) midCol++;
                                    Position pos = Position(midRow * 2, midCol * 2);
                                    Direction in = pos.directionTo(Position(prevShRow * 2, prevShCol * 2));
                                    Direction out = pos.directionTo(Position(shRow * 2, shCol * 2));
                                    //std::cout << midRow/2 << " " << midCol/2 << " " << rotation(in) << " " << rotation(out) << std::endl;
                                    game.board[midRow / 2][midCol / 2].addTrack(Track(in,out));
                                }
                            }
                        }
                        prevShRow = shRow;
                        prevShCol = shCol;
                    }
                    break;
                }
            }
        }
        bool doTick = false;
        //std::cout << diff << std::endl;
        if (mode == PLAYING) {
            diff = (difftime(timeSinceEpochMillisec(), unpauseTime) * speed + timeElapsed)/ 1000.0;
            //std::cout << diff << std::endl;
            if (diff > timeUpdated) {
                ++timeUpdated;
                game.merge();
                game.simulateTick();
                doTick = true;
            }
        }
        window.clear(sf::Color::Black);
        for (int x = 0; x < game.X; x++) {
            for (int y = 0; y < game.Y; y++) {
                drawObject(game.board[x][y], diff);
            }
        }
        for (Train* t : game.trains) {
            drawObject(t, diff);
        }
        place("start.png", game.X + 0.5, 0);
        place("pause.png", game.X + 0.5, 1);
        place("stop.png", game.X + 0.5, 2);
        if (game.crashed) {
            place("fail.png", game.X + 0.5, 3);
        } else if (game.isSolved()) {
            place("success.png", game.X + 0.5, 3);
        } else if (mode == PLAYING) {
            place("pending.png", game.X + 0.5, 3);
        }
        if ((diff - (long)diff) != 0.f || mode != PLAYING)
        window.display();
    }
}
void Display::load(std::string fn, int width, int height) {
    sf::Texture texture;
    texture.loadFromFile("assets/"+fn,
        sf::IntRect(0, 0, width, height));
    textures[fn]=texture;
}
void Display::place(std::string fn, float row, float col) {
    if (textures.find(fn) == textures.end()) {
        load(fn, tileSize, tileSize);
    }
    sf::Sprite s(textures[fn]);
    s.setPosition(sf::Vector2f(tileSize*col,tileSize*row));
    window->draw(s);
}
void Display::place(std::string fn, Position pos) {
    place(fn, pos.row, pos.col);
}
void Display::drawObject(Train* train, float diff) {
    float t = diff - (long)diff;
    if (train->colorHistory.size() < 3) {
        Position pos = train->getPosition();
        std::string fn = "train_" + getName(train->colorHistory.begin()[0]) + ".png";

        if (textures.find(fn) == textures.end()) {
            sf::Image image;
            image.loadFromFile("assets/" + fn);
            image.createMaskFromColor(background);

            sf::Texture tx;
            tx.loadFromImage(image);
            textures[fn] = tx;
        }
        sf::Sprite s(textures[fn]);
        sf::Vector2f half = sf::Vector2f(trainSize / 2.f,trainSize / 2.f);
        s.setOrigin(half);
        s.setScale(t,t);
        s.setRotation(rotation(train->getHeading()));
        s.setPosition(sf::Vector2f(tileSize*train->getPosition().y/4.0,tileSize*train->getPosition().x/4.0));
        window->draw(s);
    } else {
        Position initPos = train->posHistory.end()[-3];
        Position finPos = train->posHistory.end()[-1];
        Color actualColor = train->colorHistory.end()[-3 + (int)(t/0.5)];
        Direction initHeading = train->headingHistory.end()[-3];
        Direction finHeading = train->headingHistory.end()[-1];

        float initRot = rotation(initHeading);
        float finRot = rotation(finHeading);

        sf::Vector2f half = sf::Vector2f(trainSize / 2.f,trainSize / 2.f);
        sf::Vector2f init = sf::Vector2f(tileSize*initPos.y/4.0,tileSize*initPos.x/4.0);
        sf::Vector2f fin = sf::Vector2f(tileSize*finPos.y/4.0,tileSize*finPos.x/4.0);

        std::string fn = "train_" + getName(actualColor) + ".png";
        if (textures.find(fn) == textures.end()) {
            sf::Image image;
            image.loadFromFile("assets/" + fn);
            image.createMaskFromColor(background);

            sf::Texture tx;
            tx.loadFromImage(image);
            textures[fn] = tx;
        }
        sf::Sprite s(textures[fn]);

        s.setOrigin(half);

        bool turnRight = isRightTurn(initHeading, finHeading);


        if (initHeading == finHeading) {
            s.setPosition(t * fin + (1 - t) * init);
            s.setRotation(t * finRot + (1 - t) * initRot);
        } else {
            if (turnRight) {
                Position center = Position(0,0).add(E);
                Position newCenter = initPos.add(finHeading);
                sf::Vector2f v = sf::Vector2f(tileSize*center.y/4.0,tileSize*center.x/4.0);
                sf::Vector2f w = sf::Vector2f(tileSize*newCenter.y/4.0,tileSize*newCenter.x/4.0);
                s.setRotation(initRot);
                s.setPosition(w);
                s.setOrigin(v + half);
                s.setRotation(smoothRotate(initRot,finRot,t));
            } else {
                Position center = Position(0,0).add(W);
                Position newCenter = initPos.add(finHeading);
                sf::Vector2f v = sf::Vector2f(tileSize*center.y/4.0,tileSize*center.x/4.0);
                sf::Vector2f w = sf::Vector2f(tileSize*newCenter.y/4.0,tileSize*newCenter.x/4.0);
                s.setRotation(initRot);
                s.setPosition(w);
                s.setOrigin(v + half);
                s.setRotation(smoothRotate(initRot,finRot,t));
            }

        }
        window->draw(s);
    }
}
void Display::drawObject(MapLocation mapLocation, float diff) {
    float t = diff - (long)diff;
    switch (mapLocation.getType()) {
    case NORMAL: {
        std::string textureName = "tile" + mapLocation.generateTrackName() + ".png";
        place(textureName, mapLocation.getPosition());
        break;
    }
    case ROCK: {
        std::string textureName = "tile_unpassable.png";
        place(textureName, mapLocation.getPosition());
        break;
    }
    case START: {
        std::string fn = "tile_start.png";
        if (textures.find(fn) == textures.end()) {
            load(fn, tileSize, tileSize);
        }
        sf::Sprite s(textures[fn]);
        sf::Vector2f half = sf::Vector2f(tileSize / 2.f,tileSize / 2.f);
        s.setOrigin(half);
        s.setRotation(rotation(mapLocation.getOutput()));
        s.setPosition(sf::Vector2f(tileSize*mapLocation.getPosition().col,tileSize*mapLocation.getPosition().row) + half);
        window->draw(s);

        std::vector<Color> trains = mapLocation.getTrains();
        int idx = mapLocation.getTrainsLeft();
        int num = 0;
        int i = 0;
        if (diff <= trains.size())
        for (Color c : trains) {
            ++i;
            if (i < idx) continue;
            std::string fn = "start_" + getName(c) + ".png";
            if (textures.find(fn) == textures.end()) {
                load(fn, tileSize, tileSize);
            }
            sf::Sprite s(textures[fn]);
            s.setOrigin(sf::Vector2f(plusSize/2, plusSize/2));
            float adjRow = 0.25 * (num / 3 + 1) + mapLocation.getPosition().row;
            float adjCol = 0.25 * (num % 3 + 1) + mapLocation.getPosition().col;
            s.setPosition(sf::Vector2f(adjCol * tileSize, adjRow * tileSize));
            if (num == 0) s.setScale(1-t,1-t);
            window->draw(s);
            ++num;
            if (num > 9) break;
        }
        break;
    }
    case END: {
        std::string fn = "tile_end.png";
        if (textures.find(fn) == textures.end()) {
            load(fn, tileSize, tileSize);
        }
        sf::Sprite s(textures[fn]);
        sf::Vector2f half = sf::Vector2f(tileSize / 2.f,tileSize / 2.f);
        s.setOrigin(half);
        s.setRotation(rotation(mapLocation.getInput()));
        s.setPosition(sf::Vector2f(tileSize*mapLocation.getPosition().col,tileSize*mapLocation.getPosition().row) + half);
        window->draw(s);

        std::vector<Color> trains = mapLocation.getTrains();
        int num = 0;
        for (Color c : trains) {
            std::string fn = "end_" + getName(c) + ".png";
            if (textures.find(fn) == textures.end()) {
                load(fn, tileSize, tileSize);
            }
            sf::Sprite s(textures[fn]);
            s.setOrigin(sf::Vector2f(plusSize/2, plusSize/2));
            float adjRow = 0.25 * (num / 3 + 1) + mapLocation.getPosition().row;
            float adjCol = 0.25 * (num % 3 + 1) + mapLocation.getPosition().col;
            s.setPosition(sf::Vector2f(adjCol * tileSize, adjRow * tileSize));
            window->draw(s);
            ++num;
            if (num > 9) break;
        }
        break;
    }
    case SPLITTER: {
        std::string fn = "tile_splitter.png";
        if (textures.find(fn) == textures.end()) {
            load(fn, tileSize, tileSize);
        }
        sf::Sprite s(textures[fn]);
        sf::Vector2f half = sf::Vector2f(tileSize / 2.f,tileSize / 2.f);
        s.setOrigin(half);
        s.setRotation(rotation(mapLocation.getInput()));
        s.setPosition(sf::Vector2f(tileSize*mapLocation.getPosition().col,tileSize*mapLocation.getPosition().row) + half);
        window->draw(s);
        break;
    }
    case PAINTER:
        Direction input = mapLocation.getInput();
        Direction output = mapLocation.getOutput();
        std::string fn;
        if (input == opposite(output)) {
            fn = "tile_painter_f.png";
        } else if (isRightTurn(input, output)) {
            fn = "tile_painter_r.png";
        } else {
            fn = "tile_painter_l.png";
        }
        if (textures.find(fn) == textures.end()) {
            load(fn, tileSize, tileSize);
        }
        sf::Sprite s(textures[fn]);
        sf::Vector2f half = sf::Vector2f(tileSize / 2.f,tileSize / 2.f);
        s.setOrigin(half);
        s.setRotation(rotation(output));
        s.setPosition(sf::Vector2f(tileSize*mapLocation.getPosition().col,tileSize*mapLocation.getPosition().row) + half);
        window->draw(s);

        Color color = mapLocation.getColor();
        std::string fnPaint = "paint_" + getName(color) + ".png";
        if (textures.find(fnPaint) == textures.end()) {
            load(fnPaint, tileSize * 3/4, tileSize * 3/4);
        }
        place(fnPaint, mapLocation.getPosition().row + 0.125, mapLocation.getPosition().col + 0.125);
        break;
    }
}
sf::RenderWindow* Display::getWindow() {
    return window;
}
