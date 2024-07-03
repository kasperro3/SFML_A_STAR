#include "Pathfinder.hpp"
#include <limits>
#include <thread>
#include <chrono>

Pathfinder::Pathfinder(std::vector<std::vector<Cell>>* Iboard, Board& b) : board(Iboard), b(b) {}

void Pathfinder::FindPath(Cell* startNode, Cell* endNode)
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
			DrawPath(startNode, endNode);
			return;
		}

		float tentativeCost;

		for (Cell* cell : current->GetNeighbours(*board))
		{
			if (IsDiagonal(current, cell))
				tentativeCost = current->costFromStart + 1.41;
			else
				tentativeCost = current->costFromStart + 1;

			if (tentativeCost < cell->costFromStart)
			{
				cell->parent = current;
				cell->costFromStart = tentativeCost;
				cell->CalculateDistance(*endNode);

				if (std::find(openSet.begin(), openSet.end(), cell) == openSet.end())
					openSet.push_back(cell);
			}
		}
		closedSet.push_back(current);
	}
	DrawPath(startNode, endNode);

	openSet.clear();
	closedSet.clear();
}

Cell* Pathfinder::ExtractMin()
{
	float min = std::numeric_limits<float>::max();
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

void Pathfinder::DrawPath(Cell *startNode, Cell* endNode)
{
    Cell* current = endNode->parent;
    while (current != startNode)
    {
        current->ChangeCellType(Board::Type::Path);
		b.target->draw(current->rect);
		b.target->display();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		current = current->parent;
    }
}

bool Pathfinder::IsDiagonal(Cell* current, Cell* cell)
{
	if(current->x != cell->x && current->y != cell->y)
		return true;
	return false;
}

