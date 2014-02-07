#include <stdio.h>

int is_palindrome(int number)
{
	int number_r = 0;
	int temp = 0;
	int digit = 0;

	temp = number;
	while(temp != 0) {
		digit = temp % 10;
		number_r = number_r * 10 + digit;
		temp /= 10;
	}
	return number - number_r;
}

void biggest_pair()
{
	int i, j;
	int max = 0, best_i, best_j, prod;

	for(i = 999; i > 0; i--)
		for(j = 999; j > i; j--) {
			prod = i * j;
			if(prod > max && is_palindrome(prod) == 0) {
				max = prod;
				best_i = i;
				best_j = j;
			}
		}

	printf("Best(i, j) = (%d, %d); Prod = %d\n", best_i, best_j, max);
}

int main(void)
{
	biggest_pair();
	return 0;
}
