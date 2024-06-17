#pragma once
#include "Board.hpp"

class Pathfinder {
	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
public:
	Pathfinder(Cell* IstartNode, Cell* IendNode, std::vector<std::vector<Cell>>* IBoardArray);
	Cell* ExtractMin();
	int calculateDistance();

};