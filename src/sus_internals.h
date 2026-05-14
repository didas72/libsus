#ifndef SUS_INTERNALS_H_
#define SUS_INTERNALS_H_

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct ivector_t
{
	void *data;
	size_t capacity;
	size_t count;
	size_t element_size;
};

typedef struct llist_entry_t llist_entry_t;

struct llist_entry_t
{
	llist_entry_t *next, *prev;
	void *content;
};

struct llist_t
{
	llist_entry_t *head, *tail;
	size_t count;
};

typedef struct hashtable_entry_t hashtable_entry_t;

struct hashtable_entry_t
{
	hashtable_entry_t *next;
	void *content;
	void *key;
};

struct hashtable_t
{
	hashtable_entry_t **entries;
	size_t capacity;
	size_t count;
	size_t (*hasher)(void*);
	int (*comparer)(void*, void*);
};

struct bitstream_t
{
	FILE *file;
	uint64_t buffer;
	int head;
	bool write;
};

#endif
