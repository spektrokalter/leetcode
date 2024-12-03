#include <stdio.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

// 3e5 string + 3e5 spaces + 0
char buf[600001];

char *
addSpaces(char *s, int *spaces, int nspaces)
{
	size_t len = strlen(s);
	int *spacesp = spaces + nspaces - 1;

	char *sp = s + len - 1;
	char *bufp = buf + len + nspaces;

	*(bufp--) = 0;

	while (sp != s-1) {
		if (spacesp >= spaces && sp-s == *spacesp) {
			*(bufp--) = *(sp--);
			*(bufp--) = ' ';
			--spacesp;
		} else {
			*(bufp--) = *(sp--);
		}
	}

	return strdup(buf);
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
