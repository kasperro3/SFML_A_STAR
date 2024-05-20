#include "Board.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 500), "SFML works!");
    Board b(10, 10, window);

    sf::RectangleShape rect(sf::Vector2f(19.f, 19.f));
    rect.setPosition(2, 2);
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(79, 84, 89));
    rect.setFillColor(sf::Color(172, 177, 182));


    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // creating maze
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.scancode)
                {
                    case sf::Keyboard::Scan::W:
                        b.Mark(sf::Mouse::getPosition(window), Board::Type::Wall);
                        break;
                    case sf::Keyboard::Scan::A:
                        b.Mark(sf::Mouse::getPosition(window), Board::Type::StartNode);
                        break;
                    case sf::Keyboard::Scan::D:
                        b.Mark(sf::Mouse::getPosition(window), Board::Type::EndNode);
                        break;
                    case sf::Keyboard::Scan::S:
                        b.Mark(sf::Mouse::getPosition(window), Board::Type::Default);
                        break;
                }
            }
        }

        window.clear();
        window.draw(rect);
        window.display();
    }

    return 0;
}