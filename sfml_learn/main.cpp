#include "Board.hpp"
#include "Pathfinder.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 900), "A* Algorithm Visualization", sf::Style::Close);
    Board b(600, 600, 20, &window);

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            b.ColorBoard(event);
        }

        window.clear();
        b.Draw();
        window.display();
    }

    return 0;
}