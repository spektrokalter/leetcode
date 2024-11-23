#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))
#define MAX(x, y) ((x)>(y) ? (x) : (y))

typedef struct rtnode Rtnode;
struct rtnode
{
	char *s;
	int count;
	Rtnode *children[2];
};

struct radixtree
{
	Rtnode *root;
};
typedef struct radixtree Rtree;

Rtnode *
rtnew(char *s, int count)
{
	Rtnode *n;
	n = calloc(1, sizeof(*n));
	n->s = strdup(s);
	n->count = count;
	return n;
}

Rtnode *
rtins(Rtnode *head, char *s)
{
	// On each iteration head represents s[0].
	// That is, head->s[0] == s[0].

	if (!head)
		return rtnew(s, 1);

	if (0 == strcmp(head->s, s)) {
		head->count++;
		return head;
	}

	// Find first i such that head->s[i] != s[i].
	//
	size_t i = 0;
	while (head->s[i] && s[i] && head->s[i] == s[i])
		++i;

	// head->s is fully a prefix of s.
	//
	if (!head->s[i]) {
		Rtnode **p = head->children + s[i] - '0';
		*p = rtins(*p, s + i);
		return head;
	}

	// Keep matching part, make the rest its child.
	//
	Rtnode *subtree = rtnew(head->s + i, head->count);
	head->count = 0;
	for (int i = 0; i < 2; ++i) {
		subtree->children[i] = head->children[i];
		head->children[i] = NULL;
	}
	head->children[head->s[i] - '0'] = subtree;

	if (!s[i]) {
		// s is fully a prefix of head->s.

		head->count = 1;
	} else {
		// s is partly a prefix of head->s.

		head->count = 0;
		head->children[s[i] - '0'] = rtnew(s + i, 1);
	}

	// Only keep matching part of the string.
	//
	head->s[i] = 0;

	return head;
}

bool
rtcontains(Rtnode *head, char *s)
{
	// On each iteration head represents s[0].
	// That is, head->s[0] == s[0].

	if (!head)
		return false;

	if (0 == strcmp(head->s, s))
		return head->count > 0;

	// Find first i such that head->s[i] != s[i].
	//
	size_t i = 0;
	for (; head->s[i] && s[i]; i++) {
		if (head->s[i] != s[i])
			break;
	}

	// head->s is fully a prefix of s.
	//
	if (!head->s[i])
		return rtcontains(head->children[s[i] - '0'], s+i);

	// s is either fully (!s[i]) or partly a prefix of head->s.
	//
	return false;
}

int
rtmaxcount(Rtnode *head)
{
	if (!head)
		return 0;

	int count = head->count;
	for (int i = 0; i < 2; ++i) {
		int x = rtmaxcount(head->children[i]);
		count = MAX(count, x);
	}

	return count;
}

Rtree *
rtreenew(void)
{
	Rtree *rt;
	rt = calloc(1, sizeof(*rt));
	rt->root = rtnew("/", 0);
	return rt;
}

void
rtreeins(Rtree *rt, char *s)
{
	Rtnode **p = rt->root->children + *s - '0';
	*p = rtins(*p, s);
}

bool
rtreefullmatch(Rtree *rt, char *s)
{
	return rtcontains(rt->root->children[*s - '0'], s);
}

void
strrev(char *dst, char *src)
{
	char *dstp = dst;

	for (char *srcp = src; *srcp; ++srcp) {
		if (*srcp == '0') *(dstp++) = '1';
		else if (*srcp == '1') *(dstp++) = '0';
		else abort();
	}

	*dstp = 0;
}

