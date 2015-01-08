#ifndef BFS_SOLVER_H
#define BFS_SOLVER_H

#include <queue>

#include "Solver.h"


class BfsSolver : public Solver
{
private:
	virtual bool PathExists_Internal(Board& board, Cell* pStart);
	void AddIfPassableAndNotVisited(std::queue<Cell*> & cellQueue, Cell* pCell);
};


#endif // BFS_SOLVER_H