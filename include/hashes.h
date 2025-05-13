#ifndef SUS_HASHES_H_
#define SUS_HASHES_H_

#include "versioning.h"

#include <stddef.h>
#include <stdint.h>

size_t hash_str(void *ptr);
int compare_str(void *ptr1, void *ptr2);
//Used when casting key to void*
size_t hash_ptr(void *ptr);
//Used when casting key to void*
int compare_ptr(void *ptr1, void *ptr2);

#endif
