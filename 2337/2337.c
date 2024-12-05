#include <stdbool.h>
#include <stdio.h>

bool
canChange(char *start, char *target)
{
	char *sp = start, *tp = target;

	for (; *sp; ++sp) {
		if (*sp == '_')
			continue;

		while (*tp && *tp == '_')
			++tp;

		if (!*tp || *tp != *sp)
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

int
main(void)
{
	example1();
	example2();
	example3();

	return 0;
}
