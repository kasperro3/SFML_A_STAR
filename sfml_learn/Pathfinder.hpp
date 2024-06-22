#pragma once
#include "Board.hpp"

class Pathfinder {
	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	std::vector<std::vector<Cell>>* board;
	Cell* startNode;
	Cell* endNode;
	Board b;

public:
	Pathfinder(Cell* IstartNode, Cell* IendNode, std::vector<std::vector<Cell>>* Iboard, Board&);
	~Pathfinder() { openSet.clear(); closedSet.clear(); };
	Cell* ExtractMin();
	void DrawPath();
	bool IsDiagonal(Cell* current, Cell* cell);
};