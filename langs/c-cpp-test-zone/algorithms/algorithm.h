/**
 * \file
 *
 * \brief Declarations for algorithm generic implementations.
 *
 * Copyright (c) 2016 VectorWatch. All rights reserved.
 */

#ifndef _ALGORITHM_H
#define _ALGORITHM_H


/**
 * \brief Perform a binary search on the given array and returns a pointer to the element.
 *
 * \param sorted_array  Pointer to a sorted array on which to do the binary search.
 * \param num           Number of entries stored in the sorted array.
 * \param size          Size of an entry in the sorted array, in bytes.
 * \param key           Pointer to a key, which is passed to the equals_fn to compare elements.
 * \param equals_fn     Comparison function used to search in the array.
 *
 * \return Element's address within the array, if found. Otherwise, NULL.
 */
void* binary_search(const void* sorted_array, int num, unsigned int size, const void* key,
        int (*equals_fn)(const void* array_element, const void* key));

#endif /* _ALGORITHM_H */
