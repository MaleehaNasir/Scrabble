#include "BoardSquares.h"
using namespace std;
#include <iostream>

BoardSquares::BoardSquares()
{
    multiplier=1;
    type=NORMAL;
    empty=true;
    position.x=0.0;
    position.y=0.0;
    colour=sf::Color::White;
}

BoardSquares::BoardSquares(int m, square_type t, bool isE, coordinates pos, sf::Color c)
{
    multiplier=m;
    type=t;
    empty=isE;
    position.x=pos.x;
    position.y=pos.y;
    colour=c;
}

bool BoardSquares::isEmpty(){return empty;}
int BoardSquares::getMultiplier(){return multiplier;}
square_type BoardSquares::getType(){return type;}
float BoardSquares::getX(){return position.x;}
float::getY(){return position.y;}
sf::Color getClr() {return colour;}