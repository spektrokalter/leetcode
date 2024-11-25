#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

bool seenmem[6][6][6][6][6][6];
int movesmem[6][6][6][6][6][6];

int dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

bool *
seen(int **b)
{
	return &seenmem[b[0][0]][b[0][1]][b[0][2]][b[1][0]][b[1][1]][b[1][2]];
}

int *
moves(int **b)
{
	return &movesmem[b[0][0]][b[0][1]][b[0][2]][b[1][0]][b[1][1]][b[1][2]];
}

void
dfs(int **b, int movesdone)
{
	if (*seen(b) || *moves(b) && movesdone >= *moves(b))
		return;

	*seen(b) = true;
	*moves(b) = movesdone + 1;

	int i, j;

	for (int k = 0; k < 2; ++k) {
		for (int l = 0; l < 3; ++l) {
			if (b[k][l] == 0) {
				i = k;
				j = l;
			}
		}
	}

	for (int (*dir)[2] = dirs; dir != dirs+ARRAY_LEN(dirs); ++dir) {
		int ii = i + (*dir)[0], jj = j + (*dir)[1];
		if (ii < 0 || ii >= 2 || jj < 0 || jj >= 3)
			continue;

		int *src = &b[i][j], *dst = &b[ii][jj];
		int tmp = *src; *src = *dst; *dst = tmp;

		dfs(b, movesdone+1);

		tmp = *src; *src = *dst; *dst = tmp;
	}

	*seen(b) = false;
}

int
slidingPuzzle(int **board, int rows, int *cols)
{
	memset(seenmem, 0, sizeof(seenmem));
	memset(movesmem, 0, sizeof(movesmem));

	dfs(board, 0);

	return movesmem[1][2][3][4][5][0] - 1;
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
