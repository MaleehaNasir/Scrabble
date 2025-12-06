#include "Game.h"
#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>

Game::Game(): gameBoard() {}

void Game::render(sf::RenderWindow& window)
{drawGameBoard(window);}

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

// Game:: boardDisplay(sf::RenderWindow &window, sf::Font font, vector<string> &boardDimensions, sf::RectangleShape rectangle[255])
// {

//     for(int i=0; i<225; i++)
//     {
        
//         window.draw(rectangle[i]);

//         sf::Text text(boardDimensions[i], font, 18);
//         text.setPosition(rectangle[i].getPosition().x+3, rectangle[i].getPosition().y+7);
//         text.setFillColor(sf::Color::Black);
//         window.draw(text);
        
//     }
// }

void Game:: rackDisplay(sf::RenderWindow &window, sf::Font font, vector<char>&rackLetters, sf::RectangleShape rectangle[7])
{
    

    for (int i=0; i<7; i++)
        {
            window.draw(rectangle[i]);

            sf::Text text(rackLetters[i], font, 18);
            text.setPosition(rectangle[i].getPosition().x+10, rectangle[i].getPosition().y+7);
            text.setFillColor(sf::Color::Black);
            window.draw(text);
        }
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

void Game::drawGameBoard(sf::RenderWindow &window)
{

    sf::Font font;
    font.loadFromFile("open-sauce.sans-black.ttf");
    bool isDragging[7] = {false,false,false,false,false,false,false};

    sf::Vector2f dragOffset[7];

    vector<string> boardDims(225);
    for (int i = 0; i<225; i++)
    {boardDims[i]=to_string(i);}


    vector<char>rackLets={'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    
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

    sf::RectangleShape rectangle[7];
    vector<int> ogPositionsx;
    vector<int> ogPositionsy;
    int r_start_x=10;
    int r_start_y=660;
    for (int i =0; i<7;i++)
    {
        rectangle[i].setSize(sf::Vector2f(40.f, 40.f));
        rectangle[i].setPosition(r_start_x+(i*45), r_start_y+45);
        ogPositionsx.push_back(r_start_x+(i*45));
        ogPositionsy.push_back(r_start_y+45);

    }

    sf::RectangleShape boardTiles[225];
    for (int i = 0; i < 15; i++) 
    {
        for (int j = 0; j < 15; j++) 
        {boardTiles[i*15 + j] = gameBoard.getTileInfo(i, j);}
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
                
                for (int i=0; i<7;i++)
                {
                    sf::FloatRect rackLetterBounds = rectangle[i].getGlobalBounds();
                    if (rackLetterBounds.contains(mousePos)) //TODO: add the and if empty 
                    {
                        isDragging[i]=true;
                        dragOffset[i]=  mousePos-rectangle[i].getPosition();
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
                    for (int i=0; i<7; i++)
                    {   
                        if (isDragging[i])
                        {
                            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                            for (int a=0; a<225;a++)
                            {
                                sf::FloatRect boardTileBounds = boardTiles[a].getGlobalBounds();
                                if (boardTileBounds.contains(mousePos)) 
                                {
                                    rectangle[i].setPosition(boardTiles[a].getPosition()); 
                                    int row = a / 15;  
                                    int col = a % 15;
                                    gameBoard.setLetter(row, col, rackLets[i]);
                                    break;
                                }
                                else 
                                {rectangle[i].setPosition(ogPositionsx[i], ogPositionsy[i]);}
                            }
                        }
                        isDragging[i] = false;
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                for (int i =0; i<7;i++)
                {
                    if (isDragging[i])
                    {
                        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                        rectangle[i].setPosition(mousePos - dragOffset[i]); 
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

                if (!gameBoard.isEmpty(i, j)) 
                {
                sf::Text letterText;
                letterText.setFont(font);   // font loaded earlier
                letterText.setString(std::string(1, gameBoard.getLetter(i, j)));
                letterText.setCharacterSize(24);
                letterText.setFillColor(sf::Color::Black);
                letterText.setPosition(tile.getPosition().x + 10, tile.getPosition().y + 5);
                window.draw(letterText);
                }
            }
        }
        scoreDisplay(window, font, 34, 68);
        // boardDisplay(window, font, boardDims, boardTiles);
        rackDisplay(window, font, rackLets, rectangle);
        buttonDisplay(window, font, buttons, labels, clicked);

        
        window.display();

    }
}