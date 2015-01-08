#ifndef BFS_SOLVER_H
#define BFS_SOLVER_H

#include <queue>

#include "Solver.h"


class BfsSolver : public Solver
{
public:
	virtual bool PathExists_Internal(Board& board, Cell* pStart);

private:
	void AddIfPassableAndNotVisited(std::queue<Cell*> & cellQueue, Cell* pCell);
};


#endif // BFS_SOLVER_H