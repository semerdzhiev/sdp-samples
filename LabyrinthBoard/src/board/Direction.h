/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples repository.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once
#include <stdexcept>

/// A list of all possible directions in which we can move on the board
enum class Direction {
	Up,
	Right,
	Down,
	Left,
	First = Up,
	Last = Left
};

/// Increment a direction
///
/// Directions increment in the same order as they are listed in the enumeration:
/// Up -> Right -> Down -> Left
/// (i.e. in a clockwise manner)
///
/// @throws std::invalid_argument if you try to increment past the last of the named enumerators
/// defined for the enumeration (i.e. if you try to increment Left).
inline Direction& operator++(Direction& d)
{
	if (d == Direction::Last)
		throw std::invalid_argument("Cannot increment the enum to a value above its last member!");

	d = static_cast<Direction>(static_cast<int>(d) + 1);
	return d;
}

/// Helper class, which allows us to enumerate all directions (e.g. in a range-based for)
class AllDirections {
private:
	static Direction endValue()
	{
		return static_cast<Direction>(static_cast<int>(Direction::Last) + 1);
	}

public:
	/// @brief A constant iterator, which can be used to iterate all directions
	class ConstIterator {
		Direction value;

	public:
		ConstIterator(Direction value)
			: value(value)
		{
		}

		const Direction& operator*()
		{
			return value;
		}

		ConstIterator& operator++()
		{
			if (value == Direction::Last)
				value = endValue();
			else
				++value;

			return *this;
		}

		ConstIterator operator++(int)
		{
			ConstIterator temp = *this;
			++*this;
			return *this;
		}

		bool operator==(ConstIterator other)
		{
			return value == other.value;
		}

		bool operator!=(ConstIterator other)
		{
			return value != other.value;
		}
	};

public:
	ConstIterator begin() {
		return Direction::First;
	}

	ConstIterator end() {
		return endValue();
	}
};






