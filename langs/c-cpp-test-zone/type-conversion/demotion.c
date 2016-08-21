#include <stdio.h>

int main(void)
{
	int ia = -1;
	char ca = ia;

	printf("%d int is %c char (hex=%x)\n", ia, ca, ca & 0xff);

	unsigned int uia = -1;
	unsigned char uca = uia;

	printf("%d uint is %c uchar (hex=%x)\n", uia, uca, uca & 0xff);

	return 0;
}
