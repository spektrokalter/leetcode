#include <u.h>
#include <libc.h>

#define MAX(a, b) ((a)>(b) ? (a) : (b))

int
areaOfMaxDiagonal(int **dim, int ndim, int *nndim)
{
	long double maxdiagonal = 0;
	int area = 0;

	for (int **p = dim; p != dim+ndim; ++p) {
		long double diagonal = sqrt((*p)[0]*(*p)[0] + (*p)[1]*(*p)[1]);
		if (diagonal == maxdiagonal) {
			area = MAX(area, (*p)[0]*(*p)[1]);
		}
		else if (diagonal > maxdiagonal) {
			maxdiagonal = diagonal;
			area = (*p)[0]*(*p)[1];
		}
	}

	return area;
}

void
example1(void)
{
	print("3000.c:/example1/\n");

	int *dim[] = (int*[]){(int[]){9, 3}, (int[]){8, 6}};

	int nndim = 2;
	int area = areaOfMaxDiagonal(dim, nelem(dim), &nndim);
	print("%d\n", area); // 48
}

void
example2(void)
{
	print("3000.c:/example2/\n");

	int *dim[] = (int*[]){(int[]){3, 4}, (int[]){4, 3}};

	int nndim = 2;
	int area = areaOfMaxDiagonal(dim, nelem(dim), &nndim);
	print("%d\n", area); // 12
}

void
wonganswer1(void)
{
	print("3000.c:/wonganswer1/\n");

	int *dim[] = (int*[]){
		(int[]){6, 5}, (int[]){8, 6}, (int[]){2, 10},
		(int[]){8, 1}, (int[]){9, 2}, (int[]){3, 5},
		(int[]){3, 5},
	};

	int nndim = 2;
	int area = areaOfMaxDiagonal(dim, nelem(dim), &nndim);
	print("%d\n", area); // 20
}

void
main(void)
{
	example1();
	example2();
	wonganswer1();

	exits(0);
}
