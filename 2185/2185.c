#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

typedef struct rtnode Rtnode;
struct rtnode
{
	char *s;
	int last;
	Rtnode *children[256];
};

Rtnode *
rtnew(char *s, int last)
{
	Rtnode *n;
	n = calloc(1, sizeof(*n));
	n->s = strdup(s);
	n->last = last;
	return n;
}

void
rtins(Rtnode **headp, char *s)
{
	// On each iteration head represents s[0].
	// That is, head->s[0] == s[0].

	if (!*headp) {
		*headp = rtnew(s, true);
		return;
	}

	Rtnode *head = *headp;

	if (0 == strcmp(head->s, s)) {
		head->last++;
		return;
	}

	// Find first i such that head->s[i] != s[i].
	//
	size_t i = 0;
	while (head->s[i] && s[i] && head->s[i] == s[i])
		++i;

	// head->s is fully a prefix of s.
	//
	if (!head->s[i]) {
		rtins(&head->children[s[i]], s + i);
		return;
	}

	// Keep matching part, make the rest its child.
	//
	Rtnode *subtree = rtnew(head->s + i, head->last);
	for (int i = 0; i < 256; ++i) {
		subtree->children[i] = head->children[i];
		head->children[i] = NULL;
	}
	head->children[head->s[i]] = subtree;

	if (!s[i]) {
		// s is fully a prefix of head->s.

		head->last = 1;
	} else {
		// s is partly a prefix of head->s.

		head->last = 0;
		head->children[s[i]] = rtnew(s + i, 1);
	}

	// Only keep matching part of the string.
	//
	head->s[i] = 0;
}

int
rtsum(Rtnode *head)
{
	if (!head)
		return 0;

	int n = 0;

	for (int i = 0; i < 256; ++i)
		n += rtsum(head->children[i]);

	return head->last + n;
}

int
rtcontains(Rtnode *head, char *s)
{
	// On each iteration head represents s[0].
	// That is, head->s[0] == s[0].

	if (!head)
		return 0;

	if (0 == strcmp(head->s, s))
		return rtsum(head);

	// Find first i such that head->s[i] != s[i].
	//
	size_t i = 0;
	while (head->s[i] && s[i] && head->s[i] == s[i])
		++i;

	// head->s is fully a prefix of s.
	//
	if (!head->s[i])
		return rtcontains(head->children[s[i]], s+i);

	// s is fully a prefix of head->s.
	if (!s[i])
		return rtsum(head);

	// s is partly a prefix of head->s.
	//
	return 0;
}

void
rtnuke(Rtnode *head)
{
	if (!head)
		return;
	for (int i = 0; i < 256; ++i)
		rtnuke(head->children[i]);
	free(head->s);
	free(head);
}

void
rtprint(Rtnode *head, int shift)
{
	if (!head)
		return;

	printf("%*s%s", 4*shift, "", head->s);
	if (head->last)
		printf(". x%d", head->last);
	printf("\n");

	for (int i = 0; i < 256; ++i)
		rtprint(head->children[i], shift + 1);
}

int
prefixCount(char **words, int nwords, char *pref)
{
	int n = 0;

	for (char **w = words; w != words+nwords; ++w) {
		char *pp = pref;
		char *wp = *w;

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
