#include <stdio.h>
#include <stdlib.h>

#define nelem(x) (sizeof(x) / sizeof((x)[0]))

int
numcmp(const void *vp1, const void *vp2)
{
	int x = *(int *)vp1;
	int y = *(int *)vp2;

	return (x > y) - (x < y);
}

long long
countFairPairs(int *p, int len, int lower, int upper)
{
	qsort(p, len, sizeof(*p), numcmp);

	long long pairs = 0;

	for (int *pp = p; pp != p+len; ++pp) {

		// left is the smallest in [pp+1; p+len) at which *pp+*left >= lower
		int *left = pp+1, *limit = p+len;
		while (left < limit) {
			int *h = left + (limit - left)/2;
			if (!(*pp+*h >= lower))
				left = h + 1;
			else
				limit = h;
		}

		if (left == p+len || !(*pp+*left >= lower))
			continue;

		// right is the smallest in [pp+1; p+len) at which *pp+*right > upper
		int *right = pp+1;
		limit = p + len;
		while (right < limit) {
			int *h = right + (limit - right)/2;
			if (!(*pp+*h > upper))
				right = h + 1;
			else
				limit = h;
		}

		pairs += right - left;
	}

	return pairs;
}

void
example1(void)
{
	printf("2563.c:/^example1/\n");

	int arr[] = {0, 1, 7, 4, 4, 5};
	long long pairs = countFairPairs(arr, nelem(arr), 3, 6);
	printf("pairs: %lld\n", pairs); // 6
}

void
example2(void)
{
	printf("2563.c:/^example2/\n");

	int arr[] = {1, 7, 9, 2, 5};
	long long pairs = countFairPairs(arr, nelem(arr), 11, 11);
	printf("pairs: %lld\n", pairs); // 1
}

void
wronganswer1(void)
{
	printf("2563.c:/^wronganswer1/\n");

	int arr[] = {0, 0, 0, 0, 0, 0};
	long long pairs = countFairPairs(arr, nelem(arr), 0, 0);
	printf("pairs: %lld\n", pairs); // 15
}

int
main(void)
{
	example1();
	example2();
	wronganswer1();

	return 0;
}
