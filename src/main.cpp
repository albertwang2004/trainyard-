#include <iostream>
#include "trainyard.h"
#include "display.h"
#include <fstream>

void readFromFile(std::string fn, Trainyard& TR) {
    std::ifstream fin(fn);
    int x, y;
    fin >> x >> y;
    TR = Trainyard(x, y, fn);
    while (true) {
        fin >> x >> y;
        if (x == -1 || y == -1) break;
        int z; fin >> z;
        TileType tt = (TileType)z;
        switch (tt) {
        case NORMAL:
            TR.board[x][y].setObject(tt, NONE, NONE);
            break;
        case ROCK:
            TR.board[x][y].setObject(tt, NONE, NONE);
            break;
        case START: {
            int a, b, c; fin >> a >> b >> c;
            Color color = (Color)a;
            Direction input = (Direction)b;
            Direction output = (Direction)c;
            TR.board[x][y].setObject(tt, output, input, color);
            int n; fin >> n;
            std::vector<Color> s;
            for (int i = 0; i < n; i++) {
                int m; fin >> m;
                s.push_back((Color)m);
            }
            TR.board[x][y].loadTrains(s, true);
            break;
        }
        case END: {
            int a, b, c; fin >> a >> b >> c;
            Color color = (Color)a;
            Direction input = (Direction)b;
            Direction output = (Direction)c;
            TR.board[x][y].setObject(tt, output, input, color);
            int n; fin >> n;
            std::vector<Color> s;
            for (int i = 0; i < n; i++) {
                int m; fin >> m;
                s.push_back((Color)m);
            }
            TR.board[x][y].loadTrains(s, true);
            break;
        }
        case SPLITTER: {
            int a, b, c; fin >> a >> b >> c;
            Color color = (Color)a;
            Direction input = (Direction)b;
            Direction output = (Direction)c;
            TR.board[x][y].setObject(tt, output, input, color);
            break;
        }
        case PAINTER: {
            int a, b, c; fin >> a >> b >> c;
            Color color = (Color)a;
            Direction input = (Direction)b;
            Direction output = (Direction)c;
            TR.board[x][y].setObject(tt, output, input, color);
            break;
        }
        }
    }
}

int main() {/*
    Trainyard TR = Trainyard(7, 7, "test");
    std::vector<Color> red;
    red.push_back(RED);
    red.push_back(BLUE);
    std::vector<Color> blue;
    blue.push_back(BLUE);
    blue.push_back(RED);
    std::vector<Color> purple;
    purple.push_back(PURPLE);
    purple.push_back(PURPLE);
    std::vector<Color> orange;
    orange.push_back(ORANGE);
    orange.push_back(ORANGE);
    TR.board[0][0].setObject(START, S, NONE);
    TR.board[0][0].loadTrains(red, true);
    TR.board[2][0].setObject(START, N, NONE);
    TR.board[2][0].loadTrains(blue, true);
    TR.board[1][1].setObject(END, NONE, W);
    TR.board[1][1].loadTrains(purple, true);
    TR.board[3][3].setObject(PAINTER, W, S, WHITE);
    TR.board[4][3].setObject(PAINTER, N, S, BLUE);
    TR.board[5][3].setObject(PAINTER, E, N, ORANGE);

    TR.board[5][1].setObject(START, N, NONE);
    TR.board[5][1].loadTrains(purple, true);
    TR.board[3][5].setObject(END, NONE, S);
    TR.board[3][5].loadTrains(orange, true);*/

    /*TR.board[1][0].addTrack(Track(N,E));
    TR.board[1][0].addTrack(Track(S,E));
    TR.board[4][1].addTrack(Track(N,S));
    TR.board[3][1].addTrack(Track(S,E));
    TR.board[3][2].addTrack(Track(W,E));
    TR.board[5][4].addTrack(Track(W,E));
    TR.board[5][5].addTrack(Track(W,N));
    TR.board[4][5].addTrack(Track(N,S));*/
    /*

    TR.board[3][0].setObject(START, E, NONE);

    std::multiset<Color> colorful;
    colorful.insert(PURPLE);
    colorful.insert(GREEN);
    colorful.insert(ORANGE);
    colorful.insert(BROWN);

    TR.board[3][0].loadTrains(colorful, true);
    TR.board[3][1].addTrack(Track(E,W));
    TR.board[3][2].setObject(SPLITTER, NONE, W);
    TR.board[2][2].addTrack(Track(N,S));
    TR.board[2][2].addTrack(Track(E,S));
    TR.board[1][2].addTrack(Track(W,S));
    TR.board[1][1].addTrack(Track(W,E));
    TR.board[2][3].setObject(END, NONE, W);
    TR.board[2][3].loadTrains(blue, true);*/
    while (true) {
        std::cout << "enter name of file to load" << std::endl;
        std::string fn;
        std::cin >> fn;
        Trainyard TR;
        readFromFile("stages/" + fn + ".tr", TR);
        Display d1(TR, 10.f);
    }
/*

    for (Train* t : TR.trains) {
        std::cout << t->getPosition().x << " " << t->getPosition().y << " ";
        std::cout << t->getColor() << " " << t->getHeading() << std::endl;
    }

    bool x = TR.simulateTick(true);

    std::cout << std::endl;

    for (Train* t : TR.trains) {
        std::cout << t->getPosition().x << " " << t->getPosition().y << " ";
        std::cout << t->getColor() << " " << t->getHeading() << std::endl;
    }
    std::cout << x << std::endl;

    x = TR.simulateTick(true);

    std::cout << std::endl;

    for (Train* t : TR.trains) {
        std::cout << t->getPosition().x << " " << t->getPosition().y << " ";
        std::cout << t->getColor() << " " << t->getHeading() << std::endl;
    }

    std::cout << x << std::endl;

    x = TR.simulateTick(true);

    std::cout << std::endl;

    for (Train* t : TR.trains) {
        std::cout << t->getPosition().x << " " << t->getPosition().y << " ";
        std::cout << t->getColor() << " " << t->getHeading() << std::endl;
    }

    std::cout << x << std::endl;*/
    return 0;
}
