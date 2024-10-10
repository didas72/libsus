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
void vector_destroy(vector_t *vec);
void vector_destroy_free(vector_t *vec, void (*freer)(void *));
vector_t *vector_duplicate(vector_t *vec);
char vector_ensure(vector_t *vec, size_t capacity);
char vector_trim(vector_t *vec);
char vector_append(vector_t *vec, void *data);
char vector_append_vector(vector_t *vec, vector_t *src);
size_t vector_get_count(vector_t *vec);
char vector_push_front(vector_t *vec, void *data);
char vector_push_front_vector(vector_t *vec, vector_t *src);
char vector_pop_back(vector_t *vec);
char vector_remove_at(vector_t *vec, size_t index);
vector_t *vector_get_all(vector_t *vec, int (*match)(void *));
size_t vector_remove_all(vector_t *vec, int (*match)(void *));
vector_t *vector_sort(vector_t *vec, int (*comparer)(void *, void *));

#endif
