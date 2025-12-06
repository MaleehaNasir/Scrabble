#ifndef LETTERTILES_H
#define LETTERTILES_H
#include <SFML/Graphics.hpp>

class LetterTiles {
    char letter;
    int letter_points;
    sf::Sprite letterTileSprite;
    sf::Vector2f position;
    bool isBlank; 
    
public:
    LetterTiles();
    LetterTiles(char l);
    int getLetterPoints() const;
    char getLetter() const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::Sprite& getSprite();
    void setSprite(const sf::Texture& texture);
    bool getIsBlank() const;
};

#endif