#pragma once
#include "Board.hpp"

class Pathfinder {
	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	std::vector<std::vector<Cell>>* board;
	Cell* startNode;
	Cell* endNode;

public:
	Pathfinder(Cell* IstartNode, Cell* IendNode, std::vector<std::vector<Cell>>* Iboard);
	Cell* ExtractMin();
	void DrawPath();
};