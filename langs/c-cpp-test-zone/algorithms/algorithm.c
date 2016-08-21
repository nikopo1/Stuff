/**
 * \file
 *
 * \brief Definitions for generic algorithm implementations.
 *
 * Copyright (c) 2016 VectorWatch. All rights reserved.
 */

#include <stddef.h>


void* binary_search(const void* sorted_array, int num, unsigned int size, const void* key,
        int (*equals_fn)(const void* array_element, const void* key))
{
    int low = 0;
    int high = num - 1;
    int mid;
    int ret;

    while (low <= high)
    {
        mid = (high - low) / 2;
        mid += low;

        ret = equals_fn(sorted_array + mid * size, key);

        if (ret > 0)
            high = mid - 1;
        else if (ret < 0)
            low = mid + 1;
        else
            return (void*)sorted_array + mid * size;
    }

    return NULL;
}
