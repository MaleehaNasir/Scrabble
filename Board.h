#include "BoardSquares.h"
using namespace std;
#include <iostream>

class Board{

    BoardSquares grid[15][15];
    char lettersGrid[15][15];


    public:
    Board();
    sf::RectangleShape getTileInfo(int row, int col);
    void setLetter(int row, int col, char l);
    char getLetter(int row, int col);
    bool isEmpty(int row, int col) const;
    void setEmpty(int row, int col, bool e); 
    square_type getSquareType(int row, int col);
    
    
    

};

