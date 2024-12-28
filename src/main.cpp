#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "functions.h"
#include "game.h"
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    Game game;
    game.run();
    return 0;
}
