#ifndef SUS_HASHES_H_
#define SUS_HASHES_H_

#include "versioning.h"

#include <stddef.h>
#include <stdint.h>

size_t hash_str(void *ptr);
int compare_str(void *ptr1, void *ptr2);
//[DEPRECATED] Use ivector instead of casting keys to void*
_SUS_DEPRECATED_
size_t hash_ptr(void *ptr);
//[DEPRECATED] Use ivector instead of casting keys to void*
_SUS_DEPRECATED_
int compare_ptr(void *ptr1, void *ptr2);

#endif
