#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "Terne_game_utils.hpp"


std::tuple<std::vector<sf::RectangleShape>, std::vector<sf::CircleShape>> main_char(sf::Vector2f position){
    std::vector<sf::RectangleShape> character_rects;
    std::vector<sf::CircleShape> character_circs;
    
    sf::RectangleShape main_body=sf::RectangleShape({30, 50});
    main_body.setPosition(position);
    main_body.setFillColor(sf::Color::White);
    main_body.setOrigin({main_body.getSize().x / 2, main_body.getSize().y / 2});
    character_rects.push_back(main_body);
    float head_radius=20;
    sf::CircleShape head=sf::CircleShape(head_radius);
    head.setOrigin({head_radius,head_radius});
    head.setPosition(position+ sf::Vector2f(0, -head_radius-main_body.getSize().y / 2));
    head.setFillColor(sf::Color::White);
    character_circs.push_back(head);
    return std::make_tuple(character_rects, character_circs);
}



sf::Vector2f jump(float jump_time){
    float y=300*(-1*pow(((2*jump_time)-1), 2)+1);
    return sf::Vector2f(0, y);
}

void obstacle_move(std::vector<sf::RectangleShape> &obstacle_list, float game_time){
    for (int i=obstacle_list.size()-1; i>-1; i--){
        sf::Vector2f pos = obstacle_list[i].getPosition();
        if (pos.x < -100 && i==0){
            obstacle_list.erase(obstacle_list.begin());
            break;
        }
        obstacle_list[i].setPosition(pos-(1+static_cast<float> (sqrt(game_time)))*sf::Vector2f(1, 0));
    }
}

sf::RectangleShape floatrect_to_rectangleShape(sf::FloatRect float_rect){
    sf::RectangleShape rectShape;
    rectShape.setPosition(sf::Vector2f(float_rect.position));
    rectShape.setSize(sf::Vector2f(float_rect.size));
    rectShape.setFillColor(sf::Color::Transparent);  // Make it transparent
    rectShape.setOutlineColor(sf::Color::Red);        // Outline color
    rectShape.setOutlineThickness(2.f);               // Outline thickness
    return rectShape;
}
