#include "Game.h"
#include "SoundManager.h"
#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>

sf::Texture tilesKeTextures[27];
sf::Sprite rackSprites[7];


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

void Game:: switchPlayer()
{
    currentPlayer=(currentPlayer==&Player1)?&Player2 : &Player1;

    currentPlayer->getRack() = currentPlayer->getRack();
    
    for (int i = 0; i < currentPlayer->getRack().size(); i++)
    {currentPlayer->getRack()[i]->getSprite().setPosition(rackPositions[i]);}


}

// void Game::validateMove()
// {
//     if (isFirstMove)
//     {
//         //implement logic for first move regarding center
//     }

//     else 
//     return (allTilesAdjacent() && allTilesConnected() && returnFormedWords().size>0 && checkInDictionary)
// }

void Game::submitMove()
{
    if (currentMove.tempPlacedTiles.empty())
    return;

    for (int i =0; i<currentMove.tempPlacedTiles.size();i++)
    {
        int r = currentMove.tempPlacedTiles[i].row;
        int c = currentMove.tempPlacedTiles[i].col;
        char l = currentMove.tempPlacedTiles[i].letter;

        gameBoard.setLetter(r, c, l);
        
        int textureIndex = l - 'A';
        permanentTileSprites[r][c].setTexture(tilesKeTextures[textureIndex]);
        permanentTileSprites[r][c].setScale(0.8f, 0.8f);
        permanentTileSprites[r][c].setPosition(boardTiles[r*15 +c].getPosition());
    }

    for (int i =0; i<currentMove.tempPlacedTiles.size(); i++)
    {
        char placedletter=currentMove.tempPlacedTiles[i].letter;

        for (int j =0; j<currentPlayer->getRack().size(); j++)
        {
            if (currentPlayer->getRack()[j]->getLetter()==placedletter)
            {currentPlayer->getRack().erase(currentPlayer->getRack().begin()+j); break;}
        }
    }

    currentPlayer->fillRack(tileBag, tilesKeTextures);
    currentMove.tempPlacedTiles.clear();

    for (int i = 0; i < currentPlayer->getRack().size(); i++) 
    {currentPlayer->getRack()[i]->getSprite().setPosition(rackPositions[i]);}

    switchPlayer();

}



void Game::playerDisplay(sf::RenderWindow &window)
{

    sf::Text currPlayerLabel = sf::Text("Currently Playing: ", font, 28);
    sf::Text currPlayer("", font, 26);
    if (currentPlayer==&Player1) currPlayer.setString("Player 1");
    else currPlayer.setString("Player 2");
    

    currPlayerLabel.setFillColor(sf::Color::White);
    currPlayer.setFillColor(sf::Color::White);

    currPlayerLabel.setPosition(740,350);
    currPlayer.setPosition(780, 400);

    window.draw(currPlayerLabel);
    window.draw(currPlayer);

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

    font.loadFromFile("open-sauce.sans-black.ttf");
    for (int i =0; i<7; i++){isDragging[i] = false;}

    for (int i =0; i<4; i++){clicked[i] = false;};

    for (int i =0; i<15;i++)
    {
        for (int j =0; j<15;j++)
        {permanentTileSprites[i][j]=sf::Sprite();}
    }

    int b_start_x=20;
    int b_start_y=780;
    for (int i=0; i<4; i++)
    {
        buttons[i].setSize(sf::Vector2f(120.f, 40.f));
        buttons[i].setPosition(b_start_x+(i*150), b_start_y);

    }

    for (int i = 0; i < 15; i++) 
    {
        for (int j = 0; j < 15; j++) 
        {boardTiles[i*15 + j] = gameBoard.getTileInfo(i, j);}
    }


    float r_start_x = 10;
    float r_start_y = 690;
    for (int i = 0; i < currentPlayer->getRack().size(); i++)
    {
        rackPositions[i] = sf::Vector2f(r_start_x + i*45, r_start_y);
        currentPlayer->getRack()[i]->getSprite().setPosition(rackPositions[i]);  // Set initial position
    }
}

vector<int> Game::getFinalScores() //to pass to gameover screen so that players can stay private otherwise 
{
    vector<int> scores;
    scores.push_back(Player1.getScore());
    scores.push_back(Player2.getScore());
    return scores;
}

void Game::buttonDisplay(sf::RenderWindow &window)
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

