#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

struct node
{
	int val;
	struct node **children;
	int nchildren;
};
typedef struct node Node;

Node *globalqueue[2000000];

Node *
mknode(int val)
{
	Node *n;
	n = calloc(1, sizeof(*n));
	n->val = val;
	n->children = calloc(500, sizeof(n->children[0]));
	return n;
}

int
bfs(Node **graph, int cities)
{
	Node **queue = globalqueue;
	int nqueue = 0;

	queue[nqueue++] = graph[0];

	int depth = 0;

	while (nqueue > 0) {
		int prevlen = nqueue;

		for (Node **qp = queue; qp != queue+prevlen; ++qp) {
			if ((*qp)->val == cities-1)
				return depth;

			for (Node **child = (*qp)->children; child != (*qp)->children+(*qp)->nchildren; ++child) {
				queue[nqueue++] = *child;
			}
		}

		memmove(queue, queue+prevlen, (nqueue-prevlen)*sizeof(queue[0]));
		nqueue -= prevlen;

		++depth;
	}

	return depth;
}

int *
shortestDistanceAfterQueries
	(int cities, int **queries, int nqueries, int *mqueries, int *ndistances)
{
	Node *graph[501] = {0};

	for (int i = 0; i < cities; ++i)
		graph[i] = mknode(i);

	for (int i = 1; i < cities; ++i) {
		Node *parent = graph[i-1], *child = graph[i];
		parent->children[parent->nchildren++] = child;
	}

	int *distances;
	distances = calloc(nqueries, sizeof(*distances));

	int *dp = distances;

	for (int **qp = queries; qp != queries+nqueries; ++qp) {
		Node *parent = graph[(*qp)[0]], *child = graph[(*qp)[1]];
		parent->children[parent->nchildren++] = child;

		*(dp++) = bfs(graph, cities);
	}

	*ndistances = nqueries;
	return distances;
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
arrprint(int *p, int len)
{
	for (int *q = p; q != p+len; ++q)
		printf("	%d", *q);

	printf("\n");
}

void
example1(void)
{
	printf("3243.c:/example1/\n");

	int queries[][2] = {{2, 4}, {0, 2}, {0, 4}};
	int cols[] = {2, 2, 2};

	int ndistances = 0;
	int *distances = shortestDistanceAfterQueries(
		5, mkarr(queries, ARRAY_LEN(queries), 2), ARRAY_LEN(queries), cols, &ndistances
	);

	printf("distances:\n");
	arrprint(distances, ndistances); // 3 2 1
}

void
example2(void)
{
	printf("3243.c:/example2/\n");

	int queries[][2] = {{0, 3}, {0, 2}};
	int cols[] = {2, 2};

	int ndistances = 0;
	int *distances = shortestDistanceAfterQueries(
		4, mkarr(queries, ARRAY_LEN(queries), 2), ARRAY_LEN(queries), cols, &ndistances
	);

	printf("distances:\n");
	arrprint(distances, ndistances); // 1 1
}

int
main(void)
{
	example1();
	example2();

	return 0;
}
