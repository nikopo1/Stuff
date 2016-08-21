#include <stdio.h>
#include <stdlib.h>

int maximum_zero_sequence(int n)
{
	int count = 0, max = 0;

	while(n > 0) {
		if((n & 0x1) > 0)
			count = 0;
		else
			count++;
		if(count > max)
			max = count;
		n = n >> 1;
	}
	return max;
}

/*
 * 20.1
 */
int sum(int a, int b)
{
	int s, c;
	do {
		s = a ^ b;
		c = (a & b) << 1;
		a = s;
		b = c;
	} while(c != 0);
	return s;
}

char* get_binary_representation(int n)
{
	int i, p = 0;
	char *ret = calloc(32, sizeof(char));
	if(ret == NULL) {
		perror("calloc");
		exit(-1);
	}
	for(i = 31; i > 0; i--) {
		if((n & (1 << i)) > 0)
			ret[p++] = '1';
		else if(p > 0)
			ret[p++] = '0';
	}
	ret[31 - p] = 0;
	return ret;
}

void test_maximum_zero_sequence(void)
{
	int x = 0x85;
	char *binary = get_binary_representation(x);
	printf("Maximum length of zero sequence in %s is %d\n",
			binary,
			maximum_zero_sequence(x));
	free(binary);
}

void test_sum(void)
{
	int i, j, s, count = 0;
	for(i = -5; i < 6; i++)
		for(j = -5; j < 6; j++) {
			s = sum(i, j);
			if(s != i + j) {
				printf("Error %d + %d != %d\n", i, j, s);
				count++;
			}
		}
	if(count == 0)
		printf("Tests for sum without arithmetic operators successful!\n");
}

int main(void)
{
	test_sum();
	return 0;
}
