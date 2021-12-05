/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "SolverFactory.h"
#include "SimpleSolver.h"

#include <stdexcept>

/// @brief Create a solver object
/// @param board Refrence to the board, which the solver will work with
/// @param solverType The type of solver to create -- 'b' for BFS and 'd' for DFS. Can be upper or lowercase.
/// @param outputStream A reference to an output stream, which will be used to provide detailed information.
/// @throws std::domain_error if the specified type is not valid
std::unique_ptr<Solver> createSolver(Board& board, char solverType, std::ostream& outputStream)
{
	switch (solverType) {
	case 'b':
	case 'B':
		return std::make_unique<BfsSolver>(board, outputStream);

	case 'd':
	case 'D':
		return std::make_unique<DfsSolver>(board, outputStream);

	default:
		throw std::domain_error("Incorrect algorithm type");
	}
}