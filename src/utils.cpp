#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "utils.hpp"


std::tuple<std::vector<sf::RectangleShape>, std::vector<sf::Text>> menu_template(std::string elements[], int elements_length, unsigned int window_size[], sf::Font *font, unsigned int char_size){
    std::vector<sf::Text> element_texts;
    // int elements_length = sizeof(elements) / sizeof(elements[0]);
    std::vector<sf::RectangleShape> choices;
    float fraction_of_window = 0.4;
    unsigned int space_between = 50;
    unsigned int section_start_x = window_size[0] * ((1 - fraction_of_window) / 2);
    unsigned int center_position_y = window_size[1] / 2;
    for (int i = 0; i < elements_length; i++)
    {
        unsigned int centers_x = section_start_x + ((window_size[0] * fraction_of_window) / elements_length) * (1 / 2 + i); // determine the center positions of the elements
        sf::RectangleShape choice({(window_size[1] * fraction_of_window), ((window_size[0] * fraction_of_window) / elements_length) - space_between});
        choice.setOutlineThickness(10.f);
        choice.setFillColor(sf::Color::Transparent);
        choice.setOrigin({choice.getSize().x / 2, choice.getSize().y / 2});
        choice.setPosition({center_position_y, centers_x});
        choice.setOutlineColor(sf::Color::White);
        choices.push_back(choice);
        sf::Text element_text(*font);
        element_text.setCharacterSize(char_size);
        element_text.setString(elements[i]);
        sf::FloatRect text_bounds = element_text.getLocalBounds();
        element_text.setOrigin(text_bounds.getCenter());
        element_text.setPosition({center_position_y, centers_x});
        element_texts.push_back(element_text);
    }
    return std::make_tuple(choices, element_texts);
}