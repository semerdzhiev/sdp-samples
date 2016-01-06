/********************************************************************
 *
 * This file is part of the Data Structures in C++ Course Examples package.
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#include <iostream>

#include "Cell.h"

/**
 *
 *	Create a new cell object
 *
 */
Cell::Cell(Board* pBoard, char Symbol, int Row, int Col)
{
	this->pBoard = pBoard;
	this->Symbol = Symbol;
	this->Row = Row;
	this->Col = Col;
	this->Visited = false;
}


/**
 *
 *	Return the symbol associated with this cell
 *
 */
char Cell::GetSymbol() const
{
	return Symbol;
}


/**
 *
 *	Change the symbol associated with this cell
 *
 */
void Cell::SetSymbol(char c)
{
	Symbol = c;
}


/**
 *
 *	Returns true if you can pass through that cell
 *	when walking the albyrinth (e.g. corridor)
 *	or not (e.g. wall)
 *
 */
bool Cell::IsPassable() const
{
	return Symbol != '#';
}


/**
 *
 *	Returns true if this cell is a wall.
 *
 */
bool Cell::IsCorridor() const
{
	return Symbol == ' ';
}


/**
 *
 *	Returns true if this cell is a corridor.
 *
 */
bool Cell::IsWall() const
{
	return Symbol == '#';
}


/**
 *
 *	Returns true if this cell is the entrance of the labyrinth.
 *
 */
bool Cell::IsStart() const
{
	return Symbol == '^';
}


/**
 *
 *	Returns true if the cell is the target to find in the labyrinth
 *
 */
bool Cell::IsTarget() const
{
	return Symbol == '$';
}


/**
 *
 *	Returns the row on which this cell is located on the board.
 *
 */
int Cell::GetRow() const
{
	return this->Row;
}


/**
 *
 *	Returns the column on which this cell is located on the board.
 *
 */
int Cell::GetCol() const
{
	return this->Col;
}


/**
 *
 *	Marks the cell as visited when walking the labyrinth
 *
 */
void Cell::MarkVisited()
{
	Visited = true;
}


/**
 *
 *	Marks the cell as not visited when walking the labyrinth
 *
 */
void Cell::MarkNotVisited()
{
	Visited = false;
}


/**
 *
 *	Returns true if the cell has been visited when walking the labyrinth
 *
 */
bool Cell::IsVisited() const
{
	return Visited == true;
}


/**
 *
 *	Returns a pointer to the Board this Cell object is part of
 *
 */
const Board* Cell::GetBoard() const
{
	return pBoard;
}



/**
 *
 *	Returns the left neighbour of the cell, if such exists.
 *	Otherwise returns NULL.
 *
 */
Cell* Cell::GetLeftNeighbour() const
{
	return pBoard->GetCell(this->Row, this->Col - 1);
}


/**
 *
 *	Returns the right neighbour of the cell, if such exists.
 *	Otherwise returns NULL.
 *
 */
Cell* Cell::GetRightNeighbour() const
{
	return pBoard->GetCell(this->Row, this->Col + 1);
}


/**
 *
 *	Returns the top neighbour of the cell, if such exists.
 *	Otherwise returns NULL.
 *
 */
Cell* Cell::GetTopNeighbour() const
{
	return pBoard->GetCell(this->Row - 1, this->Col);
}


/**
 *
 *	Returns the bottom neighbour of the cell, if such exists.
 *	Otherwise returns NULL.
 *
 */
Cell* Cell::GetBottomNeighbour() const
{
	return pBoard->GetCell(this->Row + 1, this->Col);
}


/**
 *
 *	Displays information about the cell to STDOUT
 *
 */
void Cell::PrintInfo() const
{
	std::cout << "[ (" << Symbol
			  << ") r" << Row
			  << ", c" << Col
			  << ", " << (IsPassable() ? "passable" : "BLOCKED")
			  << ", " << (Visited ? "visited" : "NOT visited")
			  << "]";
}



/**
 *
 *	Specifies which Board object contains this Cell object
 *
 */
void Cell::SetBoard(Board* pBoard)
{
	this->pBoard = pBoard;
}