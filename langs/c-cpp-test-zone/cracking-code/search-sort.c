#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_A 100
#define MAX_B 100

/*
 * 9.1 Merge two sorted arrays. A has a large enough buffer ath the end to
 * contain B.
 */
void merge(int *a, int na, int *b, int nb)
{
	int i = na - 1;
	int j = nb - 1;
	int k = na + nb - 1;

	while(i >= 0 && j >= 0) {
		if(a[i] < b[j])
			a[k--] = b[j--];
		else
			a[k--] = a[i--];
	}

	while(j >= 0)
		a[k--] = b[j--];
}

void verify(int *a, int na)
{
	int i;
	for(i = 0; i < na - 1; i++)
		if(a[i] > a[i+1])
			printf("Error at %d\n", i);
}

void print(int *a, int na)
{
	int i;
	for(i = 0; i < na; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int comp(const void* a, const void* b)
{
	return *((int*)a) - *((int*)b);
}

void test_merge(void)
{
	int a[MAX_A + MAX_B];
	int b[MAX_B];
	int i;

	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));

	for(i = 0; i < MAX_A; i++)
		a[i] = random() % 1000;
	qsort(a, MAX_A, sizeof(int), comp);

	for(i = 0; i < MAX_B; i++)
		b[i] = random() % 1000;
	qsort(b, MAX_B, sizeof(int), comp);

	print(a, MAX_A);
	printf("\n");
	print(b, MAX_B);
	printf("\n");

	merge(a, MAX_A, b, MAX_B);

	verify(a, MAX_A + MAX_B);

	printf("\nSorted:\n");
	print(a, MAX_A + MAX_B);
}

/*
 * 9.3 Find element index in rotated, sorted array.
 */
int rotated_binary_search(int *a, int start, int end, int value)
{
	int mid;
	if(start > end)
		return -1;
	mid = (end - start) / 2;
	mid = mid + start;

	if(a[mid] == value)
		return mid;
	if(a[start] <= a[mid]) {
		if(a[start] <= value && value < a[mid])
			return rotated_binary_search(a, start, mid - 1, value);
		else
			return rotated_binary_search(a, mid + 1, end, value);
	} else {
		if(a[mid] < value && value <= a[end])
			return rotated_binary_search(a, mid + 1, end, value);
		else
			return rotated_binary_search(a, start, mid - 1, value);
	}
}

void test_rotated_bs(void)
{
	int a[] = { 12, 34, 55, 85, -14, -2, 3, 6, 7 };
	int i, index, n = 9;

	for(i = 0; i < n; i++) {
		index = rotated_binary_search(a, 0, n - 1, a[i]);
		if(index != i) {
			printf("Wrong index returned!\n");
			return;
		}
	}
	printf("Rotated binary search successful!\n");
}

int main(void)
{
	test_rotated_bs();
	return 0;
}
