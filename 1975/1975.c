#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long
maxMatrixSum(int **matrix, int rows, int *cols)
{
	int totalnegatives = 0;
	int minabs = INT_MAX;
	long long sum = 0;

	for (int **row = matrix; row != matrix+rows; ++row) {
		for (int *cell = *row; cell != *row+cols[0]; ++cell) {
			sum += abs(*cell);

			if (*cell < 0)
				++totalnegatives;

			if (abs(*cell) < minabs)
				minabs = abs(*cell);
		}
	}

	if (totalnegatives%2 != 0)
		sum -= 2 * minabs;

	return sum;
}

void
example1(void)
{
	printf("1975.c:/example1/\n");

	int *arr[] = (int*[]){
		(int[]){1, -1},
		(int[]){-1, 1},
	};
	int cols[] = {2, 2};

	int sum = maxMatrixSum(arr, 2, cols);
	printf("sum: %d\n", sum); // 4
}

void
example2(void)
{
	printf("1975.c:/example2/\n");

	int *arr[] = (int*[]){
		(int[]){1, 2, 3},
		(int[]){-1, -2, -3},
		(int[]){1, 2, 3},
	};
	int cols[] = {3, 3, 3};

	int sum = maxMatrixSum(arr, 3, cols);
	printf("sum: %d\n", sum); // 16
}

void
wronganswer1(void)
{
	printf("1975.c:/wronganswer1/\n");

	int *arr[] = (int*[]){
		(int[]){-1, 0, -1},
		(int[]){-2, 1, 3},
		(int[]){3, 2, 2},
	};
	int cols[] = {3, 3, 3};

	int sum = maxMatrixSum(arr, 3, cols);
	printf("sum: %d\n", sum); // 15
}

void
wronganswer2(void)
{
	printf("1975.c:/wronganswer2/\n");

	int *arr[] = (int*[]){
		(int[]){-3, 0, 0},
		(int[]){0, 0, 0},
		(int[]){0, 3, 2},
	};
	int cols[] = {3, 3, 3};

	int sum = maxMatrixSum(arr, 3, cols);
	printf("sum: %d\n", sum); // 8
}

void
wronganswer3(void)
{
	printf("1975.c:/wronganswer3/\n");

	int *arr[] = (int*[]){
		(int[]){9, -3, -4},
		(int[]){-4, -1, -3},
		(int[]){-6, -3, -3},
	};
	int cols[] = {3, 3, 3};

	int sum = maxMatrixSum(arr, 3, cols);
	printf("sum: %d\n", sum); // 36
}

void
wronganswer4(void)
{
	printf("1975.c:/wronganswer4/\n");

	int *arr[] = (int*[]){
		(int[]){2, 9, 3},
		(int[]){5, 4, -4},
		(int[]){1, 7, 1},
	};
	int cols[] = {3, 3, 3};

	int sum = maxMatrixSum(arr, 3, cols);
	printf("sum: %d\n", sum); // 34
}

int
main(void)
{
	example1();
	example2();
	wronganswer1();
	wronganswer2();
	wronganswer3();
	wronganswer4();

	return 0;
}
