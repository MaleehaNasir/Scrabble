#ifndef LETTERBAG_H
#define LETTERBAG_H
#include "LetterTiles.h"
#include <vector>

class LetterBag {
    std::vector<LetterTiles*> tiles;
    
public:
    LetterBag();
    ~LetterBag();
    LetterTiles* drawTile();
    int tilesRemaining() const;
    void returnTile(LetterTiles* tile);
};

#endif