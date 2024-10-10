#ifndef SUS_HASHTABLE_H_
#define SUS_HASHTABLE_H_

#include <stddef.h>

#include "vector.h"

typedef struct hashtable_entry_t hashtable_entry_t;

typedef struct
{
	hashtable_entry_t **entries;
	size_t capacity;
	size_t count;
	size_t (*hasher)(void*);
	int (*comparer)(void*, void*);
} hashtable_t;

struct hashtable_entry_t
{
	hashtable_entry_t *next;
	void *content;
	void *key;
};

hashtable_t *hashtable_create(size_t (*hasher)(void*), int (*comparer)(void*, void*));
void hashtable_destroy(hashtable_t *table);
char hashtable_add(hashtable_t *table, void *key, void *value);
void *hashtable_get(hashtable_t *table, void *key);
char hashtable_remove(hashtable_t *table, void *key, void **removed_key, void **removed_content);
vector_t *hashtable_list_keys(hashtable_t *table);
vector_t *hashtable_list_contents(hashtable_t *table);
char hashtable_resize(hashtable_t *table, size_t capacity);

#endif
