#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))
#define MIN(x, y) ((x)<(y) ? (x) : (y))

int mem[6][6][6][6][6][6];

int dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

bool
solved(int **board)
{
	return board[0][0] == 1 &&
		board[0][1] == 2 &&
		board[0][2] == 3 &&
		board[1][0] == 4 &&
		board[1][1] == 5 &&
		board[1][2] == 0;
}

int
dfs(int **b)
{
	int *moves = &mem[b[0][0]][b[0][1]][b[0][2]][b[1][0]][b[1][1]][b[1][2]];

	// backtracking protection
	if (*moves == -2)
		return INT_MAX;

	if (*moves)
		return *moves - 1;

	if (solved(b)) {
		*moves = 1;
		return 0;
	}

	// backtracking protection
	*moves = -2;

	int i, j;

	for (int k = 0; k < 2; ++k) {
		for (int l = 0; l < 3; ++l) {
			if (b[k][l] == 0) {
				i = k;
				j = l;
			}
		}
	}

	int deepmoves = INT_MAX - 1;

	for (int (*dir)[2] = dirs; dir != dirs+ARRAY_LEN(dirs); ++dir) {
		int ii = i + (*dir)[0], jj = j + (*dir)[1];
		if (ii < 0 || ii >= 2 || jj < 0 || jj >= 3)
			continue;

		int *src = &b[i][j], *dst = &b[ii][jj];
		int tmp = *src; *src = *dst; *dst = tmp;

		int x = dfs(b);
		deepmoves = MIN(deepmoves, x);

		tmp = *src; *src = *dst; *dst = tmp;
	}

	*moves = deepmoves + 1;
	return *moves;
}

int
slidingPuzzle(int **board, int rows, int *cols)
{
	memset(mem, 0, sizeof(mem));

	int moves = dfs(board);
	if (moves == INT_MAX)
		return -1;

	return moves;
}

int **
mkarr
	(void *vp, int nrows, int ncols)
{
	int (*arr)[ncols] = vp;

	int **p;
	p = calloc(nrows, sizeof(*p));

	int (*r)[ncols] = arr;
	for (int **q = p; q != p+nrows; ++q) {
		*q = calloc(ncols, sizeof(**q));
		memcpy(*q, *r, ncols * sizeof(**q));
		++r;
	}

	return p;
}

void
example1(void)
{
	printf("773.c:/example1/\n");
	int arr[][3] = {{1, 2, 3}, {4, 0, 5}};
	int cols[] = {3, 3};

	int moves = slidingPuzzle(mkarr(arr, 2, 3), 2, cols);
	printf("moves: %d\n", moves); // 1
}

void
example2(void)
{
	printf("773.c:/example2/\n");
	int arr[][3] = {{1, 2, 3}, {5, 4, 0}};
	int cols[] = {3, 3};

	int moves = slidingPuzzle(mkarr(arr, 2, 3), 2, cols);
	printf("moves: %d\n", moves); // -1
}

void
example3(void)
{
	printf("773.c:/example3/\n");
	int arr[][3] = {{4, 1, 2}, {5, 0, 3}};
	int cols[] = {3, 3};

	int moves = slidingPuzzle(mkarr(arr, 2, 3), 2, cols);
	printf("moves: %d\n", moves); // 5
}

void
wronganswer1(void)
{
	printf("773.c:/wronganswer1/\n");
	int arr[][3] = {{3, 2, 4}, {1, 5, 0}};
	int cols[] = {3, 3};

	int moves = slidingPuzzle(mkarr(arr, 2, 3), 2, cols);
	printf("moves: %d\n", moves); // 14
}

int
main(void)
{
	example1();
	example2();
	example3();
	wronganswer1();

	return 0;
}
