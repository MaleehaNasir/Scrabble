    #include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Drag and Drop Rectangle");
    window.setFramerateLimit(60); //

    // Create the rectangle shape
    sf::RectangleShape rectangle({120.f, 80.f});
    rectangle.setFillColor(sf::Color::Cyan); //
    rectangle.setPosition(340.f, 260.f); // Initial position
    
    bool isDragging = false;
    // Offset from the rectangle's top-left to the mouse position when clicked
    sf::Vector2f dragOffset;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle mouse button pressed event
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Get current mouse position in window coordinates
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    
                    // Check if the mouse click is within the bounds of the rectangle
                    if (rectangle.getGlobalBounds().contains(mousePos))
                    {
                        isDragging = true;
                        // Calculate the offset between the mouse position and the rectangle's top-left corner
                        dragOffset = mousePos - rectangle.getPosition();
                    }
                }
            }

            // Handle mouse button released event
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    isDragging = false;
                }
            }

            // Handle mouse moved event
            if (event.type == sf::Event::MouseMoved)
            {
                if (isDragging)
                {
                    // Get current mouse position
                    sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                    // Set the rectangle's position based on the mouse position minus the original offset
                    rectangle.setPosition(mousePos - dragOffset); //
                }
            }
        }

        // Drawing
        window.clear(sf::Color::Black); // Clear the window with black color
        window.draw(rectangle); // Draw the rectangle
        window.display(); // Display the buffer to the window
    }

    return 0;
}
