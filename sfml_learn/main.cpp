#include "Pathfinder.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "A* Algorithm Visualization", sf::Style::Close);
    Board b(600, 600, 20, &window);

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // this can't be in board unfortunatelly
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::F)
                {
                    if (b.startNode && b.endNode)
                        Pathfinder p(b.startNode, b.endNode, &b.BoardArray);
                    else
                        std::cout << "No start or end node" << std::endl;
                }
            }

            b.ColorBoard(event);
        }

        window.clear();
        b.Draw();
        window.display();
    }

    return 0;
}