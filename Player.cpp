#include "Player.h"
#include "LetterBag.h"
#include <iostream>

Player::Player() {
    score = 0;
    turn = false;
}

void Player::setScore(int s) {
    score = s;
}

int Player::getScore() {
    return score;
}

void Player::addToRack(LetterTiles* tile) {
    if (rack.size() < 7) {
        rack.push_back(tile);
    }
}

void Player::fillRack(LetterBag& bag) {
    while (rack.size() < 7) {
        LetterTiles* tile = bag.drawTile();
        if (tile == nullptr) {
            // Bag is empty
            break;
        }
        rack.push_back(tile);
    }
}

std::vector<LetterTiles*>& Player::getRack() {
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