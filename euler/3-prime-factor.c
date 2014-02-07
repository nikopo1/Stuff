#include <stdio.h>

long long largest_prime_factor(long long number)
{
	long long i, factor = 1;
	if(number < 0)
		number *= -1;

	if(number == 0)
		return -1;

	/* 2 is the only even prime */
	if(number % 2 == 0) {
		factor = 2;
		while(number % 2 == 0)
			number = number / 2;
	}

	for(i = 3; i < number / 2;) {
		if(number % i == 0) {
			number = number / i;
			factor = i;
		} else {
			i += 2;
		}
	}

	if(number == 1)
		return factor;
	else
		return number;
}

int main(void)
{
	long long euler_project = 600851475143;

	printf("%d\n", largest_prime_factor(2));
	printf("%d\n", largest_prime_factor(-169));
	printf("%d\n", largest_prime_factor(321));
	printf("%d\n", largest_prime_factor(100));
	printf("%d\n", largest_prime_factor(0));
	
	printf("%d\n", largest_prime_factor(euler_project));
}
