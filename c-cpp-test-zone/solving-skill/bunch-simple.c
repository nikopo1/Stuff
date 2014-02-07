#include <stdio.h>
#include <stdlib.h>

long sum_integers(char *filepath)
{
	FILE *f;
	long sum = 0, val;

	f = fopen(filepath, "r");
	if(f == NULL) {
		perror("fopen");
		exit(-1);
	}

	while(fscanf(f, "%ld", &val) > 0) {
		sum += val;
	}

	return sum;
}

void print_mult_table(int n)
{
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("%4d", i * j);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	long sum;
	if(argc != 2) {
		printf("usage: %s <input file>\n", argv[0]);
		return -1;
	}

	sum = sum_integers(argv[1]);
	printf("Sum = %ld\n", sum);

	print_mult_table(13);

	return 0;
}
