#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))
#define MAX(x, y) ((x)>(y) ? (x) : (y))
#define NMEM 100001

int (*mem[NMEM])[2];

void
arrprint
	(int *p, int len)
{
	for (int *q = p; q != p+len; ++q)
		printf("	%d", *q);

	printf("\n");
}

void
arr2print
	(int **p, int rows, int cols)
{
	for (int **q = p; q != p+rows; ++q) {
		for (int *r = *q; r != *q+cols; ++r)
			printf(" %d", *r);

		printf(" |");
	}

	printf("\n");
}

int
cmpitems(const void *vp1, const void *vp2)
{
	int *x = *(int **)vp1;
	int *y = *(int **)vp2;

	if (x[0] < y[0])
		return -1;
	else if (x[0] > y[0])
		return 1;
	else if (x[1] < y[1])
		return -1;
	else if (x[1] > y[1])
		return 1;
	else
		return 0;
}

int *
maximumBeauty(int **items, int nitems, int *mitems, int *queries, int nqueries, int *nanswer)
{
	memset(mem, 0, sizeof(mem));

	qsort(items, nitems, sizeof(*items), cmpitems);
//	arr2print(items, nitems, 2);

	int *answer;
	answer = calloc(nqueries, sizeof(*answer));

	int *ap = answer;

	for (int *qp = queries; qp != queries+nqueries; ++qp) {
		int (*bucket)[2] = mem[*qp%NMEM];
		if (bucket) {
			for (int (*bp)[2] = bucket; *bp; ++bp) {
//				printf("FOO\n");
				if ((*bp)[0] == *qp) {
					*(ap++) = (*bp)[1];
					goto nextquery;
				}
			}
		}

		// i is the smallest items[i] at which items[i][0] > *qp
		int i = 0, j = nitems;
		while (i < j) {
			int h = (i + j) / 2;
			if (!(items[h][0] > *qp))
				i = h + 1;
			else
				j = h;
		}

		int beauty = 0;

		int **ip = items + i - 1;
		for (int j = i - 1; j >= 0; --j, --ip) {
			int (*bucket)[2] = mem[(*ip)[0]%NMEM];
			if (bucket) {
				for (int (*bp)[2] = bucket; *bp; ++bp) {
//					printf("BAR\n");
					if ((*bp)[0] == (*ip)[0]) {
						beauty = MAX(beauty, (*bp)[1]);
						goto catchbeauty;
					}
				}
			}

			beauty = MAX(beauty, (*ip)[1]);
		}

	catchbeauty:

		bucket = mem[*qp%NMEM];
		if (!bucket)
			bucket = mem[*qp%NMEM] = calloc(10, sizeof(*bucket));
		int (*bp)[2] = bucket;
		while ((*bp)[0]) {
//			printf("BAZ\n");
			++bp;
		}
		(*bp)[0] = *qp;
		(*bp)[1] = beauty;

		*(ap++) = beauty;

	nextquery:
		;
	}

	*nanswer = nqueries;
	return answer;
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
	int items[][2] = {{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}};
	int queries[] = {1, 2, 3, 4, 5, 6};
	int nanswer = 0;

	int **itemsp = mkarr(items, ARRAY_LEN(items), 2);

	int *answer = maximumBeauty(itemsp, ARRAY_LEN(items), NULL, queries, ARRAY_LEN(queries), &nanswer);

	printf("2070.c:/example1/\n");
	arrprint(answer, nanswer); // 2, 4, 5, 5, 6, 6
}

void
example2(void)
{
	int items[][2] = {{1, 2}, {1, 2}, {1, 3}, {1, 4}};
	int queries[] = {1};
	int nanswer = 0;

	int **itemsp = mkarr(items, ARRAY_LEN(items), 2);

	int *answer = maximumBeauty(itemsp, ARRAY_LEN(items), NULL, queries, ARRAY_LEN(queries), &nanswer);

	printf("2070.c:/example2/\n");
	arrprint(answer, nanswer); // 4
}

void
example3(void)
{
	int items[][2] = {{10, 1000}};
	int queries[] = {5};
	int nanswer = 0;

	int **itemsp = mkarr(items, ARRAY_LEN(items), 2);

	int *answer = maximumBeauty(itemsp, ARRAY_LEN(items), NULL, queries, ARRAY_LEN(queries), &nanswer);

	printf("2070.c:/example3/\n");
	arrprint(answer, nanswer); // 0
}

int
main(void)
{
	example1();
	example2();
	example3();

	return 0;
}
