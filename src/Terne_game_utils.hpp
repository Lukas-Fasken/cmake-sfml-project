#ifndef TERNE_GAME_UTILS_HPP
#define TERNE_GAME_UTILS_HPP

#include <SFML/Graphics.hpp>

std::tuple<std::vector<sf::RectangleShape>, std::vector<sf::CircleShape>> main_char(sf::Vector2f);

sf::Vector2f jump(float);

void obstacle_move(std::vector<sf::RectangleShape> &, float);

sf::RectangleShape floatrect_to_rectangleShape(sf::FloatRect);

#endif