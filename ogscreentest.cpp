#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>
#include "Game.h"
#include "WelcomeScreen.h"
#include "GameOverScreen.h"

enum class ScreenState {MAIN_MENU, GAME, GAME_OVER};

int main()
{
    sf::RenderWindow window(sf::VideoMode (1050, 900), "Scrabble Scores");
    window.setFramerateLimit(60);
    ScreenState state = ScreenState::MAIN_MENU;

    WelcomeScreen welcome;
    Game game;
    GameOverScreen exit;

    while(window.isOpen())
    {
        if (state==ScreenState::MAIN_MENU)
        {
            welcome.drawMainScreen(window);

            if (welcome.playPressed) state=ScreenState::GAME;
            if (welcome.quitPressed) window.close();
        }

        else if (state==ScreenState::GAME)
        {
            game.render(window);
            if (game.resignPressed) state=ScreenState::GAME_OVER;
            else window.close();
        }
        else if (state==ScreenState::GAME_OVER)
        {
            exit.drawExitScreen(window);
            if (welcome.quitPressed) window.close();
        }
        

    }

    return 0;
}