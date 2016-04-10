#include <stdio.h>

char a[7][3][2] = { {0} };

int main(void)
{
	printf("%d\n", sizeof(char));
	printf("%d\n", sizeof(a));

	printf("%p\n%p\n", &a, &a[0][0][0]);

	return 0;
}
