#pragma once
#include "Board.hpp"

class Pathfinder {
	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	std::vector<std::vector<Cell>>* board;
	Board b;

public:
	Pathfinder(std::vector<std::vector<Cell>>* Iboard, Board&);
	~Pathfinder() { openSet.clear(); closedSet.clear(); };
	Cell* ExtractMin();
	void DrawPath(Cell*, Cell*);
	void FindPath(Cell* startNode, Cell* endNode);
	bool IsDiagonal(Cell* current, Cell* cell);
};