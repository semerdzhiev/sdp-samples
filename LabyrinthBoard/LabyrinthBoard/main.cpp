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
#include <string>

#include "Board.h"
#include "DfsSolver.h"
#include "BfsSolver.h"


int main(int argc, char* argv[])
{
	// Will store the path to the file to open
	char path[_MAX_PATH];

	// If the path is supplied as a command line argument, read it
	if(argc == 2)
	{
		strcpy_s(path, _MAX_PATH, argv[1]);
	}
	else
	{
		std::cout << "Enter path to labyrinth file: ";
		std::cin.getline(path, _MAX_PATH);
	}

	// Create a board and try to load the contents of the file
	Board board;

	std::cout << "Trying to load labyrinth from \"" << path << "\"...";

	if(board.LoadFromFile(path))
	{
		std::cout << "done\n\n";

		// If loading was successful, print the board
		board.Print();

		if (board.GetRowsCount() == 0)
		{
			std::cout << "The board is empty.\n";
			return 0;
		}

		// Now ask the user how he wants to search
		// and create the appropriate solver object
		std::cout << "Search with (B)FS or (D)FS: ";
		char choice;
		std::cin >> choice;

		Solver* pSolver = NULL;

		if (choice == 'B' || choice == 'b')
		{
			pSolver = new BfsSolver();
		}
		else
		{
			pSolver = new DfsSolver();
		}

		// Try to find the path
		bool pathExists = pSolver->PathExists(board);

		// Do not forget to delete the solver object!
		delete pSolver;

		std::cout
			<< "\n   "
			<< (pathExists ? "There is a path!" : "Sorry, there is no path!")
			<< std::endl;
	}
	else
	{
		std::cout << "failed!\n\n";
		std::cerr << "Cannot load labyrinth from input file!\n";
		return 1;
	}

	return 0;
}
