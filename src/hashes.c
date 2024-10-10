#include "hashes.h"

#include <stddef.h>
#include <string.h>

size_t hash_str(void *ptr)
{
	char *str = ptr;
	size_t hash = *str;

	while (*(++str)) hash = hash * 41 + *str;

	return hash;
}
int compare_str(void *ptr1, void *ptr2)
{
	return strcmp((char *)ptr1, (char *)ptr2);
}
size_t hash_ptr(void *ptr)
{
	return (size_t)ptr;
}
int compare_ptr(void *ptr1, void *ptr2)
{
	return ptr1 == ptr2 ? 0 : (ptr1 > ptr2 ? 1 : -1);
}
