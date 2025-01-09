#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

bool
prefix(char *s, char *p)
{
	return strncmp(s, p, strlen(p)) == 0;
}

int
prefixCount(char **words, int nwords, char *pref)
{
	int n = 0;

	for (char **w = words; w != words+nwords; ++w) {
		if (prefix(*w, pref))
			++n;
	}

	return n;
}

void
example1(void)
{
	printf("2185.c:/example1/\n");

	char *words[] = {"pay", "attention", "practice", "attend"};
	int n = prefixCount(words, ARRAY_LEN(words), "at");
	printf("n: %d\n", n); // 2
}

void
example2(void)
{
	printf("2185.c:/example2/\n");

	char *words[] = {"leetcode", "win", "loops", "success"};
	int n = prefixCount(words, ARRAY_LEN(words), "code");
	printf("n: %d\n", n); // 0
}

int
main(void)
{
	example1();
	example2();

	return 0;
}
