#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

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


struct Cell {
	sf::RectangleShape rect;
	int x;
	int y;
	Cell* parent;
	int costToTarget = 0;
	int costFromStart = INFINITY;
	int totalCost = INFINITY;
	Board::Type type;
	void ChangeCellType(Board::Type);
	Cell(sf::RectangleShape Irect, int Ix, int Iy, Board::Type Itype) : rect(Irect), x(Ix), y(Iy), type(Itype) { ChangeCellType(type); };
};