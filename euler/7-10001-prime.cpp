#include <iostream>
#include <cmath>

int find_prime(int prime_index, int sieve_size)
{
	bool prime[sieve_size];
	int square_root;
	int count = 0;

	square_root = sqrt(sieve_size);

	for(int i = 0; i < sieve_size; i++)
		prime[i] = true;

	for(int i = 2; i < square_root; i++) {
		if(prime[i]) {
			for(int j = pow(i, 2); j < sieve_size; j += i)
				prime[j] = false;
		}
	}

	for(int i = 2; i < sieve_size; i++) {
		if(prime[i]) {
			count++;
			if(count == prime_index)
				return i;
		}
	}
	return -1;
}

int main(void)
{
	std::cout<<"Prime number no. 10001 is "<<find_prime(10001, 1000000)<<std::endl;
	return 0;
}
