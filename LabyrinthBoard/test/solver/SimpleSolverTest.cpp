/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "catch2/catch_all.hpp"
#include "solver/SolverLib.h"
#include "stream/StreamLib.h"

#include <fstream>

TEST_CASE("SimpleSolver::pathExists returns true when there is a path")
{
	BoardBuilder builder;
	builder
		<< "################"
		<< "#          #   #"
		<< "#### ^     #   #"
		<< "#       ####   #"
		<< "#  #      ##   #"
		<< "#  #           #"
		<< "#  #  #   ######"
		<< "#  #  #   #   $#"
		<< "#  #### ###  ###"
		<< "#              #"
		<< "################";

	Board board = builder.build();

	std::ofstream nullStream;
	nullStream.setstate(std::ios_base::badbit);

	SECTION("Using BFS")
	{
		REQUIRE(createSolver(board, 'b', nullStream)->pathExists());
	}
	SECTION("Using DFS")
	{
		REQUIRE(createSolver(board, 'd', nullStream)->pathExists());
	}
}

TEST_CASE("SimpleSolver::pathExists returns false when there is not path")
{
	BoardBuilder builder;
	builder
		<< "################"
		<< "#^  #      #   #"
		<< "#####      #   #"
		<< "#       ####   #"
		<< "#  #      ##   #"
		<< "#  #           #"
		<< "#  #  #   ######"
		<< "#  #  #   #   $#"
		<< "#  #### ###  ###"
		<< "#              #"
		<< "################";

	std::ofstream nullStream;
	nullStream.setstate(std::ios_base::badbit);

	Board board = builder.build();

	SECTION("Using BFS")
	{
		REQUIRE_FALSE(createSolver(board, 'b', nullStream)->pathExists());
	}
	SECTION("Using DFS")
	{
		REQUIRE_FALSE(createSolver(board, 'd', nullStream)->pathExists());
	}
}


