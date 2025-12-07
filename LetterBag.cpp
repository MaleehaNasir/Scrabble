#include "LetterBag.h"
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

LetterBag::LetterBag() {
    // Standard Scrabble distribution
    const char letters[] = {
        'A','A','A','A','A','A','A','A','A', // 9 A's
        'B','B', // 2 B's
        'C','C', // 2 C's
        'D','D','D','D', // 4 D's
        'E','E','E','E','E','E','E','E','E','E','E','E', // 12 E's
        'F','F', // 2 F's
        'G','G','G', // 3 G's
        'H','H', // 2 H's
        'I','I','I','I','I','I','I','I','I', // 9 I's
        'J', // 1 J
        'K', // 1 K
        'L','L','L','L', // 4 L's
        'M','M', // 2 M's
        'N','N','N','N','N','N', // 6 N's
        'O','O','O','O','O','O','O','O', // 8 O's
        'P','P', // 2 P's
        'Q', // 1 Q
        'R','R','R','R','R','R', // 6 R's
        'S','S','S','S', // 4 S's
        'T','T','T','T','T','T', // 6 T's
        'U','U','U','U', // 4 U's
        'V','V', // 2 V's
        'W','W', // 2 W's
        'X', // 1 X
        'Y','Y', // 2 Y's
        'Z', // 1 Z
        ' ',' ' // 2 blanks
    };
    
    for (char c : letters) 
    {tiles.push_back(new LetterTiles(c));}
    
    shuffle(tiles.begin(), tiles.end(), default_random_engine(time(0)));
}

LetterBag::~LetterBag() 
{
    for (LetterTiles* tile : tiles) 
    {delete tile;}
}

LetterTiles* LetterBag::drawTile() 
{
    if (tiles.empty()) {return nullptr;}

    LetterTiles* tile = tiles.back();
    tiles.pop_back();
    
    return tile;
}

int LetterBag::tilesRemaining() const {
    return tiles.size();
}

void LetterBag::returnTile(LetterTiles* tile) {
    tiles.push_back(tile);
}