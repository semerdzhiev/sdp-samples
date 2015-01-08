#include <assert.h>
#include <iostream>
#include <fstream>

#include "Board.h"


/**
 *
 *	Allocates a new two-dimensional array of cells.
 *
 *	The new board must be freed with a call to FreeBoard().
 *
 *	\param [in] RowsCount
 *		The number of rows in the board
 *
 *	\param [in] ColsCount
 *		The number of columns in the board
 *
 *	\return
 *		A pointer to the newly allocated board or
 *		NULL if the function fails.
 *
 */
Cell** Board::AllocateNewBoard(int RowsCount, int ColsCount)
{
	Cell **ppNewBoard = NULL;

	try
	{
		ppNewBoard = new Cell*[RowsCount];

		for (int row = 0; row < RowsCount; row++)
		{
			ppNewBoard[row] = NULL;
		}

		for (int row = 0; row < RowsCount; row++)
		{
			ppNewBoard[row] = new Cell[ColsCount];
		}
	}
	catch (std::bad_alloc&)
	{
		FreeBoard(ppNewBoard, RowsCount);
	}

	// If the board was allocated, set the current object as an owner
	if(ppNewBoard)
	{
		SetAsOwnerFor(ppNewBoard, RowsCount, ColsCount);
	}

	return ppNewBoard;
}


/**
 *
 *	Frees the memory occupied by a board
 *
 *	\param [in]
 *		A pointer to the board to free.
 *
 *	\param [in]
 *		The number of rows in the board.
 *
 */
void Board::FreeBoard(Cell**& ppBoard, int RowsCount)
{
	if (!ppBoard)
		return;

	for(int row = 0; row < RowsCount; row++)
	{
		delete [] ppBoard[row];
	}

	delete[] ppBoard;

	ppBoard = NULL;
}


/**
 *
 *	Clones an already allocated board.
 *
 *	The function allocates the required memory for the new board
 *	and copies the contents of the old one to it.
 *
 *	The new board must be freed with a call to FreeBoard().
 *
 *	\param [in] ppBoard
 *		A pointer to the board to clone
 *		
 *	\param [in] RowsCount
 *		The number of rows in the board.
 *
 *	\param [in] ColsCount
 *		The number of columns in the board.
 *		
 *	\return
 *		A pointer to the cloned board or NULL if the function fails
 *
 */
Cell** Board::DuplicateBoard(const Cell** ppBoard, int RowsCount, int ColsCount)
{
	Cell** ppNewBoard = AllocateNewBoard(RowsCount, ColsCount);
	
	if(ppNewBoard)
	{
		for(int row = 0; row < RowsCount; row++)
		{
			for(int col = 0; col < ColsCount; col++)
			{
				ppNewBoard[row][col] = ppBoard[row][col];
				ppNewBoard[row][col].SetBoard(this);
			}
		}
	}

	return ppNewBoard;
}


/**
 *
 *	Clones the board data from another object
 *
 *	\param [in] board
 *		A board object to copy from
 *
 */
Cell** Board::DuplicateBoard(const Board & board)
{
	return DuplicateBoard(const_cast<const Cell**>(board.ppBoard), board.GetRowsCount(), board.GetColsCount());
}


/**
 *
 *	Sets the current object as an owner for all cells in a board
 *
 *	\param [in] ppBoard
 *		A pointer to the board to own.
 *		
 *	\param [in] RowsCount
 *		The number of rows in the board.
 *
 *	\param [in] ColsCount
 *		The number of columns in the board.
 *
 */
void Board::SetAsOwnerFor(Cell** ppOtherBoard, int RowsCount, int ColsCount)
{
	for(int row = 0; row < RowsCount; row++)
	{
		for(int col = 0; col < ColsCount; col++)
		{
			ppOtherBoard[row][col].SetBoard(this);
		}
	}
}


/**
 *
 *	Creates an empty board
 *
 */
Board::Board()
{
	ppBoard = NULL;
	ColsCount = 0;
	RowsCount = 0;
}


/**
 *
 * Creates a new board and copies its contents from another.	
 *
 */
Board::Board(const Board & board)
{
	ppBoard = DuplicateBoard(board);
}


/**
 *
 *	Frees the resources occupied by the object.
 *
 */
Board::~Board()
{
	FreeBoard(ppBoard, RowsCount);
}


/**
 *
 *	Copies the contents of one board to another.
 *
 */
Board & Board::operator=(Board const & board)
{
	if(this != &board)
	{
		Cell ** ppNewBoard = DuplicateBoard(board);

		if(ppNewBoard)
		{
			FreeBoard(ppBoard, RowsCount);
			ppBoard = ppNewBoard;
			RowsCount = board.RowsCount;
			ColsCount = board.ColsCount;
		}
	}

	return *this;
}


/**
 *
 *	Returns the number of rows in the board
 *
 */
int Board::GetRowsCount() const
{
	return RowsCount;
}


/**
 *
 *	Returns the number of columns in the board
 *
 */
int Board::GetColsCount() const
{
	return ColsCount;
}


