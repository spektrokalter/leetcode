#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

char *
addSpaces(char *s, int *spaces, int nspaces)
{
	size_t len = strlen(s);
	int *spacesp = spaces + nspaces - 1;

	char *sp = s + len - 1;

	char *buf;
	buf = calloc(len + nspaces + 1, sizeof(*buf));

	char *bufp = buf + len + nspaces;
	*(bufp--) = 0;

	while (sp != s-1) {
		*(bufp--) = *(sp--);
		if (spacesp >= spaces && sp+1-s == *spacesp) {
			*(bufp--) = ' ';
			--spacesp;
		}
	}

	return buf;
}

void
example1(void)
{
	printf("2109.c:/example1/\n");

	int spaces[] = {8, 13, 15};

	char *withspaces = addSpaces("LeetcodeHelpsMeLearn", spaces, ARRAY_LEN(spaces));
	printf("%s\n", withspaces);
}

void
wronganswer1(void)
{
	printf("2109.c:/wronganswer1/\n");

	int spaces[] = {1, 5, 7, 9};

	char *withspaces = addSpaces("icodeinpython", spaces, ARRAY_LEN(spaces));
	printf("%s\n", withspaces);
}

int
main(void)
{
	example1();
	wronganswer1();

	return 0;
}
