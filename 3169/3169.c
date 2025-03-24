#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

#define MAX(x, y) ((x)>(y) ? (x) : (y))
#define MIN(x, y) ((x)<(y) ? (x) : (y))

int
cmpinterval(const void *vp1, const void *vp2)
{
	const int *x = *(const int **)vp1;
	const int *y = *(const int **)vp2;

	if (x[0] != y[0])
		return (x[0] > y[0]) - (x[0] < y[0]);
	else
		return (x[1] > y[1]) - (x[1] < y[1]);
}

int
countDays(int days, int **meetings, int nmeetings, int *nnmeetings)
{
	qsort(meetings, nmeetings, sizeof(*meetings), cmpinterval);

	int prev0 = 0, prev1 = 0;

	// max1, in the beginning of each iteration, represents
	// max(meetings[][1]) of the previous iteration.
	//
	int max1 = 0;

	int busy = 0;

	for (int **m = meetings; m != meetings+nmeetings; ++m) {

		// ((1, 10) m=(5, 15)) or ((1, 10) m=(2, 8))
		// else: ((1, 10) m=(20, 30))
		//
		if ((*m)[0] <= prev1) {

			// ((1, 10) m=(5, 15))
			//
			if ((*m)[1] > max1)
				busy += (*m)[1] - max1;

			max1 = MAX(max1, (*m)[1]);
		} else {
			busy += (*m)[1] - (*m)[0] + 1;
			max1 = (*m)[1];
		}
		printf("%d\n", busy);

		prev0 = (*m)[0];
		prev1 = (*m)[1];
	}

	return days - busy;
}

int **
mkarr(void *vp, int nrows, int ncols)
{
	int (*arr)[ncols] = vp;

	int **p;
	p = calloc(nrows, sizeof(*p));

	int (*arrp)[ncols] = arr;
	for (int **pp = p; pp != p+nrows; ++pp) {
		*pp = calloc(ncols, sizeof(**pp));
		memcpy(*pp, *arrp, ncols * sizeof(**pp));
		++arrp;
	}

	return p;
}

void
example1(void)
{
	int meetings[][2] = {{5, 7}, {1, 3}, {9, 10}};
	int **meetingsmem = mkarr(meetings, ARRAY_LEN(meetings), 2);

	int available = countDays(10, meetingsmem, ARRAY_LEN(meetings), NULL);
	printf("3169.c:/^example1/	%d\n", available); // 2
}

void
example2(void)
{
	int meetings[][2] = {{2, 4}, {1, 3}};
	int **meetingsmem = mkarr(meetings, ARRAY_LEN(meetings), 2);

	int available = countDays(5, meetingsmem, ARRAY_LEN(meetings), NULL);
	printf("3169.c:/^example2/	%d\n", available); // 1
}

void
example3(void)
{
	int meetings[][2] = {{1, 6}};
	int **meetingsmem = mkarr(meetings, ARRAY_LEN(meetings), 2);

	int available = countDays(6, meetingsmem, ARRAY_LEN(meetings), NULL);
	printf("3169.c:/^example3/	%d\n", available); // 0
}

int
main(void)
{
	example1();
	example2();
	example3();

	return 0;
}
