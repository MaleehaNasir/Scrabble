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
    sf::Font font;
    bool clicked[4];
    bool isDragging[7];
    sf::Vector2f dragOffset[7];
    sf::RectangleShape buttons[4];
    string labels[4]={"Submit", "Swap", "Resign", "Pass"};
    sf::Vector2f rackPositions[7];
    sf::RectangleShape boardTiles[225];
    sf::Clock timer[4];
        
    void scoreDisplay(sf::RenderWindow &window, sf::Font& font, int score1, int score2);
    void boardDisplay(sf::RenderWindow &window, sf::Font& font, vector<string> &boardDimensions, sf::RectangleShape rectangle[255]);
    void rackDisplay(sf::RenderWindow &window, sf::Font& font, vector<LetterTiles*>&rackLetters);
    void buttonDisplay(sf::RenderWindow &window, sf::Font& font, sf::RectangleShape buttons[4], string labels[4], bool clicked[4]);
    void playerDisplay(sf::RenderWindow &window, sf::Font& font, int player);
    void switchPlayer();
    void validateWord();
    void update();
    void render(sf::RenderWindow &window);
    void processEvents(sf::RenderWindow &window);
    

    public:
    Game();
    bool resignPressed=false;
    
    void drawGameScreen(sf::RenderWindow& window);
    void loadTextures();
    vector<int> getFinalScores();

    
};

#endif 
