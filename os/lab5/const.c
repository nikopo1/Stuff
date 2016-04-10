#include <stdio.h>

int v = 1;

int main(void) {
	int const * p;
	p = &v;
	*p = 10;
	printf("%d\n", v);
	return 0;
}
