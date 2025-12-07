#include "Game.h"
#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>

sf::Texture tilesKeTextures[27];
sf::Sprite rackSprites[7];
sf::Vector2f rackPositions[7];

void Game::loadTextures()//load all the textures for the sprites
{
    for (char c = 'A'; c<='Z'; c++)
    {
        string filename="letterTiles/"; 
        filename+= c;
        filename+= ".png";
        tilesKeTextures[c-'A'].loadFromFile(filename);        
    }
    
    tilesKeTextures[26].loadFromFile("letterTiles/Blank.png");
}

Game::Game() : Player1(), Player2(), gameBoard(), tileBag()
{
    loadTextures();

    Player1.fillRack(tileBag, tilesKeTextures);
    Player2.fillRack(tileBag, tilesKeTextures);
    currentPlayer=&Player1;

    Player1.setTurn(true);
    Player2.setTurn(false);
    
    resignPressed=false;


}

vector<int> Game::getFinalScores() //to pass to gameover screen so that players can stay private otherwise 
{
    vector<int> scores;
    scores.push_back(Player1.getScore());
    scores.push_back(Player2.getScore());
    return scores;
}

void Game::buttonDisplay(sf::RenderWindow &window, sf::Font font, sf::RectangleShape buttons[4], string labels[4], bool clicked[4])
{
       
    for (int i =0; i<4; i++)
        {

            if (clicked[i]) 
            {buttons[i].setFillColor(sf::Color(220, 220, 220));} 
            else 
            {buttons[i].setFillColor(sf::Color(255, 255, 255));}
            
            window.draw(buttons[i]);

            sf::Text text(labels[i], font, 18);
            text.setPosition(buttons[i].getPosition().x+26, buttons[i].getPosition().y+9);
            text.setFillColor(sf::Color::Black);
            window.draw(text);

            
        }
}

void Game:: scoreDisplay(sf::RenderWindow &window, sf::Font font, int score1, int score2)
{
    sf::Text player1 = sf::Text("Player 1: ", font, 24);
    sf::Text score1_display = sf::Text(to_string(score1), font, 24);
    sf::Text player2 = sf::Text("Player 2: ", font, 24);
    sf::Text score2_display = sf::Text(to_string(score2), font, 24);
    sf::Text label = sf::Text("PLAYER SCORES", font, 30);

    score1_display.setFillColor(sf::Color::White);
    score2_display.setFillColor(sf::Color::White);
    player1.setFillColor(sf::Color::White);
    player2.setFillColor(sf::Color::White);
    label.setFillColor(sf::Color::White);

    label.setPosition(740,150);
    player1.setPosition(780, 200);
    player2.setPosition(780, 250);
    score1_display.setPosition(900, 200);
    score2_display.setPosition(900, 250);

    window.draw(player1);
    window.draw(player2);
    window.draw(score1_display);
    window.draw(score2_display);
    window.draw(label);

}

void Game:: rackDisplay(sf::RenderWindow &window, sf::Font font, vector<LetterTiles*>&rackLetters)
{

    for (int i=0; i<rackLetters.size(); i++)
    {
        sf::Sprite& s = rackLetters[i]->getSprite();
        window.draw(s);
    }
}

