/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include "Cell.h"
#include "Board.h"


class Solver
{
public:
	virtual ~Solver();

public:
	bool PathExists(Board& board);

protected:
	virtual bool PathExists_Internal(Board& board, Cell* pStart) = 0;
};