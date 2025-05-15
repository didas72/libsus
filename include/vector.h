#ifndef SUS_VECTOR_H_
#define SUS_VECTOR_H_

#include "versioning.h"

#include <stddef.h>

#include "ivector.h"

#define VECTOR_DEFAULT_CAP 4

typedef ivector_t vector_t;

/**
 * @brief Creates a new vector containing void*.
 * 
 * @return vector_t* The newly created vector or NULL if errored.
 */
static inline vector_t *vector_create()
{ return ivector_create(sizeof(void *)); }
/**
 * @brief Destroys a vector freeing associated memory.
 * 
 * @param vec The vector to destroy.
 * @return int Error code for the operation.
 */
static inline int vector_destroy(vector_t *vec)
{ return ivector_destroy(vec); }
/**
 * @brief Destroys a vector freeing associated memory. Also frees elements with the provided freer function.
 * 
 * @param vec The vector to destroy.
 * @param freer The element freer function.
 * @return int Error code for the operation.
 */
static inline int vector_destroy_free(vector_t *vec, void (*freer)(void *))
{ int err = ivector_iterate(vec, freer); return err ? err : ivector_destroy(vec); }
/**
 * @brief Creates a copy of a given vector.
 * 
 * @param vec The vector to duplicate.
 * @return vector_t* The newly created vector or NULL if errored.
 */
static inline vector_t *vector_duplicate(vector_t *vec)
{ return ivector_duplicate(vec); }
/**
 * @brief Creates a new vector from a subset of an existing one.
 * 
 * @param vec The existing vector to subset from.
 * @param start The first index to copy.
 * @param count The number of elements to copy.
 * @return vector_t* The newly created vector or NULL if errored.
 */
static inline vector_t *vector_from_range(vector_t *vec, size_t start, size_t count)
{ return ivector_from_range(vec, start, count); }

/**
 * @brief Ensures a minimum capacity for a given vector.
 * 
 * @param vec The vector whose capacity is to be ensured.
 * @param capacity The number of elements the vector should be ready to hold.
 * @return int Error code for the operation.
 * 
 * @remark This function is automatically called as needed when adding to the vector. It is mostly available for optimizations when the final or minimum vector size is known.
 */
static inline int vector_ensure(vector_t *vec, size_t capacity)
{ return ivector_ensure(vec, capacity); }
/**
 * @brief Reduces the capacity of a vector to the minimum necessary to hold it's current data.
 * 
 * @param vec The vector to be reduced.
 * @return int Error code for the operation.
 */
static inline int vector_trim(vector_t *vec)
{ return ivector_trim(vec); }

/**
 * @brief Appends an element to the given vector.
 * 
 * @param vec The vector to append to.
 * @param data The element to append.
 * @return int Error code for the operation.
 */
static inline int vector_append(vector_t *vec, void *data)
{ return ivector_append(vec, &data); }
/**
 * @brief Appends the contents of an vector to another vector.
 * 
 * @param vec The vector to append to.
 * @param src The vector whose contents are to be appended.
 * @return int Error code for the operation.
 */
static inline int vector_append_vector(vector_t *vec, vector_t *src)
{ return ivector_append_vector(vec, src); }
/**
 * @brief Appends a subset of an vector to another vector.
 * 
 * @param vec The vector to append to.
 * @param src The vector whose subset of contents are to be appended.
 * @param start The first index to append.
 * @param count The number of elements to append.
 * @return int Error code for the operation.
 */
static inline int vector_append_range(vector_t *vec, vector_t *src, size_t start, size_t count)
{ return ivector_append_range(vec, src, start, count); }
/**
 * @brief Prepends an element to a given vector.
 * 
 * @param vec The vector to prepend to.
 * @param data The element to prepend.
 * @return int Error code for the operation.
 */
static inline int vector_push_front(vector_t *vec, void *data)
{ return ivector_push_front(vec, &data); }
/**
 * @brief Prepends a subset of an vector to another vector.
 * 
 * @param vec The vector to prepend to.
 * @param src The vector whose subset of contents are to be prepended.
 * @return int Error code for the operation.
 */
