#include "Player.h"
#include "LetterBag.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Player::Player() {
    score = 0;
    turn = false;
}

Player::~Player() {
    for (LetterTiles* tile : rack) {
        delete tile;  
    }
    rack.clear();
}

void Player::incScore(int s) {
    score += s;
}

int Player::getScore() {
    return score;
}

void Player::addToRack(LetterTiles* tile, sf::Texture tilesKeTextures[]) 
{
    int index;
    if (rack.size() < 7) 
    {
        char c = tile->getLetter();
        if (c == ' '){index = 26;}
        else {index = c-'A';}
        tile->setSprite(tilesKeTextures[index]);
        tile->getSprite().setScale(0.8f, 0.8f);
        rack.push_back(tile);
    }

}

void Player::fillRack(LetterBag& bag, sf::Texture tilesKeTextures[]) 
{
    while (rack.size() < 7) 
    {
        LetterTiles* tile = bag.drawTile();
        if (tile == nullptr) 
        {break;}

        char letter = tile->getLetter();
        int index = letter-'A';
        if (!(index>=0 && index<26)){index=26;}
        tile->setSprite(tilesKeTextures[index]);
        tile->getSprite().setScale(0.8f, 0.8f);
        rack.push_back(tile);
    }
}

vector<LetterTiles*>& Player::getRack() {
    return rack;
}

void Player::removeTileFromRack(int index) {
    if (index >= 0 && index < rack.size()) {
        rack.erase(rack.begin() + index);
    }
}

bool Player::isTurn() const {
    return turn;
}

void Player::setTurn(bool t) {
    turn = t;
}