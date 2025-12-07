#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>
#include "Game.h"
#include "WelcomeScreen.h"
#include "GameOverScreen.h"

enum class ScreenState {MAIN_MENU, GAME, GAME_OVER};

class GameMaster
{   
    private:
    ScreenState state;
    WelcomeScreen welcome;
    Game game;
    GameOverScreen exit;
    
    public:
    GameMaster();
    void run();
};