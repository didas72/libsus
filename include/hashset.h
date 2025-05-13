#ifndef SUS_HASHSET_H_
#define SUS_HASHSET_H_

#include "versioning.h"

#include <stddef.h>

#include "hashtable.h"
#include "vector.h"

typedef hashset_t hashset_t;

static inline hashset_t *hashset_create(size_t (*hasher)(void*), int (*comparer)(void*, void*))
{ return hashtable_create(hasher, comparer); }
static inline int hashset_destroy(hashset_t *set)
{ return hashtable_destroy(set); }
static inline int hashset_destroy_free(hashset_t *set, void (*freer)(void *))
{ return hashtable_destroy_free(set, freer, NULL); }

static inline int hashset_add(hashset_t *set, void *key)
{ return hashtable_add(set, key, NULL); }
static inline int hashset_remove(hashset_t *set, void *key, void **removed_key)
{ return hashtable_remove(set, key, removed_key, NULL); }

static inline size_t hashset_get_count(hashset_t *set)
{ return hashtable_get_count(set); }
static inline void *hashset_contains(hashset_t *set, void *key)
{ return hashtable_has_key(set, key); }

static inline vector_t *hashset_to_vector(hashset_t *set)
{ return hashtable_list_keys(set); }

static inline int hashset_resize(hashset_t *set, size_t capacity)
{ return hashtable_resize(set, capacity); }

#endif
