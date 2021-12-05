/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "catch2/catch_all.hpp"
#include "board/Board.h"

TEST_CASE("Coordinates::operator== returns correct values")
{
	SECTION("For equal coordinates")
	{
		REQUIRE(Board::Coordinates(1, 1) == Board::Coordinates(1, 1));
	}
	SECTION("For different coordinates")
	{
		REQUIRE_FALSE(Board::Coordinates(1, 1) == Board::Coordinates(1, 2));
		REQUIRE_FALSE(Board::Coordinates(1, 1) == Board::Coordinates(2, 1));
	}
}

TEST_CASE("Board::hasNeighbour returns correct values for a 3x3 board")
{
	const size_t rowsCount = 3, colsCount = 3;
	Board board(rowsCount, colsCount);

	for (size_t row = 0; row < rowsCount; row++) {
		for (size_t col = 0; col < colsCount; ++col) {
			Board::Coordinates coordinates(row, col);
			REQUIRE(board.hasNeighbour(coordinates, Direction::Up) == row > 0);
			REQUIRE(board.hasNeighbour(coordinates, Direction::Down) == row < rowsCount-1);
			REQUIRE(board.hasNeighbour(coordinates, Direction::Left) == col > 0);
			REQUIRE(board.hasNeighbour(coordinates, Direction::Right) == col < colsCount-1);
		}
	}
}

TEST_CASE("Board::hasNeighbour returns false for cells outside the board")
{
	Board board(2, 2);

	for (auto d : AllDirections()) {
		REQUIRE_FALSE(board.hasNeighbour(Board::Coordinates(10, 10), d));
	}
}

TEST_CASE("Board::getNeighbourOf returns correct values")
{
	Board board(3, 3);
	Board::Coordinates middle(1, 1);

	REQUIRE(board.getNeighbourOf(middle, Direction::Up) == Board::Coordinates(middle.row-1, middle.col));
	REQUIRE(board.getNeighbourOf(middle, Direction::Down) == Board::Coordinates(middle.row+1, middle.col));
	REQUIRE(board.getNeighbourOf(middle, Direction::Left) == Board::Coordinates(middle.row, middle.col-1));
	REQUIRE(board.getNeighbourOf(middle, Direction::Right) == Board::Coordinates(middle.row, middle.col+1));
}
