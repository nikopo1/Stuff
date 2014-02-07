#include <stdio.h>

unsigned long long compute_even_fib_sum(unsigned long long maxfib)
{
	unsigned long long sum = 0;
	unsigned long long fib1 = 2;
	unsigned long long fib2 = 0;
	unsigned long long fib0 = fib1 + fib2;

	while(fib0 < maxfib) {
		sum += fib0;
		fib0 = 4*fib1 + fib2;
		printf("%llu\n", fib0);
		fib2 = fib1;
		fib1 = fib0;
	}

	return sum;
}

int main(void)
{
	unsigned long long n;
	printf("Give maxfib: ");
	scanf("%llu", &n);
	printf("Even sum for fib smaller than %u is %llu\n", n, compute_even_fib_sum(n));
	return 0;
}
