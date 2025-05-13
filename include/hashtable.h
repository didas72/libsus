#ifndef SUS_HASHTABLE_H_
#define SUS_HASHTABLE_H_

#include "versioning.h"

#include <stddef.h>

#include "vector.h"

typedef struct hashtable_t hashtable_t;

hashtable_t *hashtable_create(size_t (*hasher)(void*), int (*comparer)(void*, void*));
int hashtable_destroy(hashtable_t *table);
int hashtable_destroy_free(hashtable_t *table, void (*free_key)(void *), void (*free_value)(void *));

int hashtable_add(hashtable_t *table, void *key, void *value);
void *hashtable_get(hashtable_t *table, void *key);
int hashtable_remove(hashtable_t *table, void *key, void **removed_key, void **removed_content);

size_t hashtable_get_count(hashtable_t *table);
int hashtable_has_key(hashtable_t *table, void* key);

vector_t *hashtable_list_keys(hashtable_t *table);
vector_t *hashtable_list_contents(hashtable_t *table);

int hashtable_resize(hashtable_t *table, size_t capacity);

#endif
