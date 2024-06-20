#pragma once
#include "Board.hpp"

class Pathfinder {
	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	Cell* startNode;
	Cell* endNode;
	std::vector<std::vector<Cell>>* BoardArray;

public:
	Pathfinder(Cell* IstartNode, Cell* IendNode);
	Cell* ExtractMin();
};