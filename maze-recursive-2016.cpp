#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <time.h>

using namespace std;

const unsigned int MAXS = 6;
const char WALL = -1;
const char FREE = 0;
const char VSTD = 1;

unsigned int cnt = 0;


const int COEFF = 30;

char maze[MAXS][MAXS];

void init() {
    for (size_t i=0; i<  MAXS; i++)
        for (size_t j=0; j< MAXS; j++)
            maze[i][j] = rand() % 100 < COEFF ? WALL : FREE;
}

void print(int row, int col) {
    printf("\n [%d] current state at [%d, %d] \n ------------- \n", cnt, row, col);
    for (size_t i=0; i<  MAXS; i++) {
        printf("\n");
        for (size_t j=0; j< MAXS; j++) 
            switch(maze[i][j]) {
                case WALL: printf("%2c", '#'); break;
                case FREE: printf("%2c", 'O'); break;
                case VSTD: printf("%2c", '0'); break;
            }
    }
    printf("\n");
}


// possible directions 
char dir[][2] = {
    { 1,  0},
    { 0,  1},
    { -1, 0},
    { 0, -1}
};

bool rec(int row, int col) {
    cnt ++;
    // sanity checks
    if (row < 0 || col < 0 || row >= MAXS || col >= MAXS) return false;
    if ((maze[row][col] == WALL) || (maze[row][col] == VSTD)) return false;

    // denote we are in the current state
    maze[row][col] = VSTD;
    // print state
    print(row, col);

    // goal (end of recursion) check
    if (row == MAXS - 1 && col == MAXS -1) return true;

    // recursion step
    for (size_t i = 0; i < sizeof(dir) / sizeof(dir[0]); i++) {
        if (rec(row + dir[i][0], col + dir[i][1])) return true;
    }
    // denote we are no more in this staet
    maze[row][col] = FREE;

    return false;
}

int main() {
    srand(time(NULL));
    init();

    if( rec(0, 0) ) {
        printf("\n path was found! \n");
    } else {
        printf("\n no path found! \n");
    };

    return -1;
}
