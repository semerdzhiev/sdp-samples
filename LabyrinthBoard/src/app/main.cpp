/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "board/BoardLib.h"
#include "stream/StreamLib.h"
#include "solver/SolverLib.h"

#include <fstream>
#include <iostream>

void loadAndSolve(const std::string& path)
{
	Board board;

	std::ifstream inputFile(path);
	inputFile >> board;
	std::cout << board;

	std::cout << "Choose solver type -- (B)FS or (D)FS: ";
	char solverType;
	std::cin >> solverType;

	auto solver = createSolver(board, solverType, std::cout);

	std::cout << (solver->pathExists() ? "There is a path!" : "Sorry, there is no path!");
}

int main(int argc, char* argv[])
{
	// STEP 1: Determine which file to open
	std::string path; // Path of the input file

	if (argc == 2) {
		// The path is supplied as a command line argument
		path = argv[1];
	}
	else {
		// Otherwise get it from STDIN
		std::cout << "Enter path to labyrinth file: ";
		std::getline(std::cin, path);
	}

	std::cout << "Input file is \"" << path << "\"\n";

	// STEP 2: Load the board from the file and try to solve it
	try {
		loadAndSolve(path);
	}
	catch (std::exception& e) {
		std::cout
			<< "\nSomething has happened, but not in a good way!\n"
			<< "  " << typeid(e).name() << ": " << e.what() << "\n";
		return 1;
	}

	return 0;
}