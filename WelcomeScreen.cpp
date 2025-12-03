#include "WelcomeScreen.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
#include <iostream>

void WelcomeScreen ::buttonDisplay(sf::RenderWindow &window, sf::Font &font, sf::RectangleShape buttons[2], string labels[2], bool clicked[2])
{
    for (int i =0; i<2; i++)
        {

            if (clicked[i]) 
            {buttons[i].setFillColor(sf::Color(220, 220, 220));} 
            else 
            {buttons[i].setFillColor(sf::Color(255, 255, 255));}
            
            window.draw(buttons[i]);

            sf::Text text(labels[i], font, 27);
            text.setPosition(buttons[i].getPosition().x+38, buttons[i].getPosition().y+9);
            text.setFillColor(sf::Color::Black);
            window.draw(text);

            
        }
}

void WelcomeScreen :: drawMainScreen(sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("open-sauce.sans-black.ttf");
    
    sf::Text title("Welcome to Scrabble!", font, 40);
    title.setPosition(257.f, 340.f);
    title.setFillColor(sf::Color::Black);

    bool clicked[2] = {false, false};
    sf::Clock timer[2];

    string labels[4]={"Play", "Quit"};
    sf::RectangleShape buttons[2];
    int b_start_x=425;
    int b_start_y=500;
    for (int i=0; i<2; i++)
        {
            buttons[i].setSize(sf::Vector2f(150.f, 50.f));
            buttons[i].setPosition(b_start_x, b_start_y+(i*160));

        }

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type==sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                cout<<"Closed the Window"<<endl;
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (int i = 0; i < 2; ++i) 
                {
                    sf::FloatRect buttonBounds = buttons[i].getGlobalBounds();
                    if (buttonBounds.contains(mousePos)) 
                    {
                        clicked[i] = true;
                        timer[i].restart();
                        switch (i) 
                        {
                            case 0:  
                                playPressed=true;
                                return;
                                break;
                            case 1:  
                                quitPressed=true;
                                return;
                                break;
                            default:
                                return;
                                break;
                        }
                    }
                }
            }

            
        }

        for (int i = 0; i <4; ++i) 
        {
            if (clicked[i] && timer[i].getElapsedTime().asSeconds() > 0.18f) {
                clicked[i] = false;
            }
        }

        window.clear(sf::Color(165, 184, 174));

        buttonDisplay(window, font, buttons, labels, clicked);
        window.draw(title);
        
        window.display();

    }

} 