#ifndef SOLVER_H
#define SOLVER_H

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


#endif // SOLVER_H