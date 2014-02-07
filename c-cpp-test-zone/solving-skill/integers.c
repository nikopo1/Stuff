#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int count_twos(int n)
{
	int i, num_over, rem, sum = 0;

	for(i = 1; n / i * 10 > 0; i *= 10) {
		num_over = n / (i * 10);
		rem = n % (i * 10);
		sum += num_over * i;
		printf("%d %d %d\n", i, rem, sum);
		if(rem >= (2 * i))
			sum += MIN((rem - 2 * i + 1), i);
	}
	return sum;
}

int main(void)
{
	int x = 23;
	printf("Number of twos between 0 and n is %d\n", count_twos(x));
	return 0;
}
