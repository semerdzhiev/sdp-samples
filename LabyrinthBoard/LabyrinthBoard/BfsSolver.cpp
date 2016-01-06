/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>
#include <stack>

#include "BfsSolver.h"


/**
 *
 *	Uses Breadth-first search to check if there is a path
 *	between pStart and the target cell in the board.
 *
 */
bool BfsSolver::PathExists_Internal(Board& board, Cell* pStart)
{
	std::cout << "Solving with BFS\n\n";

	std::queue<Cell*> cellQueue;

	cellQueue.push(pStart);

	Cell* pCurrent = NULL;
	Cell* pNeghbour = NULL;

	while( ! cellQueue.empty())
	{
		// Get the next element from the stack
		pCurrent = cellQueue.front();
		pCurrent->MarkVisited();
		cellQueue.pop();

		// Display some information
		std::cout << "\n   Queue size: " << cellQueue.size();
		std::cout << "\n   Popped ";
		pCurrent->PrintInfo();
		std::cout << std::endl;

		if(pCurrent->IsTarget())
		{
			// If the target is found, then there is a path
			return true;
		}
		else
		{
			// Otherwise keep looking
			AddIfPassableAndNotVisited(cellQueue, pCurrent->GetLeftNeighbour());
			AddIfPassableAndNotVisited(cellQueue, pCurrent->GetRightNeighbour());
			AddIfPassableAndNotVisited(cellQueue, pCurrent->GetTopNeighbour());
			AddIfPassableAndNotVisited(cellQueue, pCurrent->GetBottomNeighbour());
		}
	}

	return false;
}


/**
 *
 *	Adds a cell to the queue cellQueue, but only if it is passable
 *	and has not been visited until now.
 *	The function also marks the cell as visited.
 *
 */
void BfsSolver::AddIfPassableAndNotVisited(std::queue<Cell*> & cellQueue, Cell* pCell)
{
	std::cout << "      Should we add ";
	pCell->PrintInfo();
	std::cout << "? ...";

	if(pCell && pCell->IsPassable() && ! pCell->IsVisited())
	{
		std::cout << "Yes";

		// Mark the cell as visited
		pCell->MarkVisited();

		// Enqeue the cell
		cellQueue.push(pCell);
	}
	else
	{
		std::cout << "No";
	}

	std::cout << std::endl;
}