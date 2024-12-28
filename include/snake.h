#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Snake
{
public:
    Snake();
    void move();
    void grow();
    void render(sf::RenderWindow &window);
    void renderTarget(sf::RenderWindow &window, int targetpoints[20][2], int numTargets);
    bool didIhittarget(int targetpoints[20][2], int &numTargets);
    bool didIhitside();
    bool didIcollide();
    bool didIwin(int &numTargets);
    sf::Vector2f direction;

private:
    std::vector<sf::RectangleShape> segments;
};

#endif
