#include <stdio.h>

#include "algorithm.h"


int compare_int(const void* param0, const void* param1)
{
    const int* x0 = param0;
    const int* x1 = param1;

    return *x0 - *x1;
}


int main(void)
{
    int array[100];

    for (int i = 0; i < 100; i++)
    {
        array[i] = i * 2;
    }

    for (int i = -20; i < 220; i++)
    {
        int* element = binary_search(array, 100, sizeof(int), &i, compare_int);
        if (element == NULL)
        {
            printf("Element %d not found\n", i);
        }
        else
        {
            printf("Element %d found at index %d, value %d\n", i,
                ((unsigned int)element - (unsigned int)array) / sizeof(int),
                *element);
        }
    }

    return 0;
}
