/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <queue>

#include "Solver.h"


class BfsSolver : public Solver
{
private:
	virtual bool PathExists_Internal(Board& board, Cell* pStart);
	void AddIfPassableAndNotVisited(std::queue<Cell*> & cellQueue, Cell* pCell);
};