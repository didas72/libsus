#include "vector.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>



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

void vector_destroy(vector_t *vec)
{
	free(vec->data);
	free(vec);
}

vector_t *vector_duplicate(vector_t *vec)
{
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

char vector_ensure(vector_t *vec, size_t capacity)
{
	if (vec->capacity >= capacity) return 0;

	if (vec->capacity < VECTOR_DEFAULT_CAP) vec->capacity = VECTOR_DEFAULT_CAP;
	while (vec->capacity < capacity) vec->capacity <<= 1;

	void **tmp = realloc(vec->data, vec->capacity * sizeof(void *));
	if (!tmp) return 1;

	vec->data = tmp;
	return 0;
}

char vector_trim(vector_t *vec)
{
	if (vec->count == vec->capacity) return 0;

	void **tmp = realloc(vec->data, vec->count * sizeof(void *));
	if (!tmp) return 1;

	vec->data = tmp;
	vec->capacity = vec->count;
	return 0;
}

char vector_append(vector_t *vec, void *data)
{
	if (vector_ensure(vec, vec->count + 1)) return 1;
	vec->data[vec->count++] = data;
	return 0;
}

char vector_append_vector(vector_t *vec, vector_t *src)
{
	if (vector_ensure(vec, vec->count + src->count)) return 1;
	for (size_t i = 0; i < src->count; i++)
		vec->data[vec->count++] = src->data[i];
	return 0;
}

size_t vector_get_count(vector_t *vec)
{
	return vec->count;
}

char vector_push_front(vector_t *vec, void *data)
{
	if (vector_ensure(vec, vec->count + 1)) return 1;
	memmove(&vec->data[1], vec->data, (vec->count) * sizeof(void *));
	vec->data[0] = data;
	vec->count++;
	return 0;
}

char vector_push_front_vector(vector_t *vec, vector_t *src)
{
	if (vector_ensure(vec, vec->count + src->count)) return 1;
	memmove(&vec->data[src->count], vec->data, (vec->count) * sizeof(void *));
	memcpy(vec->data, src->data, (src->count) * sizeof(void*));
	vec->count += src->count;
	return 0;
}

char vector_pop_back(vector_t *vec)
{
	if (!vec->count)
		return 1;
	
	vec->count--;
	return 0;
}

char vector_remove_at(vector_t *vec, size_t index)
{
	if (index >= vec->count)
		return 1;

	memmove(&vec->data[index], &vec->data[index + 1], (vec->count - index - 1) * sizeof(void *));
	vec->count--;
	return 0;
}

vector_t *vector_get_all(vector_t *vec, int (*match)(void *))
{
	vector_t *ret = vector_create();

	for (size_t i = 0; i < vec->count; i++)
		if (match(vec->data[i]))
			vector_append(ret, vec->data[i]);

	return ret;
}

size_t vector_remove_all(vector_t *vec, int (*match)(void *))
{
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
