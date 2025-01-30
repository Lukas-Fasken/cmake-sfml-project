#include <SFML/Graphics.hpp>
#include <stdio.h>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::Font font("C:/Windows/Fonts/arial.ttf");
    std::string printed_string;
    sf::Text printed_text(font);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
            else if (const auto* TextEntered = event->getIf<sf::Event::TextEntered>()){
                if (TextEntered->unicode < 128){
                    printed_string=printed_string+TextEntered;
                }
            }
        }

        window.clear();

        window.display();
    }
}
