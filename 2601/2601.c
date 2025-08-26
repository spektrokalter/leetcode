#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define nelem(x) (sizeof(x) / sizeof((x)[0]))

int primes[] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
	59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
	191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
	257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
	331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
	401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
	467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557,
	563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619,
	631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
	709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787,
	797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
	877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953,
	967, 971, 977, 983, 991, 997, 1009,
};

bool
primeSubOperation(int *p, int len)
{
	// p[0] is special. Make it as small as possible.
	if (p[0] > 2) {
		int *pp = primes;
		while (*pp < p[0])
			++pp;
		--pp;
		p[0] -= *pp;
	}

	for (int *q = p+1; q != p+len; ++q) {
		if (*q <= 2) {
			if (*q <= q[-1])
				return false;
			else
				continue;
		}

		// find *pp closest to *q
		int *pp = primes;
		while (*pp < *q)
			++pp;
		--pp;

		// find min(*q-*prime) greater than q[-1]
		while (pp != primes-1 && *q-*pp <= q[-1])
			--pp;

		// not found
		if (pp == primes-1) {
			if (*q > q[-1])
				continue;
			else
				return false;
		}

		*q -= *pp;
	}

	return true;
}

void
example1
	(void)
{
	printf("2601.c:/example1/\n");
	int arr[] = {4, 9, 6, 10};
	bool ok = primeSubOperation(arr, nelem(arr));
	printf("ok: %d\n", ok); // 1
}

void
example2
	(void)
{
	printf("2601.c:/example2/\n");
	int arr[] = {6, 8, 11, 12};
	bool ok = primeSubOperation(arr, nelem(arr));
	printf("ok: %d\n", ok); // 1
}

void
example3
	(void)
{
	printf("2601.c:/example3/\n");
	int arr[] = {5, 8, 3};
	bool ok = primeSubOperation(arr, nelem(arr));
	printf("ok: %d\n", ok); // 0
}

void
wronganswer1
	(void)
{
	printf("2601.c:/wronganswer1/\n");
	int arr[] = {8, 19, 3, 4, 9};
	bool ok = primeSubOperation(arr, nelem(arr));
	printf("ok: %d\n", ok); // 1
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
