#include "GameOverScreen.h"
#include <SFML/Graphics.hpp>
#include "SoundManager.h"
#include <string>
using namespace std;
#include <iostream>
//NEEDS MASSIVE FIXINGGGG


void GameOverScreen :: drawExitScreen(sf::RenderWindow& window, int score1, int score2)
{
    sf::Font font;
    if (!font.loadFromFile("open-sauce.sans-black.ttf")){
        cerr<<"Error loading font!"<<endl;
        return;
    }
    
    sf::Text title("Game Over", font, 40);
    title.setPosition(280.f, 240.f);
    title.setFillColor(sf::Color::Black);

    sf::Text p1("Player 1:  "+ to_string(score1), font,28);
    p1.setPosition(300.f,320.f);
    p1.setFillColor(sf::Color::Black);

    sf::Text p2("Player 2:  "+ to_string(score2), font,28);
    p2.setPosition(300.f,360.f);
    p2.setFillColor(sf::Color::Black);

    string result= 
        (score1>score2)?"Winner: Player 1": 
        (score2>score1)?"Winner: Player 2": "Tie!";

    sf::Text res(result, font, 32);
    res.setPosition(300.f, 420.f);
    res.setFillColor(sf::Color(20, 120, 20));


    sf::RectangleShape button(sf::Vector2f(150.f, 50.f));
    button.setPosition(425.f,500.f);
    button.setFillColor(sf::Color(200,200,200));

    sf::Text buttonText("Quit", font, 24);
    buttonText.setPosition(455.f,510.f);
    buttonText.setFillColor(sf::Color::Black);

    bool clicked = false;
    sf::Clock timer;

    // button.setSize(sf::Vector2f(150.f, 50.f));
    // button.setPosition(b_start_x, b_start_y+(i*160));


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
                sf::FloatRect buttonBounds = button.getGlobalBounds();
                if (buttonBounds.contains(mousePos)) 
                {
                    clicked = true;
                    timer.restart();   
                    SoundManager::get().playSound("click"); 
                    quitPressed=true;
                }

            }
                
        }

    if (clicked && timer.getElapsedTime().asSeconds() > 0.18f) 
    {
        clicked = false;
    }
        

        window.clear(sf::Color(165, 184, 174));
        window.draw(title);

        if (clicked) {button.setFillColor(sf::Color(220, 220, 220));} 
        else {button.setFillColor(sf::Color(255, 255, 255));}

        window.draw(p1);
        window.draw(p2);
        window.draw(res);
        window.draw(button);
        window.draw(buttonText);
        
        window.display();
        SoundManager::get().update();

        if(quitPressed){
            return;
        }

    }

}