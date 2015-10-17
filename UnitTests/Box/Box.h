/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

///
/// A box, which can store a single item - a rational number
///
class Box
{
public:
	Box();
	Box(double Value);
	void Add(double Value);
	double Peek() const;
	void Clear();
	bool IsEmpty() const;

private:
	double Contents;
	bool Empty;
};