int
maxEqualRowsAfterFlips(int **matrix, int rows, int *cols)
{
	Rtree *rt = rtreenew();

	for (int **p = matrix; p != matrix+rows; ++p) {
		char s[301] = {0};
		char *sp = s;

		for (int *q = *p; q != *p+cols[0]; ++q)
			*(sp++) = *q + '0';

		*sp = 0;

		char rev[301] = {0};
		strrev(rev, s);

		if (rtreefullmatch(rt, rev))
			rtreeins(rt, rev);
		else
			rtreeins(rt, s);
	}

	return rtmaxcount(rt->root);
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
	printf("1072.c:/example1/\n");

	int arr[][2] = {
		{0, 1},
		{1, 1},
	};
	int cols[] = {2, 2};

	int equalrows = maxEqualRowsAfterFlips(mkarr(arr, ARRAY_LEN(arr), 2), ARRAY_LEN(arr), cols);
	printf("equalrows: %d\n", equalrows); // 1
}

void
example2(void)
{
	printf("1072.c:/example2/\n");

	int arr[][2] = {
		{0, 1},
		{1, 0},
	};
	int cols[] = {2, 2};

	int equalrows = maxEqualRowsAfterFlips(mkarr(arr, ARRAY_LEN(arr), 2), ARRAY_LEN(arr), cols);
	printf("equalrows: %d\n", equalrows); // 2
}

void
example3(void)
{
	printf("1072.c:/example3/\n");

	int arr[][3] = {
		{0, 0, 0},
		{0, 0, 1},
		{1, 1, 0},
	};
	int cols[] = {3, 3, 3};

	int equalrows = maxEqualRowsAfterFlips(mkarr(arr, ARRAY_LEN(arr), 3), ARRAY_LEN(arr), cols);
	printf("equalrows: %d\n", equalrows); // 2
}

void
solution1(void)
{
	printf("1072.c:/solution1/\n");

	int arr[][3] = {
		{0, 1, 0},
		{0, 1, 0},
		{1, 1, 0},
	};
	int cols[] = {3, 3, 3};

	int equalrows = maxEqualRowsAfterFlips(mkarr(arr, ARRAY_LEN(arr), 3), ARRAY_LEN(arr), cols);
	printf("equalrows: %d\n", equalrows); // 2
}

void
solution2(void)
{
	printf("1072.c:/solution2/\n");

	int arr[][4] = {
		{0, 1, 0, 0},
		{1, 0, 1, 1},
		{0, 1, 0, 0},
		{0, 1, 1, 0},
	};
	int cols[] = {4, 4, 4, 4};

	int equalrows = maxEqualRowsAfterFlips(mkarr(arr, ARRAY_LEN(arr), 4), ARRAY_LEN(arr), cols);
	printf("equalrows: %d\n", equalrows); // 3
}

void
wronganswer1(void)
{
	printf("1072.c:/wronganswer1/\n");

	int arr[][11] = {
		{1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
		{1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
		{1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
	};
	int cols[] = {11, 11, 11, 11, 11};

	int equalrows = maxEqualRowsAfterFlips(mkarr(arr, ARRAY_LEN(arr), 11), ARRAY_LEN(arr), cols);
	printf("equalrows: %d\n", equalrows); // 2
}

void
wronganswer2(void)
{
	printf("1072.c:/wronganswer2/\n");

	int arr[][7] = {
		{1, 1, 1, 0, 1, 1, 0},
		{0, 1, 0, 1, 1, 0, 0},
		{1, 1, 0, 1, 0, 1, 0},
		{1, 0, 0, 0, 0, 1, 1},
		{0, 1, 1, 0, 0, 1, 1},
		{1, 0, 0, 0, 1, 1, 0},
		{0, 1, 0, 1, 0, 1, 0},
		{1, 0, 0, 1, 0, 1, 0},
		{0, 1, 0, 1, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 0},
	};
	int cols[] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

	int equalrows = maxEqualRowsAfterFlips(mkarr(arr, ARRAY_LEN(arr), 7), ARRAY_LEN(arr), cols);
	printf("equalrows: %d\n", equalrows); // 1
}

int
main(void)
{
	example1();
	example2();
	example3();
	solution1();
	solution2();
	wronganswer1();
	wronganswer2();

	return 0;
}
