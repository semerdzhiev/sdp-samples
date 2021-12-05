/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */
#pragma once

class Cell
{
public:
	enum class Type {
		Corridor,
		Wall,
		Target,
		Start
	};

private:
	/// Type of the cell
	Type m_type = Type::Corridor;
	
	/// Specifies whether the cell has been visited or not
	bool m_visited = false;

public:
	Cell() = default;

	Cell(Type type, bool isVisited = false)
		: m_type(type), m_visited(isVisited)
	{}

	bool isPassable() const noexcept
	{
		return m_type != Type::Wall;
	}

	bool isTarget() const noexcept
	{
		return m_type == Type::Target;
	}

	Type& type() noexcept
	{
		return m_type;
	}

	const Type& type() const noexcept
	{
		return m_type;
	}

	void markVisited() noexcept
	{
		m_visited = true;
	}

	void markNotVisited() noexcept
	{
		m_visited = false;
	}

	bool isVisited() const noexcept
	{
		return m_visited;
	}
};