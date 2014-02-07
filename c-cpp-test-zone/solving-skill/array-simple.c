#include <stdio.h>

void print_vector(int *vector, int n)
{
	int i;
	printf("{ ");
	for(i = 0; i < n - 1; i++)
		printf("%d, ", vector[i]);
	printf("%d }\n", vector[n - 1]);
}

int swap_zero(int* src, int* tgt, int n)
{
	int i, j;
	int zero, swp, count = 0;

	for(i = 0; i < n; i++) {
		if(src[i] == 0) {
			zero = i;
			break;
		}
	}

	for(i = 0; i < n; i++) {
		if(src[i] == tgt[i] || tgt[i] == 0)
			continue;

		for(j = 0; j < n; j++) {
			if(src[j] == tgt[i]) {
				swp = j;
				break;
			}
		}

		if(zero == i) {
			src[i] = src[swp];
			src[swp] = 0;
			zero = swp;
			print_vector(src, n);

			count++;
		} else {
			src[zero] = src[i];
			src[i] = 0;
			zero = i;
			print_vector(src, n);

			src[zero] = src[swp];
			src[swp] = 0;
			zero = swp;
			print_vector(src, n);

			count += 2;
		}
	}
	return count;
}

int main(void)
{
	int src[] = {2, 5, 3, 0, 1, 4};
	int tgt[] = {1, 2, 0, 5, 3, 4};
	int count;

	count = swap_zero(src, tgt, sizeof(src) / sizeof(int));

	printf("\nTarget:\n");
	print_vector(tgt, sizeof(src) / sizeof(int));
	printf("Total swaps: %d\n", count);
	return 0;
}
