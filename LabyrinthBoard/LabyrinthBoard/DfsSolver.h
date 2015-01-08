#ifndef DFS_SOLVER_H
#define DFS_SOLVER_H

#include <stack>

#include "Solver.h"


class DfsSolver : public Solver
{
private:
	virtual bool PathExists_Internal(Board& board, Cell* pStart);
	void AddIfPassableAndNotVisited(std::stack<Cell*> & cellStack, Cell* pCell);
};


#endif // DFS_SOLVER_H