#include <stdio.h>

long fib(int n)
{
	long f0, f1, f2;
	int i;

	if(n < 0)
		return -1;

	f0 = 0;
	f1 = 1;
	for(i = 0; i < n; i++) {
		f2 = f0 + f1;
		f0 = f1;
		f1 = f2;
	}
	return f0;
}

long fib_rec(int n)
{
	if(n <= 1)
		return n;
	else
		return fib_rec(n - 2) + fib_rec(n - 1);
}

int main(void)
{
	int i;
	int n = 35;

	for(i = 0; i < n; i++)
		printf("%ld ", fib(i));
	printf("\n");

	for(i = 0; i < n; i++)
		printf("%ld ", fib_rec(i));
	printf("\n");

	return 0;
}
