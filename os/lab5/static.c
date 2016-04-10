#include <stdio.h>

int f(void) {
	static int x = 0;
	++x;
	printf("x=%d\n", x);
	return x;
}

int main(void) {
	f();
	f();
	f();
	return 0;
}
