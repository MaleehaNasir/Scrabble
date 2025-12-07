#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Board.h"
#include "Player.h"
#include "LetterBag.h"

using namespace std;

class Game 
{
    LetterBag tileBag;
    Board gameBoard;
    Player Player1;
    Player Player2;
    Player* currentPlayer;
    void scoreDisplay(sf::RenderWindow &window, sf::Font font, int score1, int score2);
    void boardDisplay(sf::RenderWindow &window, sf::Font font, vector<string> &boardDimensions, sf::RectangleShape rectangle[255]);
    void rackDisplay(sf::RenderWindow &window, sf::Font font, vector<LetterTiles*>&rackLetters);
    void buttonDisplay(sf::RenderWindow &window, sf::Font font, sf::RectangleShape buttons[4], string labels[4], bool clicked[4]);
    void move();
    void validateWord();
    

    public:
    Game();
    bool resignPressed=false;
    
    void drawGameScreen(sf::RenderWindow& window);
    void loadTextures();
    vector<int> getFinalScores();
    
};

#endif 