static inline int vector_push_front_vector(vector_t *vec, vector_t *src)
{ return ivector_push_front_vector(vec, src); }
/**
 * @brief Removes an element from the end of a given vector.
 * 
 * @param vec The vector to remove from.
 * @return int Error code for the operation.
 */
static inline int vector_pop_back(vector_t *vec)
{ return ivector_pop_back(vec); }
/**
 * @brief Inserts an element at a given location in an vector.
 * 
 * @param vec The vector to insert into.
 * @param data The element to insert.
 * @param index The index of the newly inserted element.
 * @return int Error code for the operation.
 */
static inline int vector_insert_at(vector_t *vec, void *data, size_t index)
{ return ivector_insert_at(vec, &data, index); }
/**
 * @brief Removes the element at a given location from an vector.
 * 
 * @param vec The vector to remove from.
 * @param index The location of the element to remove.
 * @return int Error code for the operation.
 */
static inline int vector_remove_at(vector_t *vec, size_t index)
{ return ivector_remove_at(vec, index); }
/**
 * @brief Removes a subset of elements from a given vector.
 * 
 * @param vec The vector to remove from.
 * @param start The first index to remove.
 * @param count The number of elements to remove.
 * @return int Error code for the operation.
 */
static inline int vector_remove_range(vector_t *vec, size_t start, size_t count)
{ return ivector_remove_range(vec, start, count); }
/**
 * @brief Removes all elements from a given vector.
 * 
 * @param vec The vector to clear.
 * @return int Error code for the operation.
 */
static inline int vector_clear(vector_t *vec)
{ return ivector_clear(vec); }

/**
 * @brief Applies a given function to every element of a vector.
 * 
 * @param vec The vector to iterate.
 * @param func The function to apply to every element.
 * @param arg An auxiliar argument to pass to the iterated function.
 * @return int Error code for the operation.
 */
static inline int vector_iterate(vector_t *vec, void (*func)(void *))
{ return ivector_iterate(vec, func); }
/**
 * @brief Creates an vector containg all elements that match a given function.
 * 
 * @param vec The vector whose elements are to be checked.
 * @param match The matching function to be applied.
 * @param arg An auxiliar argument to pass to the matcher function.
 * @return vector_t* The created vector containing the matched elements.
 * 
 * @remark The returned vector should be destroyed after use.
 */
static inline vector_t *vector_get_all(vector_t *vec, int (*match)(void *, void *), void *arg)
{ return ivector_get_all(vec, match, arg); }
/**
 * @brief Removes all elements whose bytes match the provided data.
 * 
 * @param vec The vector to remove from.
 * @param data The data to look for.
 * @return size_t The number of elements removed or SUS_UNSIGNED_ERR if errored.
 */
static inline size_t vector_remove(vector_t *vec, void *data)
{ return ivector_remove(vec, &data); }
/**
 * @brief Removes all elements that match a given function.
 * 
 * @param vec The vector to remove from.
 * @param match The matching function to be applied.
 * @param arg An auxiliar argument to pass to the matched function.
 * @return size_t The number of elements removed or SUS_UNSIGNED_ERR if errored.
 */
static inline size_t vector_remove_all(vector_t *vec, int (*match)(void *, void *), void *arg)
{ return ivector_remove_all(vec, match, arg); }
/**
 * @brief Sorts the elements of an vector using a given comparer function.
 * 
 * @param vec The vector to sort.
 * @param comparer The comparer function to be used.
 * @return vector_t* The provided vector or NULL if errored.
 * 
 * @remark Should the function error out, the provided vector remains unchanged.
 */
static inline vector_t *vector_sort(vector_t *vec, int (*comparer)(void *, void *))
{ return ivector_sort(vec, comparer); }

/**
 * @brief Retrieves the number of elements present in a given vector.
 * 
 * @param vec The vector to check.
 * @return size_t The number of elements present.
 */
static inline size_t vector_get_count(vector_t *vec)
{ return ivector_get_count(vec); }
/**
 * @brief Retrieves a pointer to the element at a given index of an vector.
 * 
 * @param vec The vector to access.
 * @param index The index to access.
 * @return void* Pointer to the given element.
 */
static inline void *vector_get(vector_t *vec, size_t index)
{ return *(void**)ivector_get(vec, index); }

#endif
