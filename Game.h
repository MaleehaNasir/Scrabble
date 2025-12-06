#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Board.h"
#include "Player.h"
#include "LetterBag.h"

using namespace std;

// struct Tile{
// }

class Game 
{
    LetterBag tileBag;
    Board gameBoard;
    Player Player1;
    Player Player2;
    Player* currentPlayer;
    void scoreDisplay(sf::RenderWindow &window, sf::Font font, int score1, int score2);
    void boardDisplay(sf::RenderWindow &window, sf::Font font, vector<string> &boardDimensions, sf::RectangleShape rectangle[255]);
    void rackDisplay(sf::RenderWindow &window, sf::Font font, vector<char>&rackLetters, sf::RectangleShape rectangle[7]);
    void buttonDisplay(sf::RenderWindow &window, sf::Font font, sf::RectangleShape buttons[4], string labels[4], bool clicked[4]);
    void drawGameBoard(sf::RenderWindow &window);
    void move();
    void validateWord();
    

    public:
    Game();
    void render(sf::RenderWindow& window);
    bool resignPressed=false;
    
};

#endif 
