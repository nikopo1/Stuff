#include <stdio.h>

int biggest_divider(int a, int b)
{
	while(a != b) {
		if(a > b)
			a -= b;
		else
			b -= a;
	}
	return a;
}

int smallest_multiple(int n)
{
	int i, addition, product = 1;
	for(i = n; i > 1; i--)
		if(product % i != 0) {
			addition = i / biggest_divider(product, i);
			product = product * addition;
		}
	return product;
}

int main(void)
{
	printf("10 : %d\n", smallest_multiple(10));
	printf("20 : %d\n", smallest_multiple(20));
	return 0;
}
