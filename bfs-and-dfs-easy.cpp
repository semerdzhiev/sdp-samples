// dfs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>

#define DEBUG 

const size_t ROWS = 16;
const size_t COLS = 16;

typedef unsigned short int mtype;

mtype maze[ROWS][COLS];
mtype rate = 16;

// directions we can move to

char dir[][3] = {
	{ 1, 0, '>' },
	{ 0, -1, '^'},
	{ -1, 0, '<' },
	{ 0, 1, 'v' }
};

/* maze values mean  :

	0	- can go here
	1	- blocked
	2	- visited

*/

// printer visitor
// assumes is called in sequential fasion
// with respect to row/col

void printer(int row, int col) {
	if (!col) printf("\n");
	printf("%c", maze[row][col] ? maze[row][col] : '0');
	if (row == ROWS - 1 && col == COLS - 1)
		printf("\n");
}


// randomizer visitor

void randomizr(int row, int col) {
	if ( !(row + col) ) srand(time(NULL));
	maze[row][col] = ((rand() % 100) < rate) * '*';
}

// iterator
// visits all nodes and calls the f(int, int) function
void miter(void(*f)(int, int)) {
	for (auto i = 0; i < ROWS; i++) {
		for (auto j = 0; j < COLS; j++) {
			f(i, j);
		}
	}
}

/* 
	row, cow = where are we
	trow, tcow = where would we like to get to

*/
int cnt = 0;

bool dfs(mtype row, mtype col, mtype trow, mtype tcol) {
	cnt++;
#ifdef DEBUG
	if (cnt % 128 == 0 )	miter(printer);
#endif
	if (maze[row][col]) return false;
	if (row == trow && col == tcol) return true;

	// for each direction..
	for (auto d: dir) {
		// ...calculate the new position..
		auto ncol = col + d[0];
		auto nrow = row + d[1];
		
		// ..and we can ACTUALLY go there
		if (ncol < COLS && ncol >= 0 && nrow < ROWS && nrow >= 0 ) {
			maze[row][col] = d[2];	// show which direction did I take to
			if (dfs(nrow, ncol, trow, tcol)) 
				return true;
		}
		maze[row][col] = 0;
	}

	maze[row][col] = 'X';
	return false;
}

#include <queue>
#include <tuple>

using namespace std;

typedef tuple<mtype, mtype> mtuple;

bool bfs(mtype row, mtype col, mtype trow, mtype tcol) {
	queue<mtuple> wave;
	mtuple cpos;

	wave.push(mtuple(row, col));

	while (wave.size()) {
		cnt++;
#ifdef DEBUG
		if (cnt % 128 == 0)	miter(printer);
#endif
		cpos = wave.front();
		wave.pop();

		if (get<0>(cpos) == tcol && get<1>(cpos) == trow) {
			return true;
		}

		for (auto d : dir) {
			// ...calculate the new position..
			auto ncol = get<0>(cpos) + d[0];
			auto nrow = get<1>(cpos) + d[1];

			// ..and we can ACTUALLY go there
			if (ncol < COLS && ncol >= 0 && nrow < ROWS && nrow >= 0 && !maze[nrow][ncol]) {
				maze[nrow][ncol] = 'W';
				wave.push(mtuple(nrow, ncol));
			}
		}
	}
}

int main() {
	miter(randomizr);

	if (bfs(0, 0, ROWS - 1, COLS - 1)) {
		miter(printer);
		printf("bfs found a route in %d iterations!", cnt);
	}
	else {
		miter(printer);
		printf("bfs DID NOT find a route!");
	}

	return 0;
}

