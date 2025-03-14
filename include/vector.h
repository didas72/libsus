#ifndef SUS_VECTOR_H_
#define SUS_VECTOR_H_

#include <stddef.h>

#define VECTOR_DEFAULT_CAP 4

typedef struct
{
	void **data;
	size_t capacity;
	size_t count;
} vector_t;

vector_t *vector_create();
int vector_destroy(vector_t *vec);
int vector_destroy_free(vector_t *vec, void (*freer)(void *));
vector_t *vector_duplicate(vector_t *vec);

int vector_ensure(vector_t *vec, size_t capacity);
int vector_trim(vector_t *vec);

int vector_append(vector_t *vec, void *data);
int vector_append_vector(vector_t *vec, vector_t *src);
int vector_push_front(vector_t *vec, void *data);
int vector_push_front_vector(vector_t *vec, vector_t *src);
int vector_pop_back(vector_t *vec);
int vector_insert_at(vector_t *vec, void *data, size_t index);
int vector_remove_at(vector_t *vec, size_t index);
int vector_clear(vector_t *vec);

int vector_iterate(vector_t *vec, void (*func)(void *));
vector_t *vector_get_all(vector_t *vec, int (*match)(void *, void *), void *arg);
size_t vector_remove(vector_t *vec, void *data);
size_t vector_remove_all(vector_t *vec, int (*match)(void *, void *), void *arg);
vector_t *vector_sort(vector_t *vec, int (*comparer)(void *, void *));

#endif
