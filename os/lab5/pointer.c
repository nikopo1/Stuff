#include <stdio.h>

int main(void) {
	int *p1 = 0xc0000008;
	char *p2 = 0xc0000008;

	p1++;
	p2++;

	printf("%p %p\n", p1, p2);
	return 0;
}
