#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

int
prefixCount(char **words, int nwords, const char *pref)
{
	int n = 0;

	for (char **w = words; w != words+nwords; ++w) {
		const char *pp = pref;
		const char *wp = *w;

		while (*pp && *wp && *pp == *wp) {
			++pp;
			++wp;
		}

		if (!*pp)
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

void
wronganswer1(void)
{
	printf("2185.c:/example2/\n");

	char *words[] = {"lewsmb", "lewrydnve", "lewqqm", "lewec", "lewn", "lewb", "lewedb"};
	int n = prefixCount(words, ARRAY_LEN(words), "lew");
	printf("n: %d\n", n); // 7
}

void
wronganswer2(void)
{
	printf("2185.c:/wronganswer2/\n");

	char *words[] = {
		"kttxeksggb", "vucqwew", "lyknscc", "mryl",
		"vwarnwkfmd", "ivawxbntgs", "mylw", "namybmfy",
		"uosag", "rzernqxyn", "puf", "hfwjnmvm", "jjfyd",
		"xteybd", "v", "ywntwzn", "npsogop", "brgvlw",
		"vewhi", "brk", "hheub", "zl", "vt", "bxjtjivep", "p",
		"io", "xotulskjmt", "mctffonh", "pmeuqhoe", "ghktrtq",
		"u", "ngnvwan", "pqmlvvhl", "enjf", "qomcejb",
		"twgqww", "bnilyqy", "nc", "fttlodnz", "fya", "g",
		"uoivsr", "gtxgcaf", "qs", "gkfl", "sdmacxf", "mzy",
		"xjv", "yipc", "rctqugjjk", "myij", "xxg", "vyup",
		"utqxplpsa", "imbteaczlc", "qfgdcz", "atfn", "pxcsg",
		"f", "omukbiaudb", "uh", "uobwgt", "hgqipk",
		"zunfzinenk", "i", "p", "pet", "fxai", "ortqpwkukg",
		"rxgh", "ylfh",
	};
	int n = prefixCount(words, ARRAY_LEN(words), "ikwjoty");
	printf("n: %d\n", n); // 0
}

void
wronganswer3(void)
{
	printf("2185.c:/wronganswer3/\n");

	char *words[] = {
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh", "vbx",
		"fsi", "sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "gqira", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh", "sxyjellhlh",
		"sxyjellhlh", "sxyjellhlh"
	};
	int n = prefixCount(words, ARRAY_LEN(words), "sxyjellhlh");
	printf("n: %d\n", n); // 92
}

int
main(void)
{
	example1();
	example2();
	wronganswer1();
	wronganswer2();
	wronganswer3();

	return 0;
}
