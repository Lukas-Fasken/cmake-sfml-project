#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "test.hpp"
#include "gaussian_mouse.hpp"
#include "utils.hpp"
#include "game_menu.hpp"

// unsigned int window_size[] = {1920u, 1080u};
unsigned int window_size[] = {1000u, 1000u};
unsigned int char_size = 30;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({window_size[0], window_size[1]}), "WASD");
    window.setFramerateLimit(144);

    // testing variables
    sf::Font font("C:/Windows/Fonts/arial.ttf");
    std::string printed_string;
    sf::Text printed_text(font);

    // setup of menu
    std::string elements[] = {"Games", "nothing", "Test", "Exit"};
    int elements_length = sizeof(elements) / sizeof(elements[0]);
    std::tuple<std::vector<sf::RectangleShape>, std::vector<sf::Text>> main_menu=menu_template(elements, elements_length, window_size, &font, char_size);
    std::vector<sf::RectangleShape> choices= std::get<0>(main_menu);
    std::vector<sf::Text> element_texts=std::get<1>(main_menu);

    // //mouse vairables
    int mouse_menu=elements_length;

    while (window.isOpen())
    {
        // mouse position
        sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        for (int i = 0; i < sizeof(elements) / sizeof(elements[0]); i++)
        {
            if (choices[i].getGlobalBounds().contains(mouse_pos))
            {
                choices[i].setOutlineColor(sf::Color::Red);
                mouse_menu=i;
            }
        }

        //Events
        while (const std::optional event = window.pollEvent())
        {
            //Close window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            //press escape
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
            else if (const auto *TextEntered = event->getIf<sf::Event::TextEntered>())
            {
                if (static_cast<char>(TextEntered->unicode) == '\n') // doesnt work
                {
                    std::cout << "here1" << std::endl;
                    std::string printed_string;
                }
                printed_string = printed_string += TextEntered->unicode;
            }
            //mouse click
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                if (mouse_menu<elements_length){
                    std::cout << "pressed: " +std::to_string(mouse_menu)<<std::endl;
                    if (mouse_menu==0){
                        game_menu(&window, &font, window_size, char_size);
                    }else if (mouse_menu==2){
                        gaussian_mouse(&window, &font);
                    }else if (mouse_menu==elements_length-1){
                        window.close();
                    }
                    // test();
                }
            }
        }
        printed_text.setString(printed_string);
        printed_text.setFillColor(sf::Color::White);

        window.clear();
        window.draw(printed_text);
        for (int i = 0; i < elements_length; i++)
        {
            window.draw(choices[i]);
            window.draw(element_texts[i]);
        }
        window.display();

        // cleanup
        for (int i = 0; i < sizeof(elements) / sizeof(elements[0]); i++)
        {
            choices[i].setOutlineColor(sf::Color::White);
        }
        mouse_menu=elements_length;
    }
}
