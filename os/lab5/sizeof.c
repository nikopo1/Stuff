#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int v1[10];
	int *v2 = malloc(sizeof(int) * 10);
	printf("%d %d\n", sizeof(v1), sizeof(v2));
	return 0;
}
