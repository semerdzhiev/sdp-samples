/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <exception>
#include "Box.h"

///
/// Creates an empty box
///
Box::Box()
{
	Clear();
}


///
/// Crates a box and stores Value within it
///
Box::Box(double Value)
{
	Add(Value);
}


///
/// Stores Value within the box
///
void Box::Add(double Value)
{
	Contents = Value;
	Empty = false;
}


///
/// Retrieves the value stored within the box
///
/// If the box is empty, the function throws a
/// std::exception object.
///
double Box::Peek() const
{
	if (!Empty)
		return Contents;
	else
		throw std::exception();
}


///
/// Empties the box
///
void Box::Clear()
{
	Contents = 0.0;
	Empty = true;
}


///
/// Checks whether the box is empty
///
bool Box::IsEmpty() const
{
	return Empty;
}

