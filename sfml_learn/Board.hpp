#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#define BOARD_WIDTH 600
#define BOARD_HEIGHT 600

struct Cell;

class Board {
	// board variables
	int width;
	int height;
	int cellSize;
	bool locked;
	
public:
	enum Type { Default, Wall, StartNode, EndNode, Path };
	// rendering window
	sf::RenderWindow* target;

	// pathfinder variables
	Cell* startNode;
	Cell* endNode;

	std::vector<std::vector<Cell>> BoardArray;
	Board(int, int, int, sf::RenderWindow*);
	~Board(){};
	void Mark(sf::Vector2<int>, Type);
	void Draw();
	void Clear();
	void ColorBoard(sf::Event&);
	void Lock();
	void Unlock();
	void ClearPath();
};


// building block of board
struct Cell {
	sf::RectangleShape rect;
	float x;
	float y;
	int size = 1;
	Board::Type type;
	Cell(sf::RectangleShape Irect, int Ix, int Iy, Board::Type Itype) : rect(Irect), x(Ix), y(Iy), type(Itype) { ChangeCellType(type); };

	// pathfinder members
	Cell* parent = nullptr;
	float costToTarget = INFINITY;
	float costFromStart = INFINITY;
	int depth = 0;
	void ChangeCellType(Board::Type);
	void CalculateDistance(Cell);
	std::vector<Cell*> GetNeighbours(std::vector<std::vector<Cell>>&) const;
};