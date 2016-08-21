#include <stdio.h>

#define MAX_SIZE 10000

int find_integer(int *array, int size, int value)
{
	if(size == 0)
		return -1;
	if(value < array[0])
		return -1;
	if(value > array[size - 1])
		return -1;

	return binary_search(array, 0, size - 1, value);
}

int binary_search(int *a, int start, int end, int value)
{
	int mid;
	if(start > end)
		return -1;

	mid = (end - start) / 2;
	mid = start + mid;
	
	if(a[mid] == value)
		return mid;
	else if(a[mid] > value)
		return binary_search(a, start, mid - 1, value);
	else /* a[mid] < value */
		return binary_search(a, mid + 1, end, value);
}

int main(void)
{
	int array[MAX_SIZE];
	int i, size, index;

	for(i = 0; i < MAX_SIZE; i++)
		array[i] = i;

	for(size = 0; size < MAX_SIZE; size++) {
		for(i = 0; i < size; i++) {
			index = find_integer(array, size, i);
			if(index != i)
				printf("Wrong integer! size=%d, expected=%d, found=%d\n", size, i, index);
		}
	}
	printf("Tests completed!\n");
	return 0;
}
