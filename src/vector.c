#include "vector.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "sus.h"



vector_t *vector_create()
{
	vector_t *ret = malloc(sizeof(vector_t));
	if (!ret) return NULL;

	ret->data = malloc(VECTOR_DEFAULT_CAP * sizeof(void *));
	if (!ret->data) { free(ret); return NULL; }

	ret->count = 0;
	ret->capacity = VECTOR_DEFAULT_CAP;

	return ret;
}

int vector_destroy(vector_t *vec)
{
	if (!vec) return SUS_INVALID_ARG;

	free(vec->data);
	free(vec);

	return SUS_SUCCESS;
}

int vector_destroy_free(vector_t *vec, void (*freer)(void *))
{
	if (!vec) return SUS_INVALID_ARG;
	if (!freer) return SUS_INVALID_ARG;

	for (size_t i = 0; i < vec->count; i++)
		freer(vec->data[i]);

	return vector_destroy(vec);
}

vector_t *vector_duplicate(vector_t *vec)
{
	if (!vec) return NULL;
	vector_t *ret = vector_create();
	if (!ret)
		return NULL;

	if (vector_ensure(ret, vec->count))
	{
		vector_destroy(ret);
		return NULL;
	}

	for (size_t i = 0; i < vec->count; i++)
		vector_append(ret, vec->data[i]);

	return ret;
}

int vector_ensure(vector_t *vec, size_t capacity)
{
	if (!vec) return SUS_INVALID_ARG;
	if (vec->capacity >= capacity) return SUS_SUCCESS;

	if (vec->capacity < VECTOR_DEFAULT_CAP) vec->capacity = VECTOR_DEFAULT_CAP;
	while (vec->capacity < capacity) vec->capacity <<= 1;

	void **tmp = realloc(vec->data, vec->capacity * sizeof(void *));
	if (!tmp) return SUS_FAILED_ALLOC;

	vec->data = tmp;
	return SUS_SUCCESS;
}

int vector_trim(vector_t *vec)
{
	if (!vec) return SUS_INVALID_ARG;
	if (vec->count == vec->capacity) return SUS_SUCCESS;

	void **tmp = realloc(vec->data, vec->count * sizeof(void *));
	if (!tmp) return SUS_FAILED_ALLOC;

	vec->data = tmp;
	vec->capacity = vec->count;
	return SUS_SUCCESS;
}

int vector_append(vector_t *vec, void *data)
{
	if (!vec) return SUS_INVALID_ARG;
	int err = vector_ensure(vec, vec->count + 1);
	if (err) return err;
	vec->data[vec->count++] = data;
	return SUS_SUCCESS;
}

int vector_append_vector(vector_t *vec, vector_t *src)
{
	if (!vec) return SUS_INVALID_ARG;
	int err = vector_ensure(vec, vec->count + src->count);
	if (err) return err;
	for (size_t i = 0; i < src->count; i++)
		vec->data[vec->count++] = src->data[i];
	return SUS_SUCCESS;
}

int vector_push_front(vector_t *vec, void *data)
{
	if (!vec) return SUS_INVALID_ARG;
	int err = vector_ensure(vec, vec->count + 1);
	if (err) return err;
	memmove(&vec->data[1], vec->data, (vec->count) * sizeof(void *));
	vec->data[0] = data;
	vec->count++;
	return SUS_SUCCESS;
}

int vector_push_front_vector(vector_t *vec, vector_t *src)
{
	if (!vec) return SUS_INVALID_ARG;

	int err = vector_ensure(vec, vec->count + src->count);
	if (err) return err;
	memmove(&vec->data[src->count], vec->data, (vec->count) * sizeof(void *));
	memcpy(vec->data, src->data, (src->count) * sizeof(void*));
	vec->count += src->count;
	return SUS_SUCCESS;
}

int vector_pop_back(vector_t *vec)
{
	if (!vec) return SUS_INVALID_ARG;

	if (!vec->count)
		return SUS_INVALID_INDEX;
	
	vec->count--;
	return SUS_SUCCESS;
}

int vector_remove_at(vector_t *vec, size_t index)
{
	if (!vec) return SUS_INVALID_ARG;

	if (index >= vec->count)
		return SUS_INVALID_INDEX;

	memmove(&vec->data[index], &vec->data[index + 1], (vec->count - index - 1) * sizeof(void *));
	vec->count--;
	return SUS_SUCCESS;
}

int vector_iterate(vector_t *vec, void (*func)(void *))
{
	if (!vec) return SUS_INVALID_ARG;
	if (!func) return SUS_INVALID_ARG;

	for (size_t i = 0; i < vec->count; i++)
		func(vec->data[i]);

	return SUS_SUCCESS;
}

vector_t *vector_get_all(vector_t *vec, int (*match)(void *))
{
	if (!vec) return NULL;
	if (!match) return NULL;

	vector_t *ret = vector_create();

	for (size_t i = 0; i < vec->count; i++)
		if (match(vec->data[i]))
			vector_append(ret, vec->data[i]);

	return ret;
}

size_t vector_remove_all(vector_t *vec, int (*match)(void *))
{
	if (!vec) return SUS_INVALID_ARG;
	if (!match) return SUS_INVALID_ARG;

	size_t counter = 0;

	for (size_t i = vec->count - 1; i < ~(size_t)0; i--)
	{
		if (match(vec->data[i]))
		{
			vector_remove_at(vec, i);
			counter++;
		}
	}

	return counter;
}

vector_t *vector_sort(vector_t *vec, int (*comparer)(void *, void *))
{
	if (!vec) return NULL;
	if (!comparer) return NULL;

	for (size_t gap = vec->count / 2; gap > 0; gap >>= 1)
	{
		for (size_t i = gap; i < vec->count; i++)
		{
			void *tmp = vec->data[i];

			size_t j;
			for (j = i; j >= gap && comparer(vec->data[j - gap], tmp) > 0; j -= gap)
				vec->data[j] = vec->data[j - gap];

			vec->data[j] = tmp;
		}
	}

	return vec;
}
