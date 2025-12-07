#ifndef MOVE_H
#define MOVE_H

#include <SFML/Graphics.hpp>
using namespace std;

struct tilesPlaced
{
    int row;
    int col;
    char letter;
};

class Move{
    public:
    vector<tilesPlaced> tempPlacedTiles;

    
};

#endif