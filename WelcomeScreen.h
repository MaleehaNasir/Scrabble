#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H
#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>
class WelcomeScreen{

    void buttonDisplay(sf::RenderWindow &window, sf::Font &font, sf::RectangleShape buttons[2], string labels[2], bool clicked[2]);
    public:
    bool playPressed;
    bool quitPressed;

    void drawMainScreen(sf::RenderWindow& window);

};
#endif
