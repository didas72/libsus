#ifndef SUS_HASHTABLE_H_
#define SUS_HASHTABLE_H_

#include "versioning.h"

#include <stddef.h>

#include "vector.h"

typedef struct hashtable_t hashtable_t;

/**
 * @brief Creates a new hashtable with the given hasher and comparer functions.
 * 
 * @param hasher The key hashing function to be used.
 * @param comparer The key comparing function to be used.
 * @return hashtable_t* The newly created hashtable or NULL if errored.
 */
hashtable_t *hashtable_create(size_t (*hasher)(void*), int (*comparer)(void*, void*));
/**
 * @brief Destroys a hashtable freeing associated memory.
 * 
 * @param table The hashtable to destroy.
 * @return int Error code for the operation.
 */
int hashtable_destroy(hashtable_t *table);
/**
 * @brief Destroys a hashtable freeing associated memory. Also frees keys and values with the provided freer functions.
 * 
 * @param table The hashtable to destroy.
 * @param free_key The key freer function.
 * @param free_value The value freer function.
 * @return int Error code for the operation.
 */
int hashtable_destroy_free(hashtable_t *table, void (*free_key)(void *), void (*free_value)(void *));

/**
 * @brief Adds a key value pair to a hashtable.
 * 
 * @param table The hashtable to add to.
 * @param key The new key to insert.
 * @param value The new value to insert.
 * @return int Error code for the operation.
 */
int hashtable_add(hashtable_t *table, void *key, void *value);
/**
 * @brief Attempts to retreive the value associated with the given key from the hashtable.
 * 
 * @param table The hashtable to access.
 * @param key The key to search for.
 * @return void* The value associated with the searched key, or NULL if key is not found.
 */
void *hashtable_get(hashtable_t *table, void *key);
/**
 * @brief Attempts to remove a key value pair from a hashtable.
 * 
 * @param table The hashtable to remove from.
 * @param key The key to search for.
 * @param removed_key Destination for the pointer to the found key.
 * @param removed_content Destination for the pointer to the associated value.
 * @return int Error code for the opertation.
 * 
 * @remark Both pointer destinations may be NULL if they are not to be filled.
 */
int hashtable_remove(hashtable_t *table, void *key, void **removed_key, void **removed_content);

/**
 * @brief Retrieves the number of key value pairs present in the hashtable.
 * 
 * @param table The hashtable to check.
 * @return size_t The number of elements present.
 */
size_t hashtable_get_count(hashtable_t *table);
/**
 * @brief Checks whether a given key is present in the hashtable.
 * 
 * @param table The hashtable to check.
 * @param key The key to look for.
 * @return int Return code or error code for the operation.
 */
int hashtable_has_key(hashtable_t *table, void* key);

/**
 * @brief Creates a vector with the keys present in the hashtable.
 * 
 * @param table The hashtable whose keys are to be listed.
 * @return vector_t* The created vector containing the keys or NULL if errored.
 * 
 * @remark The returned vector should be destroyed after use.
 */
vector_t *hashtable_list_keys(hashtable_t *table);

/**
 * @brief Creates a vector with the values present in the hashtable.
 * 
 * @param table The hashtable whose values are to be listed.
 * @return vector_t* The created vector containing the values or NULL if errored.
 * 
 * @remark The returned vector should be destroyed after use.
 */
vector_t *hashtable_list_contents(hashtable_t *table);

/**
 * @brief [READ REMARK] Resizes the hashtable to a given number of buckets.
 * 
 * @param table The hashtable to resize.
 * @param capacity The new number of buckets.
 * @return int Error code for the operation.
 * 
 * @remark This function is automatically called as needed when adding to the hashtable. There is generally no need to call this function manually.
 */
int hashtable_resize(hashtable_t *table, size_t capacity);

#endif
