#include <u.h>
#include <libc.h>

int *
findDiagonalOrder(int **mat, int nmat, const int *nnmat, int *nout)
{
	*nout = nmat * *nnmat;

	int *out;
	out = calloc(*nout, sizeof(*out));

	int *p = out;

	int i = -1, j = 1;

	while (abs(j) <= *nnmat) {
		*(p++) = mat[abs(i)-1][abs(j)-1];

		++i;
		++j;

		if (abs(j) > *nnmat) {
			j = -*nnmat;
			i = -i + 2;
		}
		if (abs(i) < 1) {
			i = 1;
			j = -j;
		}
		if (abs(i) > nmat) {
			i = -nmat;
			j = -j + 2;
		}
		if (abs(j) < 1) {
			j = 1;
			i = -i;
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
wronganswer1(void)
{
	const int nnmat = 3;
	int mat[][nnmat] = {
		{2, 5, 8},
		{4, 0, -1},
	};

	int narr = 0;
	int *arr = findDiagonalOrder(mkarr(mat, nelem(mat), nnmat), nelem(mat), &nnmat, &narr);

	print("wronganswer1\n");
	arrprint(arr, narr);
}

void
main(void)
{
	example1();
	example2();
	wronganswer1();

	exits(0);
}
