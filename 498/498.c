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

	while (j <= *nnmat) {
		*(p++) = mat[abs(i)-1][abs(j)-1];

		++i;
		++j;

		if (j > *nnmat) {
			j = -*nnmat;
			i = -i + 2;
		}
		if (i == 0) {
			i = 1;
			j = -j;
		}
		if (i > nmat) {
			i = -nmat;
			j = -j + 2;
		}
		if (j == 0) {
			j = 1;
			i = -i;
		}
	}

	return out;
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
	print("498.c:/^example1/\n");

	const int nnmat = 3;
	int *mat[] = (int*[]){
		(int[]){1, 2, 3},
		(int[]){4, 5, 6},
		(int[]){7, 8, 9},
	};

	int narr = 0;
	int *arr = findDiagonalOrder(mat, nelem(mat), &nnmat, &narr);

	arrprint(arr, narr);
}

void
example2(void)
{
	print("498.c:/^example2/\n");

	const int nnmat = 2;
	int *mat[] = (int*[]){
		(int[]){1, 2},
		(int[]){3, 4},
	};

	int narr = 0;
	int *arr = findDiagonalOrder(mat, nelem(mat), &nnmat, &narr);

	arrprint(arr, narr);
}

void
wronganswer1(void)
{
	print("498.c:/^wronganswer1/\n");

	const int nnmat = 3;
	int *mat[] = (int*[]){
		(int[]){2, 5, 8},
		(int[]){4, 0, -1},
	};

	int narr = 0;
	int *arr = findDiagonalOrder(mat, nelem(mat), &nnmat, &narr);

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
