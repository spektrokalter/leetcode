#include <stdbool.h>
#include <stdio.h>

/*
	L in start cannot be matched by an L in target that stays to
	the right.
*/

bool
canChange(char *start, char *target)
{
	char *sp = start, *tp = target;

	for (; *sp; ++sp) {
		if (*sp == '_')
			continue;

		while (*tp && *tp == '_')
			++tp;

		if (!*tp)
			return false;

		if (*sp == 'L' && *tp == 'L' && sp-start < tp-target)
			return false;

		if (*sp == 'R' && *tp == 'R' && sp-start > tp-target)
			return false;

		if (*sp != *tp)
			return false;

		++tp;
	}

	return true;
}

void
example1(void)
{
	printf("2337.c:/example1/\n");

	bool ok = canChange("_L__R__R_", "L______RR");
	printf("ok: %d\n", ok); // 1
}

void
example2(void)
{
	printf("2337.c:/example2/\n");

	bool ok = canChange("R_L_", "__LR");
	printf("ok: %d\n", ok); // 0
}

void
example3(void)
{
	printf("2337.c:/example3/\n");

	bool ok = canChange("_R", "R_");
	printf("ok: %d\n", ok); // 0
}

void
wronganswer1(void)
{
	printf("2337.c:/wronganswer1/\n");

	bool ok = canChange("____", "R_L_");
	printf("ok: %d\n", ok); // 0
}

int
main(void)
{
	example1();
	example2();
	example3();
	wronganswer1();

	return 0;
}
