#include "GameMaster.h"
#include "SoundManager.h"



GameMaster::GameMaster()
{
    state = ScreenState::MAIN_MENU;

    auto& sm= SoundManager::get();

    sm.loadSound("click", "sound/click.ogg");
    sm.loadSound("tile_place",  "sound/tile_place.ogg");
    sm.loadSound("tile_pickup",  "sound/tile_place.ogg");
    sm.loadSound("submit_ok",   "sound/submit_ok.ogg");
    sm.loadSound("invalid",     "sound/invalid.ogg");
    sm.loadSound("swap",        "sound/swap.ogg");
    sm.loadSound("pass",        "sound/pass.ogg");
    sm.loadSound("resign",      "sound/resign.ogg");
    sm.loadSound("game_over",   "sound/game_over.ogg");

    //background music
    sm.playMusic("sound/background.ogg", true, 40.f);
}

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