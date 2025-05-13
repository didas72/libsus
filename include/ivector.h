#ifndef SUS_IVECTOR_H_
#define SUS_IVECTOR_H_

#include "versioning.h"

#include <stddef.h>

#define IVECTOR_DEFAULT_CAP 4

typedef struct ivector_t ivector_t;

ivector_t *ivector_create(size_t element_size);
int ivector_destroy(ivector_t *vec);
ivector_t *ivector_duplicate(ivector_t *vec);
ivector_t *ivector_from_range(ivector_t *vec, size_t start, size_t count);

int ivector_ensure(ivector_t *vec, size_t capacity);
int ivector_trim(ivector_t *vec);

int ivector_append(ivector_t *vec, void *data);
int ivector_append_vector(ivector_t *vec, ivector_t *src);
int ivector_append_range(ivector_t *vec, ivector_t *src, size_t start, size_t count);
int ivector_push_front(ivector_t *vec, void *data);
int ivector_push_front_vector(ivector_t *vec, ivector_t *src);
int ivector_pop_back(ivector_t *vec);
int ivector_insert_at(ivector_t *vec, void *data, size_t index);
int ivector_remove_at(ivector_t *vec, size_t index);
int ivector_remove_range(ivector_t *vec, size_t start, size_t count);
int ivector_clear(ivector_t *vec);

int ivector_iterate(ivector_t *vec, void (*func)(void *));
ivector_t *ivector_get_all(ivector_t *vec, int (*match)(void *, void *), void *arg);
size_t ivector_remove(ivector_t *vec, void *data);
size_t ivector_remove_all(ivector_t *vec, int (*match)(void *, void *), void *arg);
ivector_t *ivector_sort(ivector_t *vec, int (*comparer)(void *, void *));

size_t ivector_get_count(ivector_t *vec);
void *ivector_get(ivector_t *vec, size_t index);
int ivector_fetch(ivector_t *vec, size_t index, void *store);

#endif
