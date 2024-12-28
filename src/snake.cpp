#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "game.h"
#include "snake.h"
#include <thread>
#include <chrono>

using namespace std;

Snake::Snake()
{
    sf::RectangleShape segment(sf::Vector2f(20, 20));
    segment.setPosition(100, 100);
    segment.setFillColor(sf::Color::Blue);
    segments.push_back(segment);
    direction = sf::Vector2f(20, 0);
}

bool Snake::didIhittarget(int targetpoints[20][2], int &numTargets)
{
    sf::Vector2f position = segments[0].getPosition();
    for (int i = 0; i < numTargets; i++)
    {
        if (targetpoints[i][0] == position.x && targetpoints[i][1] == position.y)
        {
            for (int j = i; j < numTargets - 1; ++j)
            {
                targetpoints[j][0] = targetpoints[j + 1][0];
                targetpoints[j][1] = targetpoints[j + 1][1];
            }
            --numTargets;
            return true;
        }
    }
    return false;
}

bool Snake::didIhitside()
{
    sf::Vector2f position = segments[0].getPosition();
    if (position.x > 780 || position.y > 580 || position.x < 0 || position.y < 0)
    {
        return true;
    }
    return false;
}

bool Snake::didIcollide()
{
    sf::Vector2f position = segments[0].getPosition();
    for (size_t i = segments.size(); i > 1; --i)
    {
        sf::Vector2f newposition = segments[i].getPosition();
        if (newposition == position)
        {
            return true;
        };
    }
    return false;
}

bool Snake::didIwin(int &numTargets)
{
    if (numTargets <= 0)
    {
        return true;
    }
    return false;
}

void Snake::move()
{
    for (size_t i = segments.size() - 1; i > 0; --i)
    {
        segments[i].setPosition(segments[i - 1].getPosition());
    }
    segments[0].move(direction);
}

void Snake::grow()
{
    sf::RectangleShape newSegment(sf::Vector2f(20, 20));
    // newSegment.setFillColor(sf::Color(255, 192, 203));
    newSegment.setFillColor(sf::Color::Red);
    newSegment.setPosition(segments.back().getPosition());
    segments.push_back(newSegment);
}

void Snake::render(sf::RenderWindow &window)
{
    for (const auto &segment : segments)
    {
        window.draw(segment);
    }
}

void Snake::renderTarget(sf::RenderWindow &window, int targetpoints[20][2], int numTargets)
{
    srand(static_cast<unsigned int>(time(0)));
    sf::RectangleShape targetSegment(sf::Vector2f(20, 20));
    targetSegment.setFillColor(sf::Color::Red);
    for (int i = 0; i < numTargets; i++)
    {
        targetSegment.setPosition(sf::Vector2f(static_cast<float>(targetpoints[i][0]), static_cast<float>(targetpoints[i][1])));
        window.draw(targetSegment);
    }
}