void Game:: scoreDisplay(sf::RenderWindow &window)
{
    sf::Text player1 = sf::Text("Player 1: ", font, 24);
    sf::Text score1_display = sf::Text(to_string(Player1.getScore()), font, 24);
    sf::Text player2 = sf::Text("Player 2: ", font, 24);
    sf::Text score2_display = sf::Text(to_string(Player2.getScore()), font, 24);
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

void Game:: rackDisplay(sf::RenderWindow &window)
{

    for (int i=0; i<currentPlayer->getRack().size(); i++)
    {
        sf::Sprite& s = currentPlayer->getRack()[i]->getSprite();
        window.draw(s);
    }
}

void Game::processEvents(sf::RenderWindow &window)
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
                
                for (int i=0; i<currentPlayer->getRack().size();i++)
                {
                    sf::FloatRect rackLetterBounds = currentPlayer->getRack()[i]->getSprite().getGlobalBounds();
                    if (rackLetterBounds.contains(mousePos)) 
                    {
                        sf::Vector2f tilePos = currentPlayer->getRack()[i]->getSprite().getPosition();
                        SoundManager::get().playSound("tile_pickup",90.f);
                        isDragging[i]=true;
                        dragOffset[i]=  mousePos-currentPlayer->getRack()[i]->getSprite().getPosition();

                        for (int a = 0; a < 225; a++)
                        {
                            int row = a / 15;
                            int col = a % 15;

                            sf::Vector2f boardTilePos = boardTiles[a].getPosition();
                            
                            if (tilePos==boardTilePos)
                            {
                                for (auto it = currentMove.tempPlacedTiles.begin(); it != currentMove.tempPlacedTiles.end(); ++it)
                                {
                                    if (it->row == row && it->col == col)
                                    {
                                        currentMove.tempPlacedTiles.erase(it);
                                        gameBoard.setEmpty(row, col, true); // Mark board position as empty
                                        break;
                                    }
                                }
                                break; 
                            }

                        }
                
                
                        
                    }

                }

                for (int i = 0; i < 4; ++i) 
                {
                    sf::FloatRect buttonBounds = buttons[i].getGlobalBounds();
                    if (buttonBounds.contains(mousePos)) 
                    {
                        SoundManager::get().playSound("click",100.f);
                        clicked[i] = true;
                        timer[i].restart();
                        switch (i) 
                        {
                            case 0:  //submit
                                submitMove();
                                SoundManager::get().playSound("submit_ok", 85.f);
                                break;
                            case 1: //swap
                                //swaptilesfunction implement karo 
                                SoundManager::get().playSound("swap",80.f);
                                break;
                            
                            case 2:  // Resign
                                SoundManager::get().playSound("resign",100.f);
                                resignPressed=true;
                                return;
                                break;

                            case 3:
                                SoundManager::get().playSound("pass",90.f);
                                switchPlayer();
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
                    for (int i=0; i<currentPlayer->getRack().size(); i++)
                    {   
                        if (isDragging[i])
                        {
                            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                            bool placed = false;

                            for (int a=0; a<225;a++)
                            {
                                int row = a / 15;  
                                int col = a % 15;

                                sf::FloatRect boardTileBounds = boardTiles[a].getGlobalBounds();
                                if (boardTileBounds.contains(mousePos)&& gameBoard.isEmpty(row, col)) 
                                {
                                    currentPlayer->getRack()[i]->getSprite().setPosition(boardTiles[a].getPosition()); 
                                    gameBoard.setEmpty(row, col, false);
                                    tilesPlaced tempTile;
                                    tempTile.row=row;
                                    tempTile.col=col;
                                    tempTile.letter=currentPlayer->getRack()[i]->getLetter();
                                    currentMove.tempPlacedTiles.push_back(tempTile);
                                    placed=true;
                                    SoundManager::get().playSound("tile_place",95.f);

                                    break;
                                }
                            }

                            if (!placed){currentPlayer->getRack()[i]->getSprite().setPosition(rackPositions[i]);}
                        }
                        isDragging[i] = false;
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                for (int i =0; i<currentPlayer->getRack().size();i++)
                {
                    if (isDragging[i])
                    {
                        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                        currentPlayer->getRack()[i]->getSprite().setPosition(mousePos - dragOffset[i]); 
                    }
                }
            }

            
        }

            
}

void Game::update()
{
    for (int i = 0; i <4; ++i) 
        {
            if (clicked[i] && timer[i].getElapsedTime().asSeconds() > 0.18f) {
                clicked[i] = false;
            }
        }
}

void Game::render(sf::RenderWindow &window)
{
    window.clear(sf::Color(165, 184, 174));
        
        for (int i =0; i<15;i++)
        {
            for (int j =0; j<15;j++)
            {
                sf::RectangleShape tile = gameBoard.getTileInfo(i, j);
                window.draw(tile);

                if (!gameBoard.isEmpty(i, j))  
                {window.draw(permanentTileSprites[i][j]);}
            }
        }

        
        scoreDisplay(window);
        rackDisplay(window);
        buttonDisplay(window);
        playerDisplay(window);

        
        window.display();
}

void Game::drawGameScreen(sf::RenderWindow &window)
{

    while(window.isOpen())
    {
        processEvents(window);
        if (resignPressed){return;}
        update();      
        render(window);
        SoundManager::get().update();
        
    }        
}