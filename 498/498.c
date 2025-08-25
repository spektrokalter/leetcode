#include <u.h>
#include <libc.h>

int *
findDiagonalOrder(int **mat, int nmat, const int *nnmat, int *nout)
{
	*nout = nmat * *nnmat;

	int *out;
	out = calloc(*nout, sizeof(*out));

	int *p = out;

	int i = 0, j = 0;
	int dir = -1;

	while (i >= 0 && i < nmat && j >= 0 && j < *nnmat) {
		*(p++) = mat[i][j];

		i += dir;
		j += -dir;

		if (j >= *nnmat) {
			j = *nnmat-1;
			i += 2;
			dir = -dir;
		}
		if (i < 0) {
			i = 0;
			dir = -dir;
		}
		if (i >= nmat) {
			i = nmat-1;
			j += 2;
			dir = -dir;
		}
		if (j < 0) {
			j = 0;
			dir = -dir;
		}
	}

	return out;
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
		print("	%d", *q);

	print("\n");
}

void
example1(void)
{
	const int nnmat = 3;
	int mat[][nnmat] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
	};

	int narr = 0;
	int *arr = findDiagonalOrder(mkarr(mat, nelem(mat), nnmat), nelem(mat), &nnmat, &narr);

	print("example1\n");
	arrprint(arr, narr);
}

void
example2(void)
{
	const int nnmat = 2;
	int mat[][nnmat] = {
		{1, 2},
		{3, 4},
	};

	int narr = 0;
	int *arr = findDiagonalOrder(mkarr(mat, nelem(mat), nnmat), nelem(mat), &nnmat, &narr);

	print("example2\n");
	arrprint(arr, narr);
}

void
main(void)
{
	example1();
	example2();

	exits(0);
}
