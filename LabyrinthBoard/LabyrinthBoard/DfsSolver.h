#ifndef DFS_SOLVER_H
#define DFS_SOLVER_H

#include <stack>

#include "Solver.h"


class DfsSolver : public Solver
{
public:
	virtual bool PathExists_Internal(Board& board, Cell* pStart);

private:
	void AddIfPassableAndNotVisited(std::stack<Cell*> & cellStack, Cell* pCell);
};


#endif // DFS_SOLVER_H