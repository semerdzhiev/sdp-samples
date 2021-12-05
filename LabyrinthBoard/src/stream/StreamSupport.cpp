/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "StreamSupport.h"
#include "BoardBuilder.h"
#include "Conversion.h"

#include <iostream>

/// Output the contents of a board
std::ostream& operator<<(std::ostream& out, const Cell& c)
{
	out << toChar(c.type());
	return out;
}

std::ostream& operator<<(std::ostream& out, Direction direction)
{
	out << toString(direction);
	return out;
}

/// Output coordinates in r##c## format
std::ostream& operator<<(std::ostream& out, Board::Coordinates c)
{
	out << "(r" << c.row << "c" << c.col << ")";
	return out;
}

/// Output the contents of a board
std::ostream& operator<<(std::ostream& out, const Board& board)
{
	for (size_t row = 0; row < board.rowsCount(); row++) {
		for (size_t col = 0; col < board.colsCount(); col++) {
			out << board.cell(row, col);
		}
		out << "\n";
	}

	return out;
}

/// Read and overwrite the contents of a board from a stream
std::istream& operator>>(std::istream& in, Board& board)
{
	if(!in)
		throw std::invalid_argument("The input stream is not valid");

	BoardBuilder builder;
	std::string line;

	while (std::getline(in, line)) {
		builder.addRow(line);
	}

	board = builder.build(); // relies on the builder to work correctly!
	return in;
}