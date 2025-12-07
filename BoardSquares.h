#ifndef BOARDSQUARES_H
#define BOARDSQUARES_H
#include <SFML/Graphics.hpp>


enum square_type {NORMAL, DL, TL, DW, TW};
struct coordinates
{
    float x;
    float y;
};

class BoardSquares{

    int multiplier;
    square_type type;
    bool empty;
    coordinates position;
    sf::Color colour;
    char letter;

    public:
    BoardSquares();
    BoardSquares(int m, square_type t, bool isE, coordinates pos, sf::Color c);
    bool isEmpty() const;
    void setEmpty(bool e);
    int getMultiplier();
    square_type getType();
    float getX();
    float getY();
    sf::Color getClr();
    char getLetter();
    void setLetter(char l);
    
};

#endif
