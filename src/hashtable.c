#include "hashtable.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "sus.h"
#include "vector.h"


//Lowest primes above 64*4^i for hashtable growing
//Reaches 2^28, times 8B for pointers, which would make the hashtable alone ~2^31B = ~2GB
//If you reach this limit, the code still handles it but you should reconsider your life
#define HASTABLE_SIZE_COUNT 12
static const size_t hashtable_sizes[HASTABLE_SIZE_COUNT] = { 67, 257, 1031, 4099, 16411, 65537, 262147, 1048583, 4194319, 16777259, 67108879, 268435459 };
#define HASHTABLE_DEFAULT_CAP (hashtable_sizes[0])

static int hashtable_grow(hashtable_t *table)
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
	if (!hasher) return NULL;
	if (!comparer) return NULL;

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

int hashtable_destroy(hashtable_t *table)
{
	if (!table) return SUS_INVALID_ARG;

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

	return SUS_SUCCESS;
}

int hashtable_destroy_free(hashtable_t *table, void (*free_key)(void *), void (*free_value)(void *))
{
	if (!table) return SUS_INVALID_ARG;

	hashtable_entry_t *entry, *tmp;
	for (size_t i = 0; i < table->capacity; i++)
	{
		entry = table->entries[i];
		
		while (entry)
		{
			if (free_key) free_key(entry->key);
			if (free_value) free_value(entry->content);
			tmp = entry;
			entry = entry->next;
			free(tmp);
		}
	}

	free(table->entries);
	free(table);

	return SUS_SUCCESS;
}

int hashtable_add(hashtable_t *table, void *key, void *value)
{
	if (!table) return SUS_INVALID_ARG;

	if (table->count > table->capacity >> 1) //Force resize on 50% fill
	{
		hashtable_grow(table);
		//ignore failure, still able to proceed
	}

	size_t hash_index = table->hasher(key) % table->capacity;
	hashtable_entry_t *last_root = table->entries[hash_index];

	hashtable_entry_t *new_entry = malloc(sizeof(hashtable_entry_t));
	if (!new_entry) return SUS_FAILED_ALLOC;

	new_entry->content = value;
	new_entry->key = key;
	new_entry->next = last_root;
	table->entries[hash_index] = new_entry;
	table->count++;

	return SUS_SUCCESS;
}

void *hashtable_get(hashtable_t *table, void *key)
{
	if (!table) return NULL;

	size_t hash_index = table->hasher(key) % table->capacity;
	hashtable_entry_t *entry = table->entries[hash_index];

	if (entry == NULL)
		return NULL;

	while (entry->next != NULL && table->comparer(key, entry->key))
		entry = entry->next;

	return !table->comparer(key, entry->key) ? entry->content : NULL;
}

int hashtable_remove(hashtable_t *table, void *key, void **removed_key, void **removed_content)
{
	if (!table) return SUS_INVALID_ARG;

	size_t hash_index = table->hasher(key) % table->capacity;
	hashtable_entry_t *entry = table->entries[hash_index], **ptr_store = &table->entries[hash_index];

	if (entry == NULL)
		return SUS_ENTRY_NOT_FOUND;

	while (entry->next != NULL && table->comparer(key, entry->key))
	{
		ptr_store = &entry->next;
		entry = entry->next;
	}

	if (table->comparer(key, entry->key))
		return SUS_ENTRY_NOT_FOUND;
	
	if (removed_key) *removed_key = entry->key;
	if (removed_content) *removed_content = entry->content;
	*ptr_store = entry->next;
	free(entry);
	return SUS_SUCCESS;
}

vector_t *hashtable_list_keys(hashtable_t *table)
{
	if (!table) return NULL;

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
	if (!table) return NULL;

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

int hashtable_resize(hashtable_t *table, size_t capacity)
{
	if (!table) return SUS_INVALID_ARG;

	if (table->capacity == capacity)
		return SUS_SUCCESS;

	vector_t *keys = hashtable_list_keys(table);
	if (!keys) return SUS_FAILED_ALLOC;
	vector_t *values = hashtable_list_contents(table);
	if (!values) { vector_destroy(keys); return SUS_FAILED_ALLOC; }

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
	if (!tmp) { vector_destroy(keys); vector_destroy(values); return SUS_FAILED_ALLOC; }

	memset(tmp, 0, sizeof(hashtable_entry_t*) * capacity);

	free(table->entries);
	table->entries = tmp;
	table->capacity = capacity;
	table->count = 0;

	for (size_t i = 0; i < keys->count; i++)
		hashtable_add(table, keys->data[i], values->data[i]);

	vector_destroy(keys);
	vector_destroy(values);

	return SUS_SUCCESS;
}

