/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include "board/BoardLib.h"
#include "stream/StreamLib.h"
#include "Backlog.h"
#include "Solver.h"

#include <iostream>

template <typename BacklogType>
class SimpleSolver : public Solver
{
	BacklogType backlog;
	std::ostream& output; /// Specifies where to output detailed information

public:
	SimpleSolver(Board& board, std::ostream& outputStream)
		: Solver(board), output(outputStream)
	{}

	virtual bool pathExists() override
	{
		output << "Let's try to find if a path exists!\n\n";

		// First mark all cells as not visited. This is important,
		// as another search may have been carried out on the board
		output << "Marking all cells as visited...";
		m_board.markAllCellsNotVisited();
		output << "done.\n\n";

		// Find the starting cell of the labyrinth
		Board::Coordinates start = m_board.startCellCoordinates();

		return pathExists(start);
	}

private:
	bool pathExists(Board::Coordinates start)
	{
		output << "Starting from " << start << "\n\n";
		backlog.add(start);

		size_t step = 1; // counts the number of steps so far
		bool targetFound = false; // whether we have found the target yet or not

		while (!targetFound && backlog.notEmpty())
		{
			output << "\n\nStep " << step++ << ", backlog size: " << backlog.size();

			// pull the coordinates of the next cell to process
			Board::Coordinates current = backlog.pop();
			output << "\n  Popped " << current;

			// process all neighbours of the popped cell
			for (auto direction : AllDirections()) {
				output << "\n  Try to go " << direction << ": ";

				if (m_board.hasNeighbour(current, direction)) {
					targetFound = processCell(m_board.getNeighbourOf(current, direction));
					if (targetFound)
						break;
				}
				else {
					output << "No neighbour on that side";
				}
			}
		}

		output << "\n\n";

		return targetFound;
	}

	bool processCell(Board::Coordinates coordinates)
	{
		Cell& cell = m_board.cell(coordinates);

		if (cell.isTarget()) {
			output << "Found the target at " << coordinates << "!";
			return true;
		}
		else if (cell.isVisited()) {
			output << coordinates << " is already visited.";
		}
		else if (cell.isPassable()) {
			output << "Add " << coordinates << " to the backlog.";
			cell.markVisited();
			backlog.add(coordinates);
		}
		else {
			output << coordinates << " is not passable!";
		}
		return false;
	}
};

// Explicit instantiation for BFS and DFS solvers
template class SimpleSolver<QueueBacklog>;
template class SimpleSolver<StackBacklog>;

// Defined user-friendly names for the BFS and DFS solvers
using BfsSolver = SimpleSolver<QueueBacklog>;
using DfsSolver = SimpleSolver<StackBacklog>;