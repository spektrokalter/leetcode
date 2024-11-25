#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))
#define NDICT 100001

struct entry
{
	const char *key;
	int val;
	struct entry *next;
};
typedef struct entry Entry;

Entry *seenmem[NDICT];
Entry *movesmem[NDICT];

Entry *
entrymk(const char *key, int val)
{
	Entry *e;
	e = calloc(1, sizeof(*e));

	e->key = strdup(key);
	e->val = val;

	return e;
}

int
dicthash(char *key)
{
	int h = 0;

	for (char *p = key; *p; ++p)
		h = 31*h + *p;

	return h % NDICT;
}

Entry **
lookupseen(char *key)
{
	Entry **e = &seenmem[dicthash(key)];

	while (*e != NULL) {
		if (strcmp((*e)->key, key) == 0)
			return e;

		e = &(*e)->next;
	}

	return e;
}

Entry **
lookupmoves(char *key)
{
	Entry **e = &movesmem[dicthash(key)];

	while (*e != NULL) {
		if (strcmp((*e)->key, key) == 0)
			return e;

		e = &(*e)->next;
	}

	return e;
}

int dirs[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

void
mkkey(char *key, int **board)
{
	*(key++) = '0' + board[0][0];
	*(key++) = '0' + board[0][1];
	*(key++) = '0' + board[0][2];
	*(key++) = '0' + board[1][0];
	*(key++) = '0' + board[1][1];
	*(key++) = '0' + board[1][2];
	*(key++) = 0;
}

void
dfs(int **board, int movesdone)
{
	char key[7] = {0};
	mkkey(key, board);

	Entry **seen = lookupseen(key);
	if (*seen == NULL)
		*seen = entrymk(key, 0);

	Entry **moves = lookupmoves(key);
	if (*moves == NULL)
		*moves = entrymk(key, 0);

	if ((*seen)->val || (*moves)->val && movesdone >= (*moves)->val)
		return;

	(*seen)->val = 1;
	(*moves)->val = movesdone + 1;

	int i, j;

	for (int k = 0; k < 2; ++k) {
		for (int l = 0; l < 3; ++l) {
			if (board[k][l] == 0) {
				i = k;
				j = l;
			}
		}
	}

	for (int (*dir)[2] = dirs; dir != dirs+ARRAY_LEN(dirs); ++dir) {
		int ii = i + (*dir)[0], jj = j + (*dir)[1];
		if (ii < 0 || ii >= 2 || jj < 0 || jj >= 3)
			continue;

		int *src = &board[i][j], *dst = &board[ii][jj];
		int tmp = *src; *src = *dst; *dst = tmp;

		dfs(board, movesdone+1);

		tmp = *src; *src = *dst; *dst = tmp;
	}

	(*seen)->val = 0;
}

int
slidingPuzzle(int **board, int rows, int *cols)
{
	memset(seenmem, 0, sizeof(seenmem));
	memset(movesmem, 0, sizeof(movesmem));

	dfs(board, 0);

	Entry *e = *lookupmoves("123450");
	if (e == NULL)
		return -1;
	else
		return e->val - 1;
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
