#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include <thread>
#include <chrono>

using namespace std;

void Game::run()
{

    initialize();
    while (window.isOpen())
    {
        b += 5;
        handleInput();
        render();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void Game::initialize()
{
    a = 0;
    b = 0;
    ta = 50;
    tb = 50;
    state = 0;
    rx = 10;
    ry = 10;
    window.create(sf::VideoMode(800, 600), "My window");
    cout << "initializing the game....a - b are set to : " << a << " - " << b << endl;
    render();
}

void Game::handleInput()
{

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Right:
                a += 5;
                break;
            case sf::Keyboard::Left:
                a -= 5;
                break;
            case sf::Keyboard::Up:
                b -= 5;
                break;
            case sf::Keyboard::Down:
                b += 5;
                break;
            default:
                break;
            }
        }
    }
    cout << "a is : " << a << endl;
    cout << "ta is : " << ta << endl;
    cout << "b is : " << b << endl;
    cout << "tb is : " << tb << endl;
    if (a == ta && b == tb)
    {
        update();
    }

    if (a == 790 || b == 590)
    {
        closeGame();
    }
    cout << "handling the input. your a - b is: " << a << " - " << b << endl;
}

void Game::closeGame()
{
    cout << "Game is ending";
    window.close();
}

void Game::update()
{
    rx += 10;
    a += 5;
    cout << "updating the game state" << endl;
}

void Game::render()
{
    // window.clear(sf::Color::Green);
    cout << "rendering the new state : " << state << endl;
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    window.clear();

    sf::RectangleShape rectangle(sf::Vector2f(rx, ry));
    // sf::CircleShape dot(10);
    rectangle.setPosition(a, b);
    rectangle.setFillColor(sf::Color::Red);
    window.draw(rectangle);

    // sf::CircleShape dot2(10);
    sf::RectangleShape rectangle2(sf::Vector2f(10, 10));
    rectangle2.setPosition(ta, tb);
    rectangle2.setFillColor(sf::Color::Blue);
    window.draw(rectangle2);

    window.display();
}