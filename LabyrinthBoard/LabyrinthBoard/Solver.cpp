#include <iostream>

#include "Solver.h"


/**
 *
 *	Construct a new Solver object
 *
 */
Solver::~Solver()
{
	// Nothing to do here
}


/**
 *
 *	Checks whether a path exists between the starting and ending
 *	cells in the labyrinth
 *
 *	This function does not actually search in the labyrinth.
 *	It just prepares and passes the necessary arguments to the
 *	PathExists_Internal() function, which does the actual search.
 *	
 *
 **/
bool Solver::PathExists(Board& board)
{
	std::cout << "Let's try to find if a path exists!\n\n";

	// First mark all cells as not visited.
	// This is important, as another search may have been carried
	// on the board
	board.MarkAllCellsNotVisited();

	// Now try to find the starting cell, if such exists
	Cell* pStart = board.GetStart();

	if(pStart == NULL)
	{
		// If there is no start cell, no search can be performed
		std::cout << "There is no starting cell in the labyrinth!\n";
		return false;
	}
	else
	{
		std::cout << "Starting from ";
		pStart->PrintInfo();
		std::cout << std::endl << std::endl;

		return PathExists_Internal(board, board.GetStart());
	}
}
