#include <stdio.h>

int main(void)
{
	int a = 031;
	int b = 0x19;

	a == b ? printf("Equal\n") : printf("Different\n");

	return 0;
}
