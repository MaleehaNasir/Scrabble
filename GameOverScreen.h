#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>
class GameOverScreen{

    public:
    bool quitPressed=false;
    //call on events from main
    void handleevent(const sf::Event& event,const sf::RenderWindow& window);
    void drawExitScreen(sf::RenderWindow& window, int score1, int score2);

    private:
    bool initial=false;
    sf::Font font;
    sf::Text tile;
    sf::Text p1ScoreText;
    sf::Text p2ScoreText;
    sf::Text resultText;

    sf::RectangleShape quitButton;
    sf::Text quitText;    
    bool buttonClicked = false;
    sf::Clock clickTimer;
    void init();
    void centerTextHoriz(sf::Text& text, float xcenter);
    


};
#endif