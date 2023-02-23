#include <iostream>
#include "trainyard.h"
#include "display.h"

int main()
{
    Trainyard TR = Trainyard(7, 7, "test");
    std::multiset<Color> red;
    red.insert(RED);
    std::multiset<Color> blue;
    blue.insert(BLUE);
    std::multiset<Color> purple;
    purple.insert(PURPLE);
    TR.board[0][0].setObject(START, S, NONE);
    TR.board[0][0].loadTrains(red, true);
    TR.board[2][0].setObject(START, N, NONE);
    TR.board[2][0].loadTrains(blue, true);
    TR.board[1][0].addTrack(Track(N,E));
    TR.board[1][0].addTrack(Track(S,E));
    TR.board[1][1].setObject(END, NONE, W);
    TR.board[1][1].loadTrains(purple, true);/*

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
    Display d1(TR);
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
