#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))
#define MAX(x, y) ((x)>(y) ? (x) : (y))
#define NMEM 100001

struct entry
{
	int key, val;
	struct entry *next;
};
typedef struct entry Entry;

Entry *dict[NMEM];

Entry *
entryMake(int key, int val)
{
	Entry *e;
	e = calloc(1, sizeof(*e));

	e->key = key;
	e->val = val;

	return e;
}

Entry **
lookup(int key)
{
	Entry **e = &dict[key%NMEM];

	while (*e != NULL) {
		if ((*e)->key == key)
			return e;

		e = &(*e)->next;
	}

	return e;
}

void
arrprint
	(int *p, int len)
{
	for (int *q = p; q != p+len; ++q)
		printf("	%d", *q);

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
	memset(dict, 0, sizeof(dict));

	qsort(items, nitems, sizeof(*items), cmpitems);

	int *answer;
	answer = calloc(nqueries, sizeof(*answer));

	int *ap = answer;

	for (int *qp = queries; qp != queries+nqueries; ++qp) {
		Entry **e = lookup(*qp);
		if (*e) {
			*(ap++) = (*e)->val;
			continue;
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
			Entry **e = lookup((*ip)[0]);
			if (*e) {
				beauty = MAX(beauty, (*e)->val);
				break;
			}

			beauty = MAX(beauty, (*ip)[1]);
		}

		e = lookup(*qp);
		*e = entryMake(*qp, beauty);

		*(ap++) = beauty;
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
