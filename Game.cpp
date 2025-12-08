#include "Game.h"
#include "SoundManager.h"
#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>
#include <set>
#include <fstream>

sf::Texture tilesKeTextures[27];
sf::Sprite rackSprites[7];

//             INITIALIZATIONS

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

int Game::getLetterValue(char letter) 
{

    LetterTiles tletter(letter);
    return tletter.getLetterPoints();
    
}

Game::Game() : Player1(), Player2(), gameBoard(), tileBag(), dictionary()
{
    loadTextures();
    dictionary.loadDictionary("dictionary.txt");

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

void Game:: switchPlayer()
{
    currentPlayer=(currentPlayer==&Player1)?&Player2 : &Player1;

    currentPlayer->getRack() = currentPlayer->getRack();
    
    for (int i = 0; i < currentPlayer->getRack().size(); i++)
    {currentPlayer->getRack()[i]->getSprite().setPosition(rackPositions[i]);}


}

bool Game::isFirstMove() 
{
    for (int i = 0; i < 15; i++) 
    {
        for (int j = 0; j < 15; j++) 
        {
            if (permanentTileSprites[i][j].getTexture() != nullptr)
            {
                return false;
            }
        }
    }
    return true; 
}

bool Game::allTilesAdjacent()
{
    if (currentMove.tempPlacedTiles.size()<=1){return true;}

    bool sameRow=true;
    int firstRow=currentMove.tempPlacedTiles[0].row;

    for (int i =0; i<currentMove.tempPlacedTiles.size();i++)
    {if (currentMove.tempPlacedTiles[i].row!=firstRow) {sameRow=false; break;}}

    bool sameCol=true;
    int firstCol=currentMove.tempPlacedTiles[0].col;

    for (int i =0; i<currentMove.tempPlacedTiles.size();i++)
    {if (currentMove.tempPlacedTiles[i].col!=firstCol) {sameCol=false; break;}}

    return sameCol||sameRow;

}

bool Game::allTilesConnected()
{
    for (int i =0; i<currentMove.tempPlacedTiles.size(); i++)
    {
        int row=currentMove.tempPlacedTiles[i].row;
        int col=currentMove.tempPlacedTiles[i].col;

        if (row > 0 && !gameBoard.isEmpty(row - 1, col)) {return true;}
       
        if (row < 14 && !gameBoard.isEmpty(row + 1, col)) {return true;}
        
        if (col > 0 && !gameBoard.isEmpty(row, col-1)) {return true;}
       
        if (col < 14 && !gameBoard.isEmpty(row, col+1)) {return true;}
    }
    
    return false;
    
}

vector<string> Game::returnFormedWords()
{
    vector<string> words;

    for (const auto& tile : currentMove.tempPlacedTiles) 
    {
        gameBoard.setLetter(tile.row, tile.col, tile.letter);
        gameBoard.setEmpty(tile.row, tile.col, false);
    }
    
    bool horizontal = true;
    
    if (currentMove.tempPlacedTiles.size() > 1) 
    {horizontal = (currentMove.tempPlacedTiles[0].row == currentMove.tempPlacedTiles[1].row);}
    
    else 
    {
        int r = currentMove.tempPlacedTiles[0].row;
        int c = currentMove.tempPlacedTiles[0].col;
        
        bool hasHorizontalNeighbor = 
            (c > 0 && !gameBoard.isEmpty(r, c - 1)) || 
            (c < 14 && !gameBoard.isEmpty(r, c + 1));
        
        horizontal = hasHorizontalNeighbor;
    }
    
    if (horizontal) 
    {
        int row = currentMove.tempPlacedTiles[0].row;
        int minCol = 15, maxCol = 0;
        
        for (const auto& tile : currentMove.tempPlacedTiles) 
        {
            minCol = min(minCol, tile.col);
            maxCol = max(maxCol, tile.col);
        }
        
        while (minCol > 0 && !gameBoard.isEmpty(row, minCol - 1)) 
        {
            minCol--;
        }
        
        while (maxCol < 14 && !gameBoard.isEmpty(row, maxCol + 1)) 
        {
            maxCol++;
        }
        
        string word = "";
        for (int col = minCol; col <= maxCol; col++) 
        {
            word += gameBoard.getLetter(row, col);
        }
        
        if (word.length() > 1) 
        {
            words.push_back(word);
        }
    } 
    else 
    {
        int col = currentMove.tempPlacedTiles[0].col;
        int minRow = 15, maxRow = 0;
        
        for (const auto& tile : currentMove.tempPlacedTiles) 
        {
            minRow = min(minRow, tile.row);
            maxRow = max(maxRow, tile.row);
        }
        
        while (minRow > 0 && !gameBoard.isEmpty(minRow - 1, col)) 
        {
            minRow--;
        }
        
        while (maxRow < 14 && !gameBoard.isEmpty(maxRow + 1, col)) 
        {
            maxRow++;
        }
        
        string word = "";
        for (int row = minRow; row <= maxRow; row++) 
        {
            word += gameBoard.getLetter(row, col);
        }
        
        if (word.length() > 1) 
        {
            words.push_back(word);
        }
    }
    
    for (const auto& tile : currentMove.tempPlacedTiles) 
    {
        gameBoard.setEmpty(tile.row, tile.col, true);
    }
    
    return words;
}

bool Game::checkInDictionary(const string& word)
{
    string capitalWord=word;
    for (int i = 0; i < capitalWord.length(); i++)
    {capitalWord[i] = toupper(capitalWord[i]);}

    return dictionary.ValidWord(capitalWord);
}


int Game::calculateScore()
{
    int totalScore = 0;
        
    vector<string> formedWords = returnFormedWords();
    
    for (int i = 0; i < formedWords.size(); i++)
    {
        string word = formedWords[i];
        int wordScore = 0;
        int wordMultiplier = 1;  
        
        
        bool horizontal = true;
        if (currentMove.tempPlacedTiles.size() > 1)
        {
            horizontal = (currentMove.tempPlacedTiles[0].row == currentMove.tempPlacedTiles[1].row);
        }
        
        int startRow, startCol;
        
        if (horizontal)
        {
            startRow = currentMove.tempPlacedTiles[0].row;
            startCol = currentMove.tempPlacedTiles[0].col;
            
            while (startCol > 0 && !gameBoard.isEmpty(startRow, startCol - 1))
            {
                startCol--;
            }
            
            for (int j = 0; j < word.length(); j++)
            {
                char letter = word[j];
                int letterValue = getLetterValue(letter);
                int letterMultiplier = 1;  
                
                int currentRow = startRow;
                int currentCol = startCol + j;
                
                bool justPlaced = false;
                for (int k = 0; k < currentMove.tempPlacedTiles.size(); k++)
                {
                    if (currentMove.tempPlacedTiles[k].row == currentRow && 
                        currentMove.tempPlacedTiles[k].col == currentCol)
                    {
                        justPlaced = true;
                        
                        square_type sqType = gameBoard.getSquareType(currentRow, currentCol);
                        
                        if (sqType == DL)
                        {
                            letterMultiplier = 2;
                        }
                        else if (sqType == TL)
                        {
                            letterMultiplier = 3;
                        }
                        else if (sqType == DW)
                        {
                            wordMultiplier *= 2;
                        }
                        else if (sqType == TW)
                        {
                            wordMultiplier *= 3;
                        }

                        break;
                    }
                }
                                
                wordScore += letterValue * letterMultiplier;
            }
        }
        else
        {
            startRow = currentMove.tempPlacedTiles[0].row;
            startCol = currentMove.tempPlacedTiles[0].col;
            
            while (startRow > 0 && !gameBoard.isEmpty(startRow - 1, startCol))
            {
                startRow--;
            }
            
            for (int j = 0; j < word.length(); j++)
            {
                char letter = word[j];
                int letterValue = getLetterValue(letter);
                int letterMultiplier = 1;
                
                int currentRow = startRow + j;
                int currentCol = startCol;
                
                bool justPlaced = false;
                for (int k = 0; k < currentMove.tempPlacedTiles.size(); k++)
                {
                    if (currentMove.tempPlacedTiles[k].row == currentRow && 
                        currentMove.tempPlacedTiles[k].col == currentCol)
                    {
                        justPlaced = true;
                        
                        square_type sqType = gameBoard.getSquareType(currentRow, currentCol);
                        
                        if (sqType == DL)
                        {
                            letterMultiplier = 2;
                        }
                        else if (sqType == TL)
                        {
                            letterMultiplier = 3;
                        }
                        else if (sqType == DW)
                        {
                            wordMultiplier *= 2;
                        }
                        else if (sqType == TW)
                        {
                            wordMultiplier *= 3;
                        }
                        
                        
                        break;
                    }
                }
                
                
                wordScore += letterValue * letterMultiplier;
            }
        }
        
        wordScore *= wordMultiplier;
        totalScore += wordScore;
    }
    
    if (currentMove.tempPlacedTiles.size() == 7)
    {
        totalScore += 50;
    }
    
    return totalScore;
}


bool Game::validateMove()
{
    if (isFirstMove())
    {
        bool tileOnCenter=false;

        for (int i =0; i<currentMove.tempPlacedTiles.size(); i++)
        {
            if (currentMove.tempPlacedTiles[i].row==7 && currentMove.tempPlacedTiles[i].col==7)
            {
                tileOnCenter=true;
                break;
            }
        }

        if (tileOnCenter==false){return false;}
    }
    else
    {
        if(allTilesConnected()==false){return false;}
    }

    if (allTilesAdjacent()==false){return false;}

    vector<string>formedWords=returnFormedWords();

    if (formedWords.empty()){return false;}

    for (int i =0; i<formedWords.size(); i++)
    {
        if (checkInDictionary(formedWords[i])==false){return false;}
    }


    return true;
}

void Game::submitMove()
{
    if (currentMove.tempPlacedTiles.empty())
    return;

    if(!validateMove()){cout<<"Invalid Move"<<endl; return;}

    int score = calculateScore();
    currentPlayer->incScore(score);

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

void Game::swapTiles()
{
    
    for (int i = 0; i < currentPlayer->getRack().size(); i++)
    {
        LetterTiles* tile = currentPlayer->getRack()[i];
        tileBag.returnTile(tile);  
    }
    
    
    currentPlayer->getRack().clear();
    
    currentPlayer->fillRack(tileBag, tilesKeTextures);
    
    for (int i = 0; i < currentPlayer->getRack().size(); i++) 
    {
        currentPlayer->getRack()[i]->getSprite().setPosition(rackPositions[i]);
    }
    
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
                                swapTiles(); 
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