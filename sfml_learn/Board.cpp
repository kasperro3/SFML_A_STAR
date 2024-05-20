#include "Board.h"
#include <iostream>



void Board::Mark(sf::Vector2<int> point, Type typ)
{
	std::cout << "marked: " << point.x << " " << point.y << " " << typ <<std::endl;
}

Board::Board(int width, int height, sf::RenderWindow &target) {
	sf::RectangleShape rect(sf::Vector2f(120.f, 50.f));
	rect.setFillColor(sf::Color(255, 255, 0));
	target.draw(rect);
}