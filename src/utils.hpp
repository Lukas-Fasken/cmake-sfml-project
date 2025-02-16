#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <vector>

std::tuple<std::vector<sf::RectangleShape>, std::vector<sf::Text>> menu_template(std::string[], int, unsigned int[], sf::Font *, unsigned int);

#endif