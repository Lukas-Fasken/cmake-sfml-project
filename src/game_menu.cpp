#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "game_menu.hpp"
#include "utils.hpp"
#include "gaussian_mouse.hpp"
#include "Terne_game.hpp"

void game_menu(sf::RenderWindow *window, sf::Font *font, unsigned int window_size[], unsigned int char_size)
{

    // setting up the menu
    std::string menu_options[] = {"Gaussian", "Terne's game", "NoThInG", "Back"};
    int menu_size = sizeof(menu_options) / sizeof(menu_options[0]);
    std::tuple<std::vector<sf::RectangleShape>, std::vector<sf::Text>> main_menu = menu_template(menu_options, menu_size, window_size, font, char_size);
    std::vector<sf::Text> element_texts;
    std::vector<sf::RectangleShape> element_boxes;
    element_boxes = std::get<0>(main_menu);
    element_texts = std::get<1>(main_menu);

    window->clear();
    for (int i = 0; i < menu_size; i++)
    {
        window->draw(element_boxes[i]);
        window->draw(element_texts[i]);
    }
    window->display();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // mouse vairables
    int mouse_menu = menu_size;
    sf::Vector2i mouse_pos;

    while (window->isOpen())
    {
        mouse_pos = sf::Mouse::getPosition(*window);
        for (int i = 0; i < menu_size; i++)
        {
            if (element_boxes[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
            {
                element_boxes[i].setOutlineColor(sf::Color::Red);
                mouse_menu = i;
            }
        }
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
            }
            // mouse click
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) // need to implement mouse button released
            {
                if (mouse_menu < menu_size)
                {
                    std::cout << "pressed: " + std::to_string(mouse_menu) << std::endl;
                    if (mouse_menu == 0)
                    {
                        gaussian_mouse(window, font);
                    }else if (mouse_menu== 1){
                        
                        Terne_game(window, font, window_size, char_size);
                    }
                    else if (mouse_menu == menu_size - 1)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        return;
                    }
                    // test();
                }
            }
        }

        window->clear();
        for (int i = 0; i < menu_size; i++)
        {
            window->draw(element_boxes[i]);
            window->draw(element_texts[i]);
        }
        window->display();
        for (int i = 0; i < menu_size; i++)
        {
            element_boxes[i].setOutlineColor(sf::Color::White);
        }
        mouse_menu = menu_size;
    }
}