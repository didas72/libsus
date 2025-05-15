#ifndef SUS_IVECTOR_H_
#define SUS_IVECTOR_H_

#include "versioning.h"

#include <stddef.h>

#define IVECTOR_DEFAULT_CAP 4

typedef struct ivector_t ivector_t;

/**
 * @brief Creates a new ivector with elemets element_size bytes long.
 * 
 * @param element_size The size of each vector element.
 * @return ivector_t* The newly created ivector or NULL if errored.
 */
ivector_t *ivector_create(size_t element_size);
/**
 * @brief Destroys an ivector freeing associated memory.
 * 
 * @param vec The ivector to destroy.
 * @return int Error code for the operation.
 */
int ivector_destroy(ivector_t *vec);
/**
 * @brief Creates a copy of a given ivector.
 * 
 * @param vec The ivector to duplicate.
 * @return ivector_t* The newly created ivector or NULL if errored.
 */
ivector_t *ivector_duplicate(ivector_t *vec);
/**
 * @brief Creates a new ivector from a subset of an existing one.
 * 
 * @param vec The existing ivector to subset from.
 * @param start The first index to copy.
 * @param count The number of elements to copy.
 * @return ivector_t* The newly created ivector or NULL if errored.
 */
ivector_t *ivector_from_range(ivector_t *vec, size_t start, size_t count);

/**
 * @brief Ensures a minimum capacity for a given ivector.
 * 
 * @param vec The ivector whose capacity is to be ensured.
 * @param capacity The number of elements the ivector should be ready to hold.
 * @return int Error code for the operation.
 * 
 * @remark This function is automatically called as needed when adding to the ivector. It is mostly available for optimizations when the final or minimum ivector size is known.
 */
int ivector_ensure(ivector_t *vec, size_t capacity);
/**
 * @brief Reduces the capacity of an ivector to the minimum necessary to hold it's current data.
 * 
 * @param vec The ivector to be reduced.
 * @return int Error code for the operation.
 */
int ivector_trim(ivector_t *vec);

/**
 * @brief Appends an element to the given ivector.
 * 
 * @param vec The ivector to append to.
 * @param data The element to append.
 * @return int Error code for the operation.
 */
int ivector_append(ivector_t *vec, void *data);
/**
 * @brief Appends the contents of an ivector to another ivector.
 * 
 * @param vec The ivector to append to.
 * @param src The ivector whose contents are to be appended.
 * @return int Error code for the operation.
 */
int ivector_append_vector(ivector_t *vec, ivector_t *src);
/**
 * @brief Appends a subset of an ivector to another ivector.
 * 
 * @param vec The ivector to append to.
 * @param src The ivector whose subset of contents are to be appended.
 * @param start The first index to append.
 * @param count The number of elements to append.
 * @return int Error code for the operation.
 */
int ivector_append_range(ivector_t *vec, ivector_t *src, size_t start, size_t count);
/**
 * @brief Prepends an element to a given ivector.
 * 
 * @param vec The ivector to prepend to.
 * @param data The element to prepend.
 * @return int Error code for the operation.
 */
int ivector_push_front(ivector_t *vec, void *data);
/**
 * @brief Prepends a subset of an ivector to another ivector.
 * 
 * @param vec The ivector to prepend to.
 * @param src The ivector whose subset of contents are to be prepended.
 * @return int Error code for the operation.
 */
int ivector_push_front_vector(ivector_t *vec, ivector_t *src);
/**
 * @brief Removes an element from the end of a given ivector.
 * 
 * @param vec The ivector to remove from.
 * @return int Error code for the operation.
 */
int ivector_pop_back(ivector_t *vec);
/**
 * @brief Inserts an element at a given location in an ivector.
 * 
 * @param vec The ivector to insert into.
 * @param data The element to insert.
 * @param index The index of the newly inserted element.
 * @return int Error code for the operation.
 */
int ivector_insert_at(ivector_t *vec, void *data, size_t index);
/**
 * @brief Removes the element at a given location from an ivector.
 * 
 * @param vec The ivector to remove from.
 * @param index The location of the element to remove.
 * @return int Error code for the operation.
 */
int ivector_remove_at(ivector_t *vec, size_t index);
/**
 * @brief Removes a subset of elements from a given ivector.
 * 
 * @param vec The ivector to remove from.
 * @param start The first index to remove.
 * @param count The number of elements to remove.
 * @return int Error code for the operation.
 */
int ivector_remove_range(ivector_t *vec, size_t start, size_t count);
/**
 * @brief Removes all elements from a given ivector.
 * 
 * @param vec The vector to clear.
 * @return int Error code for the operation.
 */
int ivector_clear(ivector_t *vec);

/**
 * @brief Applies a given function to every element of an ivector.
 * 
 * @param vec The ivector to iterate.
 * @param func The function to apply to every element.
 * @param arg An auxiliar argument to pass to the iterated function.
 * @return int Error code for the operation.
 */
int ivector_iterate(ivector_t *vec, void (*func)(void *));
/**
 * @brief Creates an ivector containg all elements that match a given function.
 * 
 * @param vec The ivector whose elements are to be checked.
 * @param match The matching function to be applied.
 * @param arg An auxiliar argument to pass to the matcher function.
 * @return ivector_t* The created ivector containing the matched elements.
 * 
 * @remark The returned ivector should be destroyed after use.
 */
ivector_t *ivector_get_all(ivector_t *vec, int (*match)(void *, void *), void *arg);
/**
 * @brief Removes all elements whose bytes match the provided data.
 * 
 * @param vec The ivector to remove from.
 * @param data The data to look for.
 * @return size_t The number of elements removed or SUS_UNSIGNED_ERR if errored.
 */
size_t ivector_remove(ivector_t *vec, void *data);
/**
 * @brief Removes all elements that match a given function.
 * 
 * @param vec The ivector to remove from.
 * @param match The matching function to be applied.
 * @param arg An auxiliar argument to pass to the matched function.
 * @return size_t The number of elements removed or SUS_UNSIGNED_ERR if errored.
 */
size_t ivector_remove_all(ivector_t *vec, int (*match)(void *, void *), void *arg);
/**
 * @brief Sorts the elements of an ivector using a given comparer function.
 * 
 * @param vec The ivector to sort.
 * @param comparer The comparer function to be used.
 * @return ivector_t* The provided ivector or NULL if errored.
 * 
 * @remark Should the function error out, the provided ivector remains unchanged.
 */
ivector_t *ivector_sort(ivector_t *vec, int (*comparer)(void *, void *));

/**
 * @brief Retrieves the number of elements present in a given ivector.
 * 
 * @param vec The ivector to check.
 * @return size_t The number of elements present.
 */
size_t ivector_get_count(ivector_t *vec);
/**
 * @brief Retrieves a pointer to the element at a given index of an ivector.
 * 
 * @param vec The ivector to access.
 * @param index The index to access.
 * @return void* Pointer to the given element.
 */
void *ivector_get(ivector_t *vec, size_t index);
/**
 * @brief Retrieves the element at a given index of an ivector to a buffer.
 * 
 * @param vec The ivector to access.
 * @param index The index to access.
 * @param store The buffer to read to.
 * @return int Error code for the operation.
 */
int ivector_fetch(ivector_t *vec, size_t index, void *store);

#endif
