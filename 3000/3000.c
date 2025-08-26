#include <u.h>
#include <libc.h>

#define MAX(a, b) ((a)>(b) ? (a) : (b))

int
areaOfMaxDiagonal(int **dim, int ndim, int *nndim)
{
	long double maxdiagonal = 0;
	int maxarea = 0;

	for (int **p = dim; p != dim+ndim; ++p) {
		long double diagonal = sqrt((*p)[0]*(*p)[0] + (*p)[1]*(*p)[1]);
		if (diagonal >= maxdiagonal) {
			maxdiagonal = diagonal;
			maxarea = MAX(maxarea, (*p)[0]*(*p)[1]);
		}
	}

	return maxarea;
}

void
example1(void)
{
	int **dim = (int*[]){(int[]){9, 3}, (int[]){8, 6}};

	int nndim = 2;
	int area = areaOfMaxDiagonal(dim, 2, &nndim);
	print("example1\n");
	print("%d\n", area); // 48
}

void
example2(void)
{
	int **dim = (int*[]){(int[]){3, 4}, (int[]){4, 3}};

	int nndim = 2;
	int area = areaOfMaxDiagonal(dim, 2, &nndim);
	print("example2\n");
	print("%d\n", area); // 12
}

void
main(void)
{
	example1();
	example2();

	exits(0);
}
