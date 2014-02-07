#include <stdio.h>

void find_pythagorean_triplet(void)
{
	int a,b,c;
	int up, down;

	for(a = 0; a < 500; a++) {
		// compute b
		up = 500000 - 1000 * a;
		down = 1000 - a;
		if(up % down != 0)
			continue;
		if(500000 % down != 0)
			continue;
		b = up/down;
		c = 500000/down - a;

		printf("%d, %d, %d, product = %d\n", a, b, c, a*b*c);
	}
}

int main(void)
{
	find_pythagorean_triplet();
	return 0;
}
