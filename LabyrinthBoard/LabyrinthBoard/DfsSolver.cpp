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

#include "DfsSolver.h"


/**
 *
 *	Uses Depth-first search to check if there is a path
 *	between pStart and the target cell in the board.
 *
 */
bool DfsSolver::PathExists_Internal(Board& board, Cell* pStart)
{
	std::cout << "Solving with DFS\n\n";

	std::stack<Cell*> cellStack;

	cellStack.push(pStart);

	Cell* pCurrent = NULL;
	Cell* pNeghbour = NULL;

	while( ! cellStack.empty())
	{
		// Get the next element from the stack
		pCurrent = cellStack.top();
		pCurrent->MarkVisited();
		cellStack.pop();

		// Display some information
		std::cout << "\n   Stack size: " << cellStack.size();
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
			AddIfPassableAndNotVisited(cellStack, pCurrent->GetLeftNeighbour());
			AddIfPassableAndNotVisited(cellStack, pCurrent->GetRightNeighbour());
			AddIfPassableAndNotVisited(cellStack, pCurrent->GetTopNeighbour());
			AddIfPassableAndNotVisited(cellStack, pCurrent->GetBottomNeighbour());
		}
	}

	return false;
}


/**
 *
 *	Adds a cell to the stack cellStack, but only if it is passable
 *	and has not been visited until now.
 *	The function also marks the cell as visited.
 *
 */
void DfsSolver::AddIfPassableAndNotVisited(std::stack<Cell*> & cellStack, Cell* pCell)
{
	std::cout << "      Should we add ";
	pCell->PrintInfo();
	std::cout << "? ...";

	if(pCell && pCell->IsPassable() && ! pCell->IsVisited())
	{
		std::cout << "Yes";

		// Mark the cell as visited
		pCell->MarkVisited();

		// Push the cell to the stack
		cellStack.push(pCell);
	}
	else
	{
		std::cout << "No";
	}

	std::cout << std::endl;
}