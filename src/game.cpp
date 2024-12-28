#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <string>
#include "game.h"
#include <thread>
#include <chrono>

using namespace std;

void Game::run()
{

    initialize();
    while (window.isOpen())
    {
        gamemove();
        handleInput();
        render();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void Game::initialize()
{
    window.create(sf::VideoMode(800, 600), "My window");
    cout << "initializing the game..." << endl;
    numTargets = 10;

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disX(0, 38); // Range for x-coordinates (0 to 38)
    uniform_int_distribution<> disY(0, 28);

    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < numTargets; i++)
    {
        targetpoints[i][0] = disX(gen) * 20;
        targetpoints[i][1] = disY(gen) * 20;
    }
    // render();
}

void Game::closeGame(std::string &message2)
{
    sf::Font font;
    if (!(font.loadFromFile("/Users/rasingh/Documents/Random/code/cpp/smallgame/build/Arial.ttf")))
    {
        cout << "error loading font";
        return;
    }

    sf::Text message;
    message.setFont(font);
    message.setString("Game is ending! \n" + message2);
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::Red);
    message.setPosition(200, 300);
    window.clear();
    window.draw(message);
    window.display();
    cout << "Game is ending";
    sf::sleep(sf::seconds(5));
    window.close();
}

void Game::gamemove()
{
    snake.move();
    if (snake.didIhittarget(targetpoints, numTargets))
    {
        snake.grow();
        window.clear();
        snake.render(window);
        snake.renderTarget(window, targetpoints, numTargets);
    }
    if (snake.didIhitside())
    {
        std::string message = "you hit the wall so you lose";
        cout << "you hit the wall so you lose" << endl;
        closeGame(message);
    }
    if (snake.didIcollide())
    {
        std::string message = "you tried to eat yourself so you lose";
        cout << "you tried to eat yourself so you lose" << endl;
        closeGame(message);
    }
    if (snake.didIwin(numTargets))
    {
        std::string message = "you ate all the snake cookies so you win";
        cout << "you ate all the snake cookies so you win" << endl;
        closeGame(message);
    }
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
                snake.direction = sf::Vector2f(20, 0);
                break;
            case sf::Keyboard::Left:
                snake.direction = sf::Vector2f(-20, 0);
                break;
            case sf::Keyboard::Up:
                snake.direction = sf::Vector2f(0, -20);
                break;
            case sf::Keyboard::Down:
                snake.direction = sf::Vector2f(0, 20);
                break;
            default:
                break;
            }
        }
    }
}

void Game::render()
{
    window.clear();
    snake.renderTarget(window, targetpoints, numTargets);
    snake.render(window);
    window.display();
}
