#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <array>
#include <random>
#include <ctime>
#include "gaussian_mouse.hpp"

void gaussian_mouse(sf::RenderWindow *window, sf::Font *font)
{
    time_t timer;
    std::time(&timer);
    int time_delay=0;
    
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution d{0.0,25.0};

    const std::size_t nr_points=100;
    std::array<sf::CircleShape, nr_points> point_list;
    int x=0;

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
            }else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    return;
                }
            }
        }
        if (timer+time_delay<std::time(NULL)){

            sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
            auto random_int_x = [&d, &gen]{ return std::lround(d(gen)); };
            auto random_int_y = [&d, &gen]{ return std::lround(d(gen)); };
            auto time_delay = [&d, &gen]{ return std::lround(d(gen)); };

            sf::Vector2i position={mouse_pos.x+static_cast<int>(random_int_x()), mouse_pos.y+static_cast<int>(random_int_y())};
            sf::CircleShape point(5.f);
            point.setPosition(static_cast<sf::Vector2f>(position));
            point.setFillColor(sf::Color::White);
            point_list[x]=point;
            x++;
            if (x==nr_points){
                x=0;
            }
            
        }

        window->clear();

        for (int i=0; i<nr_points;i++){
            window->draw(point_list[i]);
        }
        window->display();
        
    }
}