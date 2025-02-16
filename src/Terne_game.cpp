#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>
#include "Terne_game.hpp"
#include "Terne_game_utils.hpp"

void Terne_game(sf::RenderWindow *window, sf::Font *font, unsigned int window_size[], unsigned int char_size)
{
    unsigned int score = 0;
    sf::Text score_text(*font);
    score_text.setString(std::to_string(score));
    sf::Clock gametime;

    // environment
    float ground_line = 800.f;

    // character
    sf::Vector2f base_char_pos = {300, ground_line};
    std::tuple<std::vector<sf::RectangleShape>, std::vector<sf::CircleShape>> character;
    std::vector<sf::RectangleShape> char_rects;
    std::vector<sf::CircleShape> char_circs;
    sf::Clock jump_time;
    jump_time.stop();

    // obstacles
    unsigned int distance = 0;
    std::vector<sf::RectangleShape> obstacle_list;
    sf::Clock obstacle_timer;
    float obstacle_delay = 3.f;

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution d{500.f, 100.f};

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    return; // enter menu and be able to save score
                }
            }
            else if (const auto *TextEntered = event->getIf<sf::Event::TextEntered>())
            {
                if (static_cast<char>(TextEntered->unicode) == 'w')
                {
                    if (!(jump_time.isRunning()))
                    {
                        jump_time.start();
                    }
                }
                else if (static_cast<char>(TextEntered->unicode) == 'd')
                {
                    ; // implement dash
                }
                else if (static_cast<char>(TextEntered->unicode) == 's')
                {
                    ; // implement roll down
                }
            }
        }

        // character position (with jump)
        float current_jump_time = jump_time.getElapsedTime().asSeconds();
        if (current_jump_time > 1.f)
        {
            jump_time.stop();
            jump_time.reset();
        }
        sf::Vector2f char_pos = base_char_pos - jump(current_jump_time);
        character = main_char(char_pos);
        char_rects = std::get<0>(character);
        char_circs = std::get<1>(character);

        // obstacles
        if (obstacle_timer.getElapsedTime().asSeconds() > obstacle_delay)
        {
                std::cout << "Obstacle spawned" << std::endl;
                obstacle_delay = static_cast<float>(std::lround(d(gen)))/(250);
                // (1+static_cast<float> (sqrt(gametime.getElapsedTime().asSeconds())))
                std::cout << obstacle_delay << std::endl;
                if (obstacle_delay < 1)
                {
                    obstacle_delay = 1;
                }
                sf::RectangleShape obstacle = sf::RectangleShape({100.f, 100.f});
                obstacle.setOrigin({obstacle.getSize().x / 2, obstacle.getSize().y / 2});
                // obstacle.setPosition(sf::Vector2f(window_size[0]+obstacle.getSize().x / 2, ground_line));
                obstacle.setPosition(sf::Vector2f(window_size[0], ground_line)); // for testing
                obstacle_list.push_back(obstacle);
                score +=1;
                score_text.setString(std::to_string(score));
                obstacle_timer.restart();
            
        }
        obstacle_move(obstacle_list, gametime.getElapsedTime().asSeconds());

        // collision
        sf::FloatRect char_bounds = char_rects[0].getGlobalBounds();
        for (int i = 0; i < obstacle_list.size(); i++)
        {
            if (char_bounds.findIntersection(obstacle_list[i].getGlobalBounds()))
            {
                std::cout << "collision" << std::endl;
                return;
            }
        }
        window->clear();
        // score
        window->draw(score_text);
        // character
        for (int i = 0; i < char_rects.size(); i++)
        {
            window->draw(char_rects[i]);
        }
        for (int i = 0; i < char_circs.size(); i++)
        {
            window->draw(char_circs[i]);
        }
        // obstacles
        for (int i = 0; i < obstacle_list.size(); i++)
        {
            window->draw(obstacle_list[i]);
            // window->draw(floatrect_to_rectangleShape(obstacle_list[i].getGlobalBounds()));
        }
        // window->draw(floatrect_to_rectangleShape(char_bounds));

        window->display();
    }
}