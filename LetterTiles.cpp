#include "LetterTiles.h"
#include <cctype>

LetterTiles::LetterTiles() : letter('\0'), letter_points(0), isBlank(false) {
}

LetterTiles::LetterTiles(char l) 
{

    letter=toupper(l);
    isBlank=l==' ';
    
    switch(toupper(l)) {
        case 'A': case 'E': case 'I': case 'O': case 'U': case 'L': 
        case 'N': case 'S': case 'T': case 'R':
            letter_points = 1; break;
        case 'D': case 'G':
            letter_points = 2; break;
        case 'B': case 'C': case 'M': case 'P':
            letter_points = 3; break;
        case 'F': case 'H': case 'V': case 'W': case 'Y':
            letter_points = 4; break;
        case 'K':
            letter_points = 5; break;
        case 'J': case 'X':
            letter_points = 8; break;
        case 'Q': case 'Z':
            letter_points = 10; break;
        case ' ': // Blank tile
            letter_points = 0; break;
        default:
            letter_points = 0;
    }
}


int LetterTiles::getLetterPoints() const { return letter_points; }

char LetterTiles::getLetter() const { return letter; }

void LetterTiles::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    letterTileSprite.setPosition(x, y);
}

sf::Vector2f LetterTiles::getPosition() const { return position; }

sf::Sprite& LetterTiles::getSprite() {return letterTileSprite;}

void LetterTiles:: setSprite(const sf::Texture& texture) {letterTileSprite.setTexture(texture);}


bool LetterTiles::getIsBlank() const { return isBlank; }