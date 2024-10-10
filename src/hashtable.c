#include "hashtable.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"


//Lowest primes above 64*4^i for hashtable growing
//Reaches 2^28, times 8B for pointers, which would make the hashtable alone ~2^31B = ~2GB
//If you reach this limit, the code still handles it but you should reconsider your life
#define HASTABLE_SIZE_COUNT 12
static const size_t hashtable_sizes[HASTABLE_SIZE_COUNT] = { 67, 257, 1031, 4099, 16411, 65537, 262147, 1048583, 4194319, 16777259, 67108879, 268435459 };
#define HASHTABLE_DEFAULT_CAP (hashtable_sizes[0])

static char hashtable_grow(hashtable_t *table)
{
	size_t target_size = 0;

	for (int i = 0; i < HASTABLE_SIZE_COUNT; i++)
	{
		target_size = hashtable_sizes[i];
		if (target_size > table->capacity) break;
	}

	while (target_size <= table->capacity) target_size <<= 2;

	return hashtable_resize(table, target_size);
}

hashtable_t *hashtable_create(size_t (*hasher)(void*), int (*comparer)(void*, void*))
{
	hashtable_t *table = malloc(sizeof(hashtable_t));
	if (!table) return NULL;

	table->entries = malloc(sizeof(hashtable_entry_t*) * HASHTABLE_DEFAULT_CAP);
	if (!table->entries) { free(table); return NULL; }
	
	memset(table->entries, 0, sizeof(hashtable_entry_t*) * HASHTABLE_DEFAULT_CAP);

	table->capacity = HASHTABLE_DEFAULT_CAP;
	table->count = 0;
	table->hasher = hasher;
	table->comparer = comparer;

	return table;
}

void hashtable_destroy(hashtable_t *table)
{
	hashtable_entry_t *entry, *tmp;

	for (size_t i = 0; i < table->capacity; i++)
	{
		entry = table->entries[i];
		
		while (entry)
		{
			tmp = entry;
			entry = entry->next;
			free(tmp);
		}
	}

	free(table->entries);
	free(table);
}

char hashtable_add(hashtable_t *table, void *key, void *value)
{
	if (table->count > table->capacity >> 1) //Force resize on 50% fill
	{
		hashtable_grow(table);
		//ignore failure, still able to proceed
	}

	size_t hash_index = table->hasher(key) % table->capacity;
	hashtable_entry_t *last_root = table->entries[hash_index];

	hashtable_entry_t *new_entry = malloc(sizeof(hashtable_entry_t));
	if (!new_entry) return 1;

	new_entry->content = value;
	new_entry->key = key;
	new_entry->next = last_root;
	table->entries[hash_index] = new_entry;
	table->count++;

	return 0;
}

void *hashtable_get(hashtable_t *table, void *key)
{
	size_t hash_index = table->hasher(key) % table->capacity;
	hashtable_entry_t *entry = table->entries[hash_index];

	if (entry == NULL)
		return NULL;

	while (entry->next != NULL && table->comparer(key, entry->key))
		entry = entry->next;

	return !table->comparer(key, entry->key) ? entry->content : NULL;
}

char hashtable_remove(hashtable_t *table, void *key, void **removed_key, void **removed_content)
{
	size_t hash_index = table->hasher(key) % table->capacity;
	hashtable_entry_t *entry = table->entries[hash_index], **ptr_store = &table->entries[hash_index];

	if (entry == NULL)
		return 1;

	while (entry->next != NULL && table->comparer(key, entry->key))
	{
		ptr_store = &entry->next;
		entry = entry->next;
	}

	if (table->comparer(key, entry->key))
		return 1;
	
	if (removed_key) *removed_key = entry->key;
	if (removed_content) *removed_content = entry->content;
	*ptr_store = entry->next;
	free(entry);
	return 0;
}

vector_t *hashtable_list_keys(hashtable_t *table)
{
	vector_t *ret = vector_create();
	if (!ret) return NULL;

	if (vector_ensure(ret, table->count))
	{
		vector_destroy(ret);
		return NULL;
	}

	for (size_t i = 0; i < table->capacity; i++)
	{
		hashtable_entry_t *entry = table->entries[i];

		while (entry)
		{
			vector_append(ret, entry->key);
			entry = entry->next;
		}
	}

	return ret;
}

vector_t *hashtable_list_contents(hashtable_t *table)
{
	vector_t *ret = vector_create();
	if (!ret) return NULL;

	if (vector_ensure(ret, table->count))
	{
		vector_destroy(ret);
		return NULL;
	}

	for (size_t i = 0; i < table->capacity; i++)
	{
		hashtable_entry_t *entry = table->entries[i];

		while (entry)
		{
			vector_append(ret, entry->content);
			entry = entry->next;
		}
	}

	return ret;
}

char hashtable_resize(hashtable_t *table, size_t capacity)
{
	if (table->capacity == capacity)
		return 0;

	vector_t *keys = hashtable_list_keys(table);
	if (!keys) return 1;
	vector_t *values = hashtable_list_contents(table);
	if (!values) { vector_destroy(keys); return 1; }

	hashtable_entry_t *entry, *prev;

	for (size_t i = 0; i < table->capacity; i++)
	{
		entry = table->entries[i];
		
		while (entry)
		{
			prev = entry;
			entry = entry->next;
			free(prev);
		}
	}

	hashtable_entry_t **tmp = malloc(capacity * sizeof(hashtable_entry_t*));
	if (!tmp) { vector_destroy(keys); vector_destroy(values); return 1; }

	memset(tmp, 0, sizeof(hashtable_entry_t*) * capacity);

	free(table->entries);
	table->entries = tmp;
	table->capacity = capacity;
	table->count = 0;

	for (size_t i = 0; i < keys->count; i++)
		hashtable_add(table, keys->data[i], values->data[i]);

	vector_destroy(keys);
	vector_destroy(values);

	return 0;
}

