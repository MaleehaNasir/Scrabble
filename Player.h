#ifndef PLAYER_H
#define PLAYER_H

#include "LetterTiles.h"
#include <vector>

class LetterBag;

class Player {
    int score;
    std::vector<LetterTiles*> rack;
    bool turn;

public:
    Player();
    void setScore(int s);
    int getScore();
    void addToRack(LetterTiles* tile);
    void fillRack(LetterBag& bag);
    std::vector<LetterTiles*>& getRack();
    void removeTileFromRack(int index);
    bool isTurn() const;
    void setTurn(bool t);
};

#endif