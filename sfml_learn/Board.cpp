#include "Board.hpp"
#include <iostream>

Board::Board(int Iwidth, int Iheight, int IcellSize, sf::RenderWindow* Itarget){
	target = Itarget;
	width = Iwidth;
	height = Iheight;
	cellSize = IcellSize;
	std::vector<Cell> row;
	
	// create board
	for (int i = 0; i < width; i += cellSize)
	{
		for (int j = 0; j < height; j += cellSize)
		{
			sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
			rect.setPosition(sf::Vector2f(i, j));
			rect.setOutlineThickness(1);
			rect.setOutlineColor(sf::Color::Black);
			Cell cell(rect, i, j, Type::Default);
			row.push_back(cell);
		}
		BoardArray.push_back(row);
		row.clear();
	}
}

void Board::ColorBoard(sf::Event& event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		Mark(sf::Mouse::getPosition(*target), Board::Type::Wall);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		Mark(sf::Mouse::getPosition(*target), Board::Type::Default);

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.scancode)
		{
		case sf::Keyboard::Scan::W:
			Mark(sf::Mouse::getPosition(*target), Board::Type::Wall);
			break;
		case sf::Keyboard::Scan::A:
			Mark(sf::Mouse::getPosition(*target), Board::Type::StartNode);
			break;
		case sf::Keyboard::Scan::D:
			Mark(sf::Mouse::getPosition(*target), Board::Type::EndNode);
			break;
		case sf::Keyboard::Scan::S:
			Mark(sf::Mouse::getPosition(*target), Board::Type::Default);
			break;
		case sf::Keyboard::Scan::R:
			Clear();
			break;
		case sf::Keyboard::Scan::F:
			// find path
			break;
		}
	}
}

void Board::Mark(sf::Vector2<int> point, Type type)
{
	point.x = point.x / 20;
	point.y = point.y / 20;

	if (point.x < 0 || point.y < 0)
		return;
	if (point.x >= width / cellSize || point.y >= height / cellSize)
		return;

	std::cout << "marked: " << point.x << " " << point.y << " " << type << std::endl;

	if (type == Type::StartNode)
	{
		if (startNode)
		{
			startNode->ChangeCellType(Type::Default);
		}
		startNode = &BoardArray[point.x][point.y];
	}
	else if (type == Type::EndNode)
	{
		if (endNode)
		{
			endNode->ChangeCellType(Type::Default);
		}
		endNode = &BoardArray[point.x][point.y];
	}
	BoardArray[point.x][point.y].ChangeCellType(type);
}

// render board run this every frame
void Board::Draw()
{
	for (int i = 0, s = BoardArray.size(); i < s; i++)
	{
		for (int j = 0, z = BoardArray[i].size(); j < z; j++)
		{
			target->draw(BoardArray[i][j].rect);
		}
	}
}

void Board::Clear() {
	for (auto& row : BoardArray)
		for (Cell& cell : row)
			cell.ChangeCellType(Board::Default);
}

void Cell::Cell::ChangeCellType(Board::Type type)
{
	switch (type)
	{
	case Board::Type::Default:
		rect.setFillColor(sf::Color(217, 217, 217));
		break;
	case Board::Type::Wall:
		rect.setFillColor(sf::Color::Black);
		break;
	case Board::Type::StartNode:
		rect.setFillColor(sf::Color::Green);
		break;
	case Board::Type::EndNode:
		rect.setFillColor(sf::Color::Red);
		break;
	}
}