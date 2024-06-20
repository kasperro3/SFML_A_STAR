#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

struct Cell;

class Board {
	// board variables
	int width;
	int height;
	int cellSize;
	std::vector<std::vector<Cell>> BoardArray;
	
	// rendering window
	sf::RenderWindow* target;

	// pathfinder variables
	Cell *startNode;
	Cell *endNode;

	void Clear();

public:
	enum Type { Default, Wall, StartNode, EndNode, Path };

	Board(int, int, int, sf::RenderWindow*);
	void Mark(sf::Vector2<int>, Type);
	void Draw();
	void ColorBoard(sf::Event&);
};


// building block of board
struct Cell {
	sf::RectangleShape rect;
	int x;
	int y;
	int size = 1;
	Board::Type type;
	Cell(sf::RectangleShape Irect, int Ix, int Iy, Board::Type Itype) : rect(Irect), x(Ix), y(Iy), type(Itype) { ChangeCellType(type); };

	// pathfinder members
	Cell* parent = nullptr;
	int costToTarget = 0;
	int costFromStart = INFINITY;
	void ChangeCellType(Board::Type);
	void CalculateDistance(Cell);
	std::vector<Cell*> GetNeighbours();
};