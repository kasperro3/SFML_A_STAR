#include "Pathfinder.hpp"
#include <limits>
#include <thread>
#include <chrono>

Pathfinder::Pathfinder(Cell* IstartNode, Cell* IendNode, std::vector<std::vector<Cell>>* Iboard) : startNode(IstartNode), endNode(IendNode), board(Iboard)
{
	Cell* current;
	startNode->costFromStart = 0;
	startNode->CalculateDistance(*endNode);
	openSet.push_back(startNode);
	while (!openSet.empty())
	{
		// grab closest cell
		current = ExtractMin();

		if (current == endNode)
		{
			std::cout << "Found path" << std::endl;
			break;
		}

		std::vector<Cell*> neighbours = current->GetNeighbours(*board);
		for (Cell* cell : neighbours)
		{
			cell->CalculateDistance(*endNode);
			if (cell->costToTarget < current->costToTarget)
			{
				cell->parent = current;
				cell->costFromStart = current->costFromStart + 1;
				cell->CalculateDistance(*endNode);
				openSet.push_back(cell);
			}
		}
		closedSet.push_back(current);
	}

	DrawPath();
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

void Pathfinder::DrawPath()
{
	while(closedSet.back() != startNode)
	{
		closedSet.back()->ChangeCellType(Board::Type::Path);
		closedSet.push_back(closedSet.back()->parent);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
