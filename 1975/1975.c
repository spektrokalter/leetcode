#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long
maxMatrixSum(int **matrix, int rows, int *cols)
{
	int totalnegatives = 0;
	int maxnegative = INT_MIN;
	int found = false;
	int sum = 0;

	for (int **row = matrix; row != matrix+rows; ++row) {
		for (int *cell = *row; cell != *row+cols[0]; ++cell) {
			sum += abs(*cell);

			if (*cell < 0)
				++totalnegatives;

			if (*cell < 0 && *cell > maxnegative) {
				if (found)
					sum += -maxnegative;

				maxnegative = *cell;
				sum -= 2 * abs(*cell);
				found = true;
			}
		}
	}

	if (totalnegatives%2 == 0)
		sum += 2 * abs(maxnegative);

	return sum;
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
	printf("1975.c:/example1/\n");

	int arr[][2] = {
		{1, -1},
		{-1, 1},
	};
	int cols[] = {2, 2};

	int sum = maxMatrixSum(mkarr(arr, 2, 2), 2, cols);
	printf("sum: %d\n", sum); // 4
}

void
example2(void)
{
	printf("1975.c:/example2/\n");

	int arr[][3] = {
		{1, 2, 3},
		{-1, -2, -3},
		{1, 2, 3},
	};
	int cols[] = {3, 3, 3};

	int sum = maxMatrixSum(mkarr(arr, 3, 3), 3, cols);
	printf("sum: %d\n", sum); // 16
}

void
wronganswer1(void)
{
	printf("1975.c:/wronganswer1/\n");

	int arr[][3] = {
		{-1, 0, -1},
		{-2, 1, 3},
		{3, 2, 2},
	};
	int cols[] = {3, 3, 3};

	int sum = maxMatrixSum(mkarr(arr, 3, 3), 3, cols);
	printf("sum: %d\n", sum); // 15
}

int
main(void)
{
	example1();
	example2();
	wronganswer1();

	return 0;
}
