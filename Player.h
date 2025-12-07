#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "LetterTiles.h"
#include "LetterBag.h"
#include <vector>
using namespace std;

class Player {
private:
    int score;
    vector<LetterTiles*> rack;   
    bool turn;

public:
    Player();
    ~Player();
    void incScore(int s);
    int getScore();

    void addToRack(LetterTiles* tile, sf::Texture tilesKeTextures[]);
    void fillRack(LetterBag& bag, sf::Texture tilesKeTextures[]);

    std::vector<LetterTiles*>& getRack();

    void removeTileFromRack(int index);

    bool isTurn() const;
    void setTurn(bool t);
};

#endif
