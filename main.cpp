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
    TR.board[0][0].setObject(START, S, NONE);
    TR.board[0][0].loadTrains(red, true);
    TR.board[2][0].setObject(START, N, NONE);
    TR.board[2][0].loadTrains(blue, true);
    TR.board[1][0].setObject(SPLITTER, NONE, S);


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

    std::cout << x << std::endl;

    Display d(TR);
    return 0;
}
