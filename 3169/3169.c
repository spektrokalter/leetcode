#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

#define MAX(x, y) ((x)>(y) ? (x) : (y))

int
cmpinterval(const void *vp1, const void *vp2)
{
	const int *x = *(const int **)vp1;
	const int *y = *(const int **)vp2;

	if (x[0] != y[0])
		return (x[0] > y[0]) - (x[0] < y[0]);
	else
		return (x[1] > y[1]) - (x[1] < y[1]);
}

int
countDays(int days, int **meetings, int nmeetings, int *nnmeetings)
{
	qsort(meetings, nmeetings, sizeof(*meetings), cmpinterval);

	// max1, in the beginning of each iteration, represents
	// max(meetings[][1]) of the previous iteration.
	//
	int max1 = 0;

	int busy = 0;

	for (int **m = meetings; m != meetings+nmeetings; ++m) {
		if ((*m)[0] > max1 && (*m)[1] > max1) // ((1, 10) m=(20, 30))
			busy += (*m)[1] - (*m)[0] + 1;
		else if ((*m)[1] > max1) // ((1, 10) m=(5, 15)) or ((1, 30) (10, 20) m=(25, 35))
			busy += (*m)[1] - max1;

		// excluded: ((1, 10) m=(2, 8))

		max1 = MAX(max1, (*m)[1]);

//		printf("(%d, %d), %d, %d\n", (*m)[0], (*m)[1], max1, busy);
	}

	return days - busy;
}

void
example1(void)
{
	int *meetings[] = (int*[]){(int[]){5, 7}, (int[]){1, 3}, (int[]){9, 10}};

	int available = countDays(10, meetings, ARRAY_LEN(meetings), NULL);
	printf("3169.c:/^example1/		%d\n", available); // 2
}

void
example2(void)
{
	int *meetings[] = (int*[]){(int[]){2, 4}, (int[]){1, 3}};

	int available = countDays(5, meetings, ARRAY_LEN(meetings), NULL);
	printf("3169.c:/^example2/		%d\n", available); // 1
}

void
example3(void)
{
	int *meetings[] = (int*[]){(int[]){1, 6}};

	int available = countDays(6, meetings, ARRAY_LEN(meetings), NULL);
	printf("3169.c:/^example3/		%d\n", available); // 0
}

// 4, 8 → 8-4+1 = 5
// 7, 42 → 5 + 42-8 = 39
// 9, 18 → 39
// 9, 33 → 39
// 18, 19 → 39
// 22, 31 → problem
// 23, 39
// 30, 46
//
void
wronganswer1(void)
{
	int *meetings[] = (int*[]){
		(int[]){22, 31}, (int[]){7, 42}, (int[]){30, 46},
		(int[]){9, 33}, (int[]){9, 18}, (int[]){23, 39},
		(int[]){4, 8}, (int[]){18, 19},
	};

	int available = countDays(50, meetings, ARRAY_LEN(meetings), NULL);
	printf("3169.c:/^wronganswer1/	%d\n", available); // 7
}

// 2, 44 → 44-2+1 = 43
// 3, 55 → 43+55-44 = 54
// 13, 21 → 54
// 14, 24 → 54
// 16, 19 → 54
// 16, 38 → 54
// 20, 25 → 54
// 37, 40 → 54
// 54, 58 → 54+58-55 = 57 → problem
//
void
wronganswer2(void)
{
	int *meetings[] = (int*[]){
		(int[]){37, 40}, (int[]){16, 19}, (int[]){20, 25},
		(int[]){3, 55}, (int[]){16, 38}, (int[]){2, 44},
		(int[]){54, 58}, (int[]){14, 24}, (int[]){13, 21},
	};

	int available = countDays(65, meetings, ARRAY_LEN(meetings), NULL);
	printf("3169.c:/^wronganswer2/	%d\n", available); // 8
}

int
main(void)
{
	example1();
	example2();
	example3();
	wronganswer1();
	wronganswer2();

	return 0;
}
