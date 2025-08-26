#include <stdio.h>

#define nelem(x) (sizeof(x) / sizeof((x)[0]))
#define MIN(x, y) ((x)<(y) ? (x) : (y))

int
dictnum
	(int dict[32])
{
	int n = 0;
	for (int *p = dict; p != dict+32; ++p) {
		n <<= 1;
		if (*p)
			n |= 1;
	}
	return n;
}

void
dictadd
	(int dict[32], int n)
{
	int *p = dict + 32 - 1;
	for (int i = 0; i < 32; ++i, --p) {
		if (n & 1)
			++*p;
		n >>= 1;
	}
}

void
dictremove
	(int dict[32], int n)
{
	int *p = dict + 32 - 1;
	for (int i = 0; i < 32; ++i, --p) {
		if (n & 1)
			--*p;
		n >>= 1;
	}
}

int
minimumSubarrayLength
	(int *p, int len, int k)
{
	int minlen = 200001;

	int *left = p, *right = p+1;
	int dict[32] = {0};
	dictadd(dict, *left);

	while (left < right) {
		if (dictnum(dict) < k) {
			if (right == p+len)
				goto stop;

			dictadd(dict, *right);
			++right;
		}
		if (dictnum(dict) >= k) {
			dictremove(dict, *left);
			++left;
			minlen = MIN(minlen, right - left);
		}
	}

stop:
	if (minlen == 200001)
		return -1;
	else
		return minlen + 1;
}

void
example1
	(void)
{
	printf("main.c:/^example1/\n");
	int arr[] = {1, 2, 3};
	int len = minimumSubarrayLength(arr, nelem(arr), 2);
	printf("len: %d\n", len); // 1
}

void
example2
	(void)
{
	printf("main.c:/^example2/\n");
	int arr[] = {2, 1, 8};
	int len = minimumSubarrayLength(arr, nelem(arr), 10);
	printf("len: %d\n", len); // 3
}

void
example3
	(void)
{
	printf("main.c:/^example3/\n");
	int arr[] = {1, 2};
	int len = minimumSubarrayLength(arr, nelem(arr), 0);
	printf("len: %d\n", len); // 1
}

void
wronganswer1
	(void)
{
	printf("main.c:/^wronganswer1/\n");
	int arr[] = {1, 2, 32, 21};
	int len = minimumSubarrayLength(arr, nelem(arr), 55);
	printf("len: %d\n", len); // 3
}

int
main
	(void)
{
	example1();
	example2();
	example3();
	wronganswer1();

	return 0;
}
