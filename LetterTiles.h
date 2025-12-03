class LetterTiles
{
    char letter;
    int letter_points;
    sf::RectangleShape tileRect(sf::Vector2f(120.f, 40.f));

    public:
    int getLetterPoints();
    char getLetter();
    void drawLetterTile();
}