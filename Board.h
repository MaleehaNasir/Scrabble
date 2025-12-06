#include "BoardSquares.h"
using namespace std;
#include <iostream>

class Board{

    BoardSquares grid[15][15];

    public:
    Board();
    string getTypeText(BoardSquares &square);
    sf::RectangleShape getTileInfo(int row, int col);
    void setLetter(int row, int col, char l);
    char getLetter(int row, int col);
    bool isEmpty(int row, int col) const; 

    
    

};

