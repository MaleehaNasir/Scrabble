#include "BoardSquares.h"
using namespace std;
#include <iostream>
#include "Board.h"

Board::Board()
{
    const float start_x=10;
    const float start_y=10;

    for (int i =0; i<15; i++)
    {

        for (int j = 0; j<15;j++)
        {
            coordinates p;
            p.x=start_x+(j*44.f);
            p.y=start_y+(i*44.f);
            
            if (i==7&&j==7) //CENTER
            {grid[i][j]=BoardSquares(1, NORMAL, true, p, sf::Color(76, 98, 132));}

            //TRIPLE WORD
            else if((i==0&&(j==0||j==7||j==14))   ||   (i==7&&(j==0||j==14))   || (i==14&&(j==0||j==7||j==14)))
            {
                grid[i][j]=BoardSquares(3, TW, true, p, sf::Color(133,33,33));

            }

            //DOUBLE WORD
            else if ((i==j && ((i>=1 && i<=4)||(i>=10 && i<=14)))   ||   (i==14-j && ((i>=1 && i<=4)||(i>=10 && i<=14))))
            {
                grid[i][j]=BoardSquares(2, DW, true, p, sf::Color(182, 101, 96));
            }

            //TRIPLE LETTER
            else if (((i==5||i==9) && (j == 1 || j == 13 || j==5||j==9))   ||   ((i==1||i==13)&&(j==5||j==9)))
            {
                grid[i][j]=BoardSquares(3, TL, true, p, sf::Color(24, 45, 109));
            }

            //DOUBLE LETTER
            else if (((i==0 || i==14)&&(j==3||j==11))   ||   ((i==6||i==8)&&(j==2||j==6||j==8||j==12))   ||   ((i==3 || i==11)&&(j==0 || j == 7 || j == 14))    ||    ((i==2 || i ==12)&&(j==6 || j==8))    ||   ((i==7)&&(j==11||j==3)))
            {
                grid[i][j]=BoardSquares(2, DL, true, p, sf::Color(76, 98, 132));
            }

            else
            {grid[i][j]=BoardSquares(1, NORMAL, true, p, sf::Color(121, 139, 127));}


            lettersGrid[i][j]='\0';


    
        }

    }
}

void Board::setLetter(int row, int col, char l)
{grid[row][col].setLetter(l);}

char Board::getLetter(int row, int col) 
{return grid[row][col].getLetter();}

bool Board::isEmpty(int row, int col) const {return grid[row][col].isEmpty();}

square_type Board::getSquareType(int row, int col)
{return grid[row][col].getType();}

sf::RectangleShape Board:: getTileInfo(int row, int col)
{
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(40.f,40.f));
    square.setFillColor(grid[row][col].getClr());
    square.setPosition(grid[row][col].getX(), grid[row][col].getY());

    if (grid[row][col].isEmpty()) 
    {
        sf::Text text;
        text.setString(std::string(1, grid[row][col].getLetter()));
        text.setPosition(square.getPosition().x+10, square.getPosition().y+5);
    
    }

    return square;

}

void Board::setEmpty(int row, int col, bool e){grid[row][col].setEmpty(e);}


