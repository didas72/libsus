#ifndef SUS_HASHES_H_
#define SUS_HASHES_H_

#include "versioning.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Premade hash function for strings.
 * 
 * @param ptr String to hash.
 * @return size_t Calculated hash.
 * 
 * @remark Does not implement any known algorithm. Do not rely on it for any purpose other than hashtables.
 */
size_t hash_str(void *ptr);
/**
 * @brief Premade comparer function for strings.
 * 
 * @param ptr1 First string to compare.
 * @param ptr2 Second string to compare.
 * @return int Comparison result.
 */
int compare_str(void *ptr1, void *ptr2);
/**
 * @brief Premade hash function for pointers.
 * 
 * @param ptr String to hash.
 * @return size_t Calculated hash.
 * 
 * @remark Does not hash at all, simply returns the pointer itself.
 */
size_t hash_ptr(void *ptr);
/**
 * @brief Premade comparer function for pointers.
 * 
 * @param ptr1 First pointer to compare.
 * @param ptr2 Second pointer to compare.
 * @return int Comparison result.
 */
int compare_ptr(void *ptr1, void *ptr2);

#endif
