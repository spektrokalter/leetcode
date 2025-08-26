#include <stdbool.h>
#include <stdio.h>

#define nelem(x) (sizeof(x) / sizeof((x)[0]))
#define MAX(x, y) ((x)>(y) ? (x) : (y))
#define MIN(x, y) ((x)<(y) ? (x) : (y))

bool
candistribute(int x, int n, int *quantities, int qlen)
{
	for (int *qp = quantities; qp != quantities+qlen; ++qp) {
		int q = *qp;
		while (q) {
			if (n == 0)
				return false;

			q -= MIN(x, q);
			--n;
		}
	}

	return true;
}

int
minimizedMaximum(int n, int *quantities, int qlen)
{
	int maxq = 0;
	for (int *qp = quantities; qp != quantities+qlen; ++qp)
		maxq = MAX(maxq, *qp);

	// x is the smallest in [0; max(quantities)) at which candistribute(x) is true
	int x = 0, limit = maxq;
	while (x < limit) {
		int h = (x + limit) / 2;
		if (!candistribute(h, n, quantities, qlen))
			x = h + 1;
		else
			limit = h;
	}

	return x;
}

void
example1(void)
{
	printf("2064.c:/example1/\n");

	int quantities[] = {11, 6};
	int x = minimizedMaximum(6, quantities, nelem(quantities));
	printf("x: %d\n", x); // 3
}

void
example2(void)
{
	printf("2064.c:/example2/\n");

	int quantities[] = {15, 10, 10};
	int x = minimizedMaximum(7, quantities, nelem(quantities));
	printf("x: %d\n", x); // 5
}

void
example3(void)
{
	printf("2064.c:/example3/\n");

	int quantities[] = {100000};
	int x = minimizedMaximum(1, quantities, nelem(quantities));
	printf("x: %d\n", x); // 100000
}

void
wronganswer1(void)
{
	printf("2064.c:/wronganswer1/\n");

	int quantities[] = {5, 7};
	int x = minimizedMaximum(2, quantities, nelem(quantities));
	printf("x: %d\n", x); // 7
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
