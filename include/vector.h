#ifndef SUS_VECTOR_H_
#define SUS_VECTOR_H_

#include "versioning.h"

#include <stddef.h>

#include "ivector.h"

#define VECTOR_DEFAULT_CAP 4

typedef ivector_t vector_t;

static inline vector_t *vector_create()
{ return ivector_create(sizeof(void *)); }
static inline int vector_destroy(vector_t *vec)
{ return ivector_destroy(vec); }
static inline int vector_destroy_free(vector_t *vec, void (*freer)(void *))
{ int err = ivector_iterate(vec, freer); return err ? err : ivector_destroy(vec); }
static inline vector_t *vector_duplicate(vector_t *vec)
{ return ivector_duplicate(vec); }
static inline vector_t *vector_from_range(vector_t *vec, size_t start, size_t count)
{ return ivector_from_range(vec, start, count); }

static inline int vector_ensure(vector_t *vec, size_t capacity)
{ return ivector_ensure(vec, capacity); }
static inline int vector_trim(vector_t *vec)
{ return ivector_trim(vec); }

static inline int vector_append(vector_t *vec, void *data)
{ return ivector_append(vec, &data); }
static inline int vector_append_vector(vector_t *vec, vector_t *src)
{ return ivector_append_vector(vec, src); }
static inline int vector_append_range(vector_t *vec, vector_t *src, size_t start, size_t count)
{ return ivector_append_range(vec, src, start, count); }
static inline int vector_push_front(vector_t *vec, void *data)
{ return ivector_push_front(vec, &data); }
static inline int vector_push_front_vector(vector_t *vec, vector_t *src)
{ return ivector_push_front_vector(vec, src); }
static inline int vector_pop_back(vector_t *vec)
{ return ivector_pop_back(vec); }
static inline int vector_insert_at(vector_t *vec, void *data, size_t index)
{ return ivector_insert_at(vec, &data, index); }
static inline int vector_remove_at(vector_t *vec, size_t index)
{ return ivector_remove_at(vec, index); }
static inline int vector_remove_range(vector_t *vec, size_t start, size_t count)
{ return ivector_remove_range(vec, start, count); }
static inline int vector_clear(vector_t *vec)
{ return ivector_clear(vec); }

static inline int vector_iterate(vector_t *vec, void (*func)(void *))
{ return ivector_iterate(vec, func); }
static inline vector_t *vector_get_all(vector_t *vec, int (*match)(void *, void *), void *arg)
{ return ivector_get_all(vec, match, arg); }
static inline size_t vector_remove(vector_t *vec, void *data)
{ return ivector_remove(vec, &data); }
static inline size_t vector_remove_all(vector_t *vec, int (*match)(void *, void *), void *arg)
{ return ivector_remove_all(vec, match, arg); }
static inline vector_t *vector_sort(vector_t *vec, int (*comparer)(void *, void *))
{ return ivector_sort(vec, comparer); }

#endif
