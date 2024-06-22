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

// on keyboard action update board
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
			// it causes a lot of problems, no time to fix
		//case sf::Keyboard::Scan::R:
		//	Clear();
		//	break;
		}
	}
}

void Board::Mark(sf::Vector2<int> point, Type type)
{
	point.x = point.x / cellSize;
	point.y = point.y / cellSize;

	if (point.x < 0 || point.y < 0)
		return;
	if (point.x >= width / cellSize || point.y >= height / cellSize)
		return;
	if (BoardArray[point.x][point.y].type == Type::StartNode || BoardArray[point.x][point.y].type == Type::EndNode)
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
	for (auto& row : BoardArray)
		for (Cell& cell : row)
			target->draw(cell.rect);
}

void Board::Clear() 
{
	for (auto& row : BoardArray)
		for (Cell& cell : row)
			cell.ChangeCellType(Board::Default);

	startNode = nullptr;
	endNode = nullptr;
}

// coloring
void Cell::ChangeCellType(Board::Type Itype)
{
	type = Itype;
	switch (Itype)
	{
	case Board::Type::Default:
		rect.setFillColor(sf::Color(217, 217, 217));
		break;
	case Board::Type::Wall:
		rect.setFillColor(sf::Color::Black);
		break;
	case Board::Type::StartNode:
		rect.setFillColor(sf::Color::Red);
		break;
	case Board::Type::EndNode:
		rect.setFillColor(sf::Color::Green);
		break;
	case Board::Type::Path:
		rect.setFillColor(sf::Color::Blue);
		break;
	}
}

void Cell::CalculateDistance(Cell endNode)
{
	// euclidean distance
	costToTarget = sqrt(pow(x - endNode.x, 2) + pow(y - endNode.y, 2)) + costFromStart;
}

std::vector<Cell*> Cell::GetNeighbours(std::vector<std::vector<Cell>>& board)
{
	std::vector<Cell*> neighbours;

	for(int i = x / 20 - 1; i <= x / 20 + 1; i++)
	{
		for(int j = y / 20 - 1; j <= y / 20 + 1; j++)
		{
			if(i < 0 || j < 0)
				continue;
			if(i == x / 20 && j == y / 20)
				continue;
			if(i >= BOARD_WIDTH / 20 || j >= BOARD_HEIGHT / 20)
				continue;
			if(board[i][j].type == Board::Type::Wall)
				continue;

			neighbours.push_back(&board[i][j]);
		}
	}
	return neighbours;
}