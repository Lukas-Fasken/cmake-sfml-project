#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "test.hpp"


void test(sf::RenderWindow* window, sf::Font* font){
    std::string printed_string;
    sf::Text printed_text(*font);
    while (window->isOpen()){
        while (const std::optional event = window->pollEvent()){
            if (event->is<sf::Event::Closed>())
            {
                window->close();
            }else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window->close();
                }
            }else if (const auto *TextEntered = event->getIf<sf::Event::TextEntered>())
            {
                printed_string = printed_string += TextEntered->unicode;
            }

        }
        printed_text.setString(printed_string);
        printed_text.setFillColor(sf::Color::White);

        window->clear();
        window->draw(printed_text);
        window->display();
    }
}