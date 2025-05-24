#ifndef SUS_HASHSET_H_
#define SUS_HASHSET_H_

#include "versioning.h"

#include <stddef.h>

#include "hashtable.h"
#include "vector.h"

typedef hashtable_t hashset_t;

/**
 * @brief Creates a new hashset with the given hasher and comparer functions.
 * 
 * @param hasher The hashing function to be used.
 * @param comparer The comparing function to be used.
 * @return hashset_t* The newly created hashset or NULL if errored.
 */
static inline hashset_t *hashset_create(size_t (*hasher)(void*), int (*comparer)(void*, void*))
{ return hashtable_create(hasher, comparer); }
/**
 * @brief Destroys a hashset freeing associated memory.
 * 
 * @param set The hashset to destroy.
 * @return int Error code for the operation.
 */
static inline int hashset_destroy(hashset_t *set)
{ return hashtable_destroy(set); }
/**
 * @brief Destroys a hashset freeing associated memory. Also frees keys with the provided freer function.
 * 
 * @param set The hashset to destroy.
 * @param free The freer function.
 * @return int Error code for the operation.
 */
static inline int hashset_destroy_free(hashset_t *set, void (*freer)(void *))
{ return hashtable_destroy_free(set, freer, NULL); }

/**
 * @brief Adds a key to a hashset.
 * 
 * @param set The hashset to add to.
 * @param key The new key to insert.
 * @return int Error code for the operation.
 */
static inline int hashset_add(hashset_t *set, void *key)
{ return hashtable_add(set, key, NULL); }
/**
 * @brief Attempts to remove a key from a hashset.
 * 
 * @param set The hashset to remove from.
 * @param key The key to search for.
 * @param removed_key Destination for the pointer to the found key.
 * @return int Error code for the opertation.
 * 
 * @remark The pointer destination may be NULL if it is not to be filled.
 */
static inline int hashset_remove(hashset_t *set, void *key, void **removed_key)
{ return hashtable_remove(set, key, removed_key, NULL); }

/**
 * @brief Retrieves the number of keys present in the hashset.
 * 
 * @param set The hashset to check.
 * @return size_t The number of keys present.
 */
static inline size_t hashset_get_count(hashset_t *set)
{ return hashtable_get_count(set); }
/**
 * @brief Checks whether a given key is present in the hashset.
 * 
 * @param set The hashset to check.
 * @param key The key to look for.
 * @return int Return code or error code for the operation.
 */
static inline int hashset_contains(hashset_t *set, void *key)
{ return hashtable_has_key(set, key); }

/**
 * @brief Creates a vector with the keys present in the hashset.
 * 
 * @param set The hashset whose keys are to be listed.
 * @return vector_t* The created vector containing the keys or NULL if errored.
 * 
 * @remark The returned vector should be destroyed after use.
 */
static inline vector_t *hashset_to_vector(hashset_t *set)
{ return hashtable_list_keys(set); }

/**
 * @brief [READ REMARK] Resizes the hashset to a given number of buckets.
 * 
 * @param set The hashset to resize.
 * @param capacity The new number of buckets.
 * @return int Error code for the operation.
 * 
 * @remark This function is automatically called as needed when adding to the hashset. There is generally no need to call this function manually.
 */
static inline int hashset_resize(hashset_t *set, size_t capacity)
{ return hashtable_resize(set, capacity); }

#endif
