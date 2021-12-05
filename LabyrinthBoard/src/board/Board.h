/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include "Cell.h"
#include "Direction.h"

#include <stdexcept>
#include <vector>
#include <iostream>

class Board {
public:
	struct Coordinates {
		size_t row;
		size_t col;

		Coordinates(size_t row, size_t col)
			: row(row), col(col)
		{
		}

		bool operator==(const Coordinates& other) const
		{
			return row == other.row && col == other.col;
		}
	};

private:
	size_t m_rowsCount; /// Number of rows in the board
	size_t m_colsCount; /// Number of columns in the board
	std::vector<Cell> m_board; /// The cells, which comprise the board

	size_t m_startRow; /// Row on which the start cell is located
	size_t m_startCol; /// Column on which the start cell is located

private:
	size_t toLinear(size_t row, size_t col) const noexcept
	{
		return row * colsCount() + col;
	}

public:
	Board(const Board&) = default;
	Board(Board&&) = default;
	Board& operator=(const Board&) = default;
	Board& operator=(Board&&) = default;
	~Board() = default;

	Board() = default;

	Board(size_t rows, size_t cols)
		: m_rowsCount(rows),
		  m_colsCount(cols),
		  m_board(rows * cols),
		  m_startRow(0),
		  m_startCol(0)
	{}

public:
	/// Returns the number of rows of the board
	size_t rowsCount() const noexcept
	{
		return m_rowsCount;
	}

	/// Returns the number of columns of the board
	size_t colsCount() const noexcept
	{
		return m_colsCount;
	}

	/// Checks if the coordinates (row, col) are valid for this board
	bool areCoordinatesValid(size_t row, size_t col) const noexcept
	{
		return row < rowsCount() && col < colsCount();
	}

	/// Returns the cell at (row,col) of the board
	/// @throws std::invalid_argument if the coordinates are not valid
	Cell& cell(size_t row, size_t col)
	{
		return m_board.at(toLinear(row, col));
	}

	/// Returns the cell at (row,col) of the board
	/// @throws std::invalid_argument if the coordinates are not valid
	const Cell& cell(size_t row, size_t col) const
	{
		return m_board.at(toLinear(row, col));
	}

	Cell& cell(Coordinates c)
	{
		return cell(c.row, c.col);
	}

	const Cell& cell(Coordinates c) const
	{
		return cell(c.row, c.col);
	}
	
	void setStartCell(size_t row, size_t col)
	{
		if (!areCoordinatesValid(row, col))
			throw std::invalid_argument("Coordinates are outside of the board");
		
		if( ! cell(row,col).isPassable())
			throw std::invalid_argument("The starting location cannot coincide with a wall");

		m_startRow = row;
		m_startCol = col;
		cell(row, col).type() = Cell::Type::Start;
	}

	/// Returns the coordinates of the start cell
	Coordinates startCellCoordinates()
	{
		return Coordinates(m_startRow, m_startCol);
	}

	void markAllCellsNotVisited() noexcept
	{
		for (Cell& c : m_board)
			c.markNotVisited();
	}

	/// Checks whether the cell at coordinates c is a valid cell in the board
	/// and whether it has a neighbour at the side d
	bool hasNeighbour(Coordinates c, Direction d) const noexcept
	{
		return
			areCoordinatesValid(c.row, c.col) &&
			((d == Direction::Up && c.row > 0) ||
			(d == Direction::Down && c.row < (rowsCount() - 1)) ||
			(d == Direction::Left && c.col > 0) ||
			(d == Direction::Right && c.col < (colsCount() - 1)));
	}

	/// Return the coordinates of the neighbour on the side d of the cell at coordinates c
	/// @throws std::invalid_argument if the cell does not have a neighbour at the specified size
	/// @throws std::invalid_argument of the direction is not one of the named enumeration values of Direction
	Coordinates getNeighbourOf(Coordinates c, Direction d) const
	{
		if (!hasNeighbour(c, d))
			throw std::invalid_argument("The specified cell has no neighbour in the requested direction");

		switch (d) {
		case Direction::Up:    { --c.row; break; }
		case Direction::Down:  { ++c.row; break; }
		case Direction::Left:  { --c.col; break; }
		case Direction::Right: { ++c.col; break; }
		default: throw std::invalid_argument("Invalid direction");
		}
		return c;
	}
};