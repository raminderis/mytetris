#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "snake.h"

class Game
{
public:
    void run();
    void render();
    void handleInput();
    void gamemove();

private:
    Snake snake;
    void initialize();
    void update();
    void closeGame(std::string &message);
    int a;
    int ta;
    int b;
    int tb;
    int rx;
    int ry;
    int state;
    int targetpoints[20][2];
    int numTargets;
    sf::RenderWindow window;
};

#endif
