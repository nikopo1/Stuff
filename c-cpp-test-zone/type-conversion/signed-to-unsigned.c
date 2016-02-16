#include <stdio.h>

int main(void)
{
	int sa = 10;
	int sb = -1;

	unsigned int ua = sa;
	unsigned int ub = sb;

	printf("Signed to unsigned\n");
	printf("%d to %u\n", sa, ua);
	printf("%d to %u\n", sb, ub);

	return 0;
}
