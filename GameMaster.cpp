#include "GameMaster.h"

GameMaster::GameMaster()
{state = ScreenState::MAIN_MENU;}

void GameMaster::run()
{
    sf::RenderWindow window(sf::VideoMode (1050, 900), "Scrabble Scores");
    window.setFramerateLimit(60);

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
            game.drawGameScreen(window);
            if (game.resignPressed) state=ScreenState::GAME_OVER;
            else window.close();
        }
        else if (state==ScreenState::GAME_OVER)
        {
            exit.drawExitScreen(window, game.getFinalScores()[0], game.getFinalScores()[1]);
            if (exit.quitPressed) window.close();
        }
        

    }
}