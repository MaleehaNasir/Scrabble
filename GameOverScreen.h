#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>
class GameOverScreen{

    public:
    bool quitPressed;
    void drawExitScreen(sf::RenderWindow& window);

};
#endif