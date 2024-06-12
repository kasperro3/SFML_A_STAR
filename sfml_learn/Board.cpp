#include "Board.hpp"
#include <iostream>



void Board::Mark(sf::Vector2<int> point, Type typ)
{
	std::cout << "marked: " << point.x << " " << point.y << " " << typ <<std::endl;
	point.x = point.x / 20;
	point.y = point.y / 20;
	
	if (point.x < 0 || point.y < 0)
		return;

	switch (typ)
	{
	case Board::Type::Default:
		BoardArray[point.x][point.y].setFillColor(sf::Color(217, 217, 217));
	break;
	case Board::Type::Wall:
		BoardArray[point.x][point.y].setFillColor(sf::Color::Black);
		break;
	case Board::Type::StartNode:
		BoardArray[point.x][point.y].setFillColor(sf::Color::Green);
		break;
	case Board::Type::EndNode:
		BoardArray[point.x][point.y].setFillColor(sf::Color::Red);
		break;
	}
}

Board::Board(int Iwidth, int Iheight, sf::Vector2f IcubeSize, sf::RenderWindow* Itarget){
	target = Itarget;
	width = Iwidth;
	height = Iheight;
	cubeSize = IcubeSize;
	sf::RectangleShape rect(cubeSize);
	std::vector<sf::RectangleShape> row;
	
	for (int i = 0; i < width; i += cubeSize.y)
	{
		for (int j = 0; j < height; j += cubeSize.x)
		{
			rect.setPosition(sf::Vector2f(i, j));
			rect.setFillColor(sf::Color(217, 217, 217));
			rect.setOutlineColor(sf::Color::Black);
			rect.setOutlineThickness(1);

			row.push_back(rect);
		}
		BoardArray.push_back(row);
		row.clear();
	}
}

void Board::Draw()
{
	for (int i = 0, s = BoardArray.size(); i < s; i++)
	{
		for (int j = 0, z = BoardArray[i].size(); j < z; j++)
		{
			target->draw(BoardArray[i][j]);
		}
	}
}