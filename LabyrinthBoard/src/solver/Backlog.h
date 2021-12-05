#pragma once

#include "board/BoardLib.h"

#include <stack>
#include <queue>

// The Backlog classes serve as an adapter over the std::stack and std::queue classes from STL.
// They are required, since the interfaces of those two classes have small differences and
// this prevents us from using them in the Solver class template.

/// A backlog, which uses a stack to store its data
class StackBacklog {
	std::stack<Board::Coordinates> data;
public:
	void add(Board::Coordinates c)
	{
		data.push(c);
	}

	Board::Coordinates pop()
	{
		Board::Coordinates result = data.top();
		data.pop();
		return result;
	}

	bool notEmpty() const
	{
		return !data.empty();
	}

	size_t size() const
	{
		return data.size();
	}
};

/// A backlog, which uses a queue to store its data
class QueueBacklog {
	std::queue<Board::Coordinates> data;
public:
	void add(Board::Coordinates c)
	{
		data.push(c);
	}

	Board::Coordinates pop()
	{
		Board::Coordinates result = data.front();
		data.pop();
		return result;
	}

	bool notEmpty() const
	{
		return !data.empty();
	}

	size_t size() const
	{
		return data.size();
	}
};

