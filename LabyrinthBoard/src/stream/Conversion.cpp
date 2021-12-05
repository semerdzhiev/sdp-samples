/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include "Conversion.h"

/// Converts a direction to a string
const char* toString(Direction& d)
{
	switch (d) {
	case Direction::Up:
		return "Up";

	case Direction::Right:
		return "Right";

	case Direction::Down:
		return "Down";

	case Direction::Left:
		return "Left";

	default:
		throw std::invalid_argument("The supplied value is not one of the named enumerators defined for Direction");
	}
}

/// Returns the cell type associated with a certain character
/// @throws std::invalid_argument if the character does not correspond to any cell type
Cell::Type toCellType(char c)
{
	switch (c) {
	case '#':
		return Cell::Type::Wall;
	case ' ':
		return Cell::Type::Corridor;
	case '^':
		return Cell::Type::Start;
	case '$':
		return Cell::Type::Target;
	default:
		throw std::invalid_argument("Invalid character");
	}
}

/// Converts a cell type to its representation as a character
char toChar(Cell::Type t)
{
	static char symbols[] = { ' ', '#', '$', '^' };
	return symbols[static_cast<size_t>(t)];
}