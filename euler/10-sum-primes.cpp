#include <iostream>
#include <cmath>

long sum_primes(int sieve_size)
{
	bool prime[sieve_size];
	int square_root;
	int count = 0;
	long sum = 0;

	square_root = sqrt(sieve_size);

	for(int i = 0; i < sieve_size; i++)
		prime[i] = true;

	for(int i = 2; i < square_root; i++) {
		if(prime[i]) {
			for(int j = pow(i, 2); j < sieve_size; j += i)
				prime[j] = false;
		}
	}

	for(long i = 2; i < sieve_size; i++) {
		if(prime[i]) {
			sum += i;
		}
	}
	return sum;
}

int main(void)
{
	std::cout<<"Sum of all primes < 2 million "<<sum_primes(2000000)<<std::endl;
	return 0;
}
