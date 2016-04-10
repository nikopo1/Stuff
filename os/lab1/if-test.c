#include <stdio.h>

int main(void)
{
	int x = 1, y = 2, z = 3;

	if(x = 0, y = 1, z = 0) {
		printf("%d, %d, %d\n", x, y, z);
	} else {
		printf("Error!\n");
	}
	return 0;
}
