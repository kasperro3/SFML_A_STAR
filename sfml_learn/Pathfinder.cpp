#include "Pathfinder.hpp"
#include <limits>
#include <thread>
#include <chrono>

Pathfinder::Pathfinder(Cell* IstartNode, Cell* IendNode) : startNode(IstartNode), endNode(IendNode)
{
	Cell* current;
	startNode->costFromStart = 0;
	startNode->CalculateDistance(*endNode);
	openSet.push_back(startNode);
	while (!openSet.empty())
	{
		// grab closest cell
		current = ExtractMin();
		for (Cell* cell : current->GetNeighbours())
		{
			if (cell == startNode)
			{
				std::cout << "Found path" << std::endl;
				return;
			}
			openSet.push_back(cell);
			cell->parent = current;
			cell->costFromStart = cell->parent->costToTarget;
			cell->CalculateDistance(*endNode);
			std::cout << "Pathing..." << std::endl;
		}
		current->ChangeCellType(Board::Path);
		closedSet.push_back(current);
		std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(100));
	}
}

Cell* Pathfinder::ExtractMin()
{
	int min = std::numeric_limits<int>::max();
	int minIndex = 0;
	Cell* minCell = nullptr;
	for (int i = 0, n = openSet.size(); i < n; i++)
	{
		if (openSet[i]->costToTarget < min)
		{
			minCell = openSet[i];
			minIndex = i;
			min = minCell->costToTarget;
		}
	}
	
	openSet.erase(openSet.begin() + minIndex);
	return minCell;
}