/**
 *
 *	Loads the contents of a board from a text file.
 *
 *	\param [in] Filename
 *		Path to the file to read from.
 *		
 *	\return
 *		true if the function succeeds or false otherwise.
 *
 */
bool Board::LoadFromFile(const char* Filename)
{
	std::ifstream InputFile(Filename);

	if( ! InputFile)
	{
		return false;
	}

	int Rows = 0;
	int Cols = 0;

	if( ! GetBoardDimensionsFromFile(InputFile, Rows, Cols))
	{
		return false;
	}

	Cell ** ppNewBoard = AllocateNewBoard(Rows, Cols);

	if( ! ppNewBoard)
	{
		return false;
	}

	ReadBoardFromFile(InputFile, ppNewBoard);

	ppBoard = ppNewBoard;
	RowsCount = Rows;
	ColsCount = Cols;

	return true;
}


/**
 *
 *	Determines what are the dimensions of a labyrinth stored in a file.
 *
 *	\param [in] InputFile
 *		The file to read data from
 *
 *	\param [out] RowsCount
 *		A variable which will receive the numbe of rows in the labyrinth.
 *		The variable will be altered only if the file contains valid data.
 *
 *	\param [out] ColsCount
 *		A variable which will receive the numbe of columns in the labyrinth.
 *		The variable will be altered only if the file contains valid data.
 *
 *	\return
 *		true if the file contains valid data and the dimensions were written
 *		to RowsCount and ColsCount. Otherwise the function returns false.
 *
 */
bool Board::GetBoardDimensionsFromFile(std::ifstream & InputFile, int& RowsCount, int& ColsCount)
{
	InputFile.clear();
	InputFile.seekg(0, std::ios::beg);

	int rows = 0; // Number of rows in the board
	int cols = 0; // Number of columns in the board

	char c = 0;
	int counter = 0;
		
	// Find the number of columns in the board
	while (InputFile.get(c) && c != '\n')
		cols++;


	// Find the number of rows in the board and also
	// verify that all rows have the same number of columns
	if (cols > 0)
	{
		rows++; // at leas one row was read from the file

		while (InputFile.get(c))
		{
			if (c == '\n')
			{
				// the number of columns on each line must be the same
				if (cols != counter)
					return false;

				rows++;
				counter = 0;
			}
			else
			{
				counter++;
			}
		}

		// The last row of the labyrinth may or may not be followed by a blank line
		// Thus if we just count the number of new lines, we may count one row less
		if (c != '\n')
			rows++;
	}

	RowsCount = rows;
	ColsCount = cols;

	return true;
	/*
	while(InputFile.get(c))
	{
		if(c == '\n')
		{
			if(rows == 0)
			{
				cols = counter;
			}
			else if(cols != counter)
			{
				return false;
			}

			rows++;
			counter = 0;
		}
		else
		{
			counter++;
		}
	}

	RowsCount = rows;
	ColsCount = cols;

	return true;
	*/
}


/**
 *
 *	Reads labyrinth data from InputFile and stores it in ppBoard.
 *
 *	The function assumes that the file contains valid data and
 *	ppBoard was alloated with the necessary dimensions.
 *
 */
void Board::ReadBoardFromFile(std::ifstream & InputFile, Cell ** ppBoard)
{
	InputFile.clear();
	InputFile.seekg(0, std::ios::beg);

	int row = 0;
	int col = 0;
	char c;

	while(InputFile.get(c))
	{
		if(c == '\n')
		{
			row++;
			col = 0;
		}
		else
		{
			ppBoard[row][col] = Cell(this, c, row, col);
			col++;
		}
	}
}


/**
 *
 *	Returns a pointer to the cell on row Row and column Col.
 *
 *	If there is no such cell in the labyrinth, the function
 *	returns NULL.
 *
 */
Cell* Board::GetCell(int Row, int Col) const
{
	if(	Row >= 0 && Row < RowsCount &&
		Col >= 0 && Col < ColsCount)
	{
		return &ppBoard[Row][Col];
	}
	else
	{
		return NULL;
	}	
}


/**
 *
 *	Returns the starting cell in the labyrinth or NULL
 *	if there is no such cell.
 *
 */
Cell* Board::GetStart() const
{
	for(int row = 0; row < RowsCount; row++)
	{
		for(int col = 0; col < ColsCount; col++)
		{
			if(ppBoard[row][col].IsStart())
			{
				return &ppBoard[row][col];
			}
		}
	}

	return NULL;
}


/**
 *
 *	Print the board to STDOUT
 *
 */
void Board::Print() const
{
	for(int row = 0; row < RowsCount; row++)
	{
		for(int col = 0; col < ColsCount; col++)
		{
			std::cout << ppBoard[row][col].GetSymbol();
		}

		std::cout << std::endl;
	}

	std::cout << "(" << RowsCount << " rows, " << ColsCount << " columns)\n";
}


/**
 *
 *	Mark all cells in the board as not visited.
 *
 */
void Board::MarkAllCellsNotVisited()
{
	for(int row = 0; row < RowsCount; row++)
	{
		for(int col = 0; col < ColsCount; col++)
		{
			ppBoard[row][col].MarkNotVisited();
		}
	}

}