void Game::drawGameScreen(sf::RenderWindow &window)
{

    sf::Font font;
    font.loadFromFile("open-sauce.sans-black.ttf");
    bool isDragging[7] = {false,false,false,false,false,false,false};

    sf::Vector2f dragOffset[7];

    vector<LetterTiles*>& currentRack= currentPlayer->getRack();

    vector<string> boardDims(225);
    for (int i = 0; i<225; i++)
    {boardDims[i]=to_string(i);}
    
    bool clicked[4] = {false, false, false, false};
    sf::Clock timer[4];

    string labels[4]={"Submit", "Swap", "Resign", "Pass"};
    sf::RectangleShape buttons[4];
    int b_start_x=20;
    int b_start_y=780;
    for (int i=0; i<4; i++)
    {
        buttons[i].setSize(sf::Vector2f(120.f, 40.f));
        buttons[i].setPosition(b_start_x+(i*150), b_start_y);

    }

    sf::RectangleShape boardTiles[225];
    for (int i = 0; i < 15; i++) 
    {
        for (int j = 0; j < 15; j++) 
        {boardTiles[i*15 + j] = gameBoard.getTileInfo(i, j);}
    }


    float r_start_x = 10;
    float r_start_y = 690;
    for (int i = 0; i < currentRack.size(); i++)
    {
        rackPositions[i] = sf::Vector2f(r_start_x + i*45, r_start_y);
        currentRack[i]->getSprite().setPosition(rackPositions[i]);  // Set initial position
    }

    
    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type==sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                cout<<"Closed the Window"<<endl;
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                
                for (int i=0; i<currentRack.size();i++)
                {
                    sf::FloatRect rackLetterBounds = currentRack[i]->getSprite().getGlobalBounds();
                    if (rackLetterBounds.contains(mousePos)) //TODO: add the and if empty 
                    {
                        isDragging[i]=true;
                        dragOffset[i]=  mousePos-currentRack[i]->getSprite().getPosition();
                    }

                }

                for (int i = 0; i < 4; ++i) 
                {
                    sf::FloatRect buttonBounds = buttons[i].getGlobalBounds();
                    if (buttonBounds.contains(mousePos)) 
                    {
                        clicked[i] = true;
                        timer[i].restart();
                        std::cout << labels[i] << " clicked! TODO: Add game." << labels[i] << "();" << std::endl;
                        switch (i) 
                        {
                            // case 0:  
                            //     // game.Swap();  // Or whatever your method is
                            //     break;
                            // case 1:  // Pass
                            //     // game.Pass();
                            //     break;
                            case 2:  // Resign
                                resignPressed=true;
                                return;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (int i=0; i<currentRack.size(); i++)
                    {   
                        if (isDragging[i])
                        {
                            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                            for (int a=0; a<225;a++)
                            {
                                int row = a / 15;  
                                int col = a % 15;

                                sf::FloatRect boardTileBounds = boardTiles[a].getGlobalBounds();
                                if (boardTileBounds.contains(mousePos)&& gameBoard.isEmpty(row, col)) 
                                {
                                    currentRack[i]->getSprite().setPosition(boardTiles[a].getPosition()); 
                                    gameBoard.setEmpty(row, col, false);
                                    break;
                                }
                                else 
                                {currentRack[i]->getSprite().setPosition(rackPositions[i]); gameBoard.setEmpty(row, col, true);}
                            }
                        }
                        isDragging[i] = false;
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                for (int i =0; i<currentRack.size();i++)
                {
                    if (isDragging[i])
                    {
                        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                        currentRack[i]->getSprite().setPosition(mousePos - dragOffset[i]); 
                    }
                }
            }

            
        }

        for (int i = 0; i <4; ++i) 
        {
            if (clicked[i] && timer[i].getElapsedTime().asSeconds() > 0.18f) {
                clicked[i] = false;
            }
        }

        window.clear(sf::Color(165, 184, 174));
        
        for (int i =0; i<15;i++)
        {
            for (int j =0; j<15;j++)
            {
                sf::RectangleShape tile = gameBoard.getTileInfo(i, j);
                window.draw(tile);

                // if (!gameBoard.isEmpty(i, j)) 
                // {
                // sf::Text letterText;
                // letterText.setFont(font);   // font loaded earlier
                // letterText.setString(std::string(1, gameBoard.getLetter(i, j)));
                // letterText.setCharacterSize(24);
                // letterText.setFillColor(sf::Color::Black);
                // letterText.setPosition(tile.getPosition().x + 10, tile.getPosition().y + 5);
                // window.draw(letterText);
                // }
            }
        }
        scoreDisplay(window, font, Player1.getScore(), Player2.getScore());
        rackDisplay(window, font, currentRack);
        buttonDisplay(window, font, buttons, labels, clicked);

        
        window.display();

    }
}