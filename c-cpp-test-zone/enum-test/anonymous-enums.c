#include <stdio.h>

int main(void)
{
	int start;
	enum { Si = 4 };
	enum { Sn = -1 };
	int end;
	printf("Anonymous enum from %p to %p!\n", &start, &end);
	return 0;
}
