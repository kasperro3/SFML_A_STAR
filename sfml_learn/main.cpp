#include "Board.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 500), "SFML works!");
    Board b(600, 500, sf::Vector2f(20, 20), &window);

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                b.Mark(sf::Mouse::getPosition(window), Board::Type::Wall);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                b.Mark(sf::Mouse::getPosition(window), Board::Type::Default);

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
        b.Draw();
        window.display();
    }

    return 0;
}