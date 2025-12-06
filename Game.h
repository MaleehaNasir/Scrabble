#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Board.h"
#include "LetterBag.h"    
#include "Player.h" 

using namespace std;

// struct Tile{
// }

class Game 
{
    LetterBag letterBag;
    Player player1;
    Player player2;
    Player* currentPlayer;
    Board gameBoard;
    
    void scoreDisplay(sf::RenderWindow &window, sf::Font font, int score1, int score2);
    void boardDisplay(sf::RenderWindow &window, sf::Font font, vector<string> &boardDimensions, sf::RectangleShape rectangle[255]);
    void rackDisplay(sf::RenderWindow &window, sf::Font font, vector<LetterTiles*>&rackLetters, sf::RectangleShape rectangle[7]);
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