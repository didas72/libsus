#include "ivector.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "sus.h"

#define ADDR(vec, idx) (void*)((char*)((vec)->data) + (idx) * (vec)->element_size)



ivector_t *ivector_create(size_t element_size)
{
	ivector_t *ret = malloc(sizeof(ivector_t));
	if (!ret) return NULL;

	ret->data = malloc(IVECTOR_DEFAULT_CAP * element_size);
	if (!ret->data) { free(ret); return NULL; }

	ret->count = 0;
	ret->capacity = IVECTOR_DEFAULT_CAP;
	ret->element_size = element_size;

	return ret;
}

int ivector_destroy(ivector_t *vec)
{
	if (!vec) return SUS_INVALID_ARG;

	free(vec->data);
	free(vec);

	return SUS_SUCCESS;
}

ivector_t *ivector_duplicate(ivector_t *vec)
{
	if (!vec) return NULL;
	ivector_t *ret = ivector_create(vec->element_size);
	if (!ret)
		return NULL;

	if (ivector_ensure(ret, vec->count))
	{
		ivector_destroy(ret);
		return NULL;
	}

	memcpy(ret->data, vec->data, vec->count * vec->element_size);
	ret->count = vec->count;

	return ret;
}

ivector_t *ivector_from_range(ivector_t *vec, size_t start, size_t count)
{
	if (!vec) return NULL;
	if (start + count >= vec->count) return NULL;

	ivector_t *ret = ivector_create(vec->element_size);
	if (!ret)
		return NULL;

	if (ivector_append_range(ret, vec, start, count))
	{
		ivector_destroy(ret);
		return NULL;
	}

	return ret;
}

int ivector_ensure(ivector_t *vec, size_t capacity)
{
	if (!vec) return SUS_INVALID_ARG;
	if (vec->capacity >= capacity) return SUS_SUCCESS;
	size_t old_capacity = vec->capacity;

	if (vec->capacity < IVECTOR_DEFAULT_CAP) vec->capacity = IVECTOR_DEFAULT_CAP;
	while (vec->capacity < capacity) vec->capacity <<= 1;

	void *tmp = realloc(vec->data, vec->capacity * vec->element_size);
	if (!tmp) 
	{
		vec->capacity = old_capacity;
		return SUS_FAILED_ALLOC;
	}

	vec->data = tmp;
	return SUS_SUCCESS;
}

int ivector_trim(ivector_t *vec)
{
	if (!vec) return SUS_INVALID_ARG;
	if (vec->count == vec->capacity) return SUS_SUCCESS;

	void *tmp = realloc(vec->data, vec->count * vec->element_size);
	if (!tmp) return SUS_FAILED_ALLOC;

	vec->data = tmp;
	vec->capacity = vec->count;
	return SUS_SUCCESS;
}

int ivector_append(ivector_t *vec, void *data)
{
	if (!vec) return SUS_INVALID_ARG;
	int err = ivector_ensure(vec, vec->count + 1);
	if (err) return err;

	memcpy(ADDR(vec, vec->count++), data, vec->element_size);
	return SUS_SUCCESS;
}

int ivector_append_vector(ivector_t *vec, ivector_t *src)
{
	if (!vec) return SUS_INVALID_ARG;
	if (!src) return SUS_INVALID_ARG;
	if (vec->element_size != src->element_size) return SUS_INCOMPATIBLE_IVECTORS;
	
	int err = ivector_ensure(vec, vec->count + src->count);
	if (err) return err;

	memcpy(ADDR(vec, vec->count), src->data, src->count * vec->element_size);
	vec->count += src->count;

	return SUS_SUCCESS;
}

int ivector_append_range(ivector_t *vec, ivector_t *src, size_t start, size_t count)
{
	if (!vec) return SUS_INVALID_ARG;
	if (!src) return SUS_INVALID_ARG;
	if (start + count >= src->count) return SUS_INVALID_RANGE;

	int err = ivector_ensure(vec, vec->count + count);
	if (err) return err;

	memcpy(ADDR(vec, vec->count), ADDR(src, start), count * vec->element_size);
	vec->count += count;

	return SUS_SUCCESS;
}

int ivector_push_front(ivector_t *vec, void *data)
{
	if (!vec) return SUS_INVALID_ARG;
	
	int err = ivector_ensure(vec, vec->count + 1);
	if (err) return err;
	memmove(ADDR(vec, 1), vec->data, (vec->count) * vec->element_size);
	memcpy(vec->data, data, vec->element_size);
	vec->count++;
	return SUS_SUCCESS;
}

int ivector_push_front_vector(ivector_t *vec, ivector_t *src)
{
	if (!vec) return SUS_INVALID_ARG;
	if (vec->element_size != src->element_size) return SUS_INCOMPATIBLE_IVECTORS;

	int err = ivector_ensure(vec, vec->count + src->count);
	if (err) return err;
	memmove(ADDR(vec, src->count), vec->data, (vec->count) * vec->element_size);
	memcpy(vec->data, src->data, (src->count) * vec->element_size);
	vec->count += src->count;
	return SUS_SUCCESS;
}

int ivector_pop_back(ivector_t *vec)
{
	if (!vec) return SUS_INVALID_ARG;

	if (!vec->count)
		return SUS_INVALID_INDEX;
	
	vec->count--;
	return SUS_SUCCESS;
}

int ivector_insert_at(ivector_t *vec, void *data, size_t index)
{ //REVIEW: Written at 2:51 am
	if (!vec) return SUS_INVALID_ARG;
	if (index > vec->count) return SUS_INVALID_INDEX;

	ivector_ensure(vec, vec->count+1);

	memmove(ADDR(vec, index+1), ADDR(vec, index), (vec->count - index) * vec->element_size);
	memcpy(ADDR(vec, index), data, vec->element_size);
	vec->count++;
	return SUS_SUCCESS;
}

int ivector_remove_at(ivector_t *vec, size_t index)
{
	if (!vec) return SUS_INVALID_ARG;

	if (index >= vec->count)
		return SUS_INVALID_INDEX;

	memmove(ADDR(vec, index), ADDR(vec, index + 1), (vec->count - index - 1) * vec->element_size);
	vec->count--;
	return SUS_SUCCESS;
}

int ivector_remove_range(ivector_t *vec, size_t start, size_t count)
{
	if (!vec) return SUS_INVALID_ARG;

	if (start + count >= vec->count)
		return SUS_INVALID_RANGE;

	memmove(ADDR(vec, start), ADDR(vec, start + count), (vec->count - start - count) * vec->element_size);
	vec->count -= count;
	return SUS_SUCCESS;
}

int ivector_clear(ivector_t *vec)
{
	if (!vec) return SUS_INVALID_ARG;

	vec->count = 0;
	return SUS_SUCCESS;
}

int ivector_iterate(ivector_t *vec, void (*func)(void *))
{
	if (!vec) return SUS_INVALID_ARG;
	if (!func) return SUS_INVALID_ARG;

	for (size_t i = 0; i < vec->count; i++)
		func(ADDR(vec, i));

	return SUS_SUCCESS;
}

ivector_t *ivector_get_all(ivector_t *vec, int (*match)(void *, void *), void *arg)
{
	if (!vec) return NULL;
	if (!match) return NULL;

	ivector_t *ret = ivector_create(vec->element_size);

	for (size_t i = 0; i < vec->count; i++)
		if (match(ADDR(vec, i), arg))
			ivector_append(ret, ADDR(vec, i));

	return ret;
}

size_t ivector_remove(ivector_t *vec, void *data)
{
	if (!vec) return SUS_INVALID_ARG;

	size_t counter = 0;

	for (size_t i = vec->count - 1; i < ~(size_t)0; i--)
	{
		if (memcmp(ADDR(vec, i), data, vec->element_size) == 0)
		{
			ivector_remove_at(vec, i);
			counter++;
		}
	}

	return counter;
}

size_t ivector_remove_all(ivector_t *vec, int (*match)(void *, void *), void *arg)
{
	if (!vec) return SUS_INVALID_ARG;
	if (!match) return SUS_INVALID_ARG;

	size_t counter = 0;

	for (size_t i = vec->count - 1; i < ~(size_t)0; i--)
	{
		if (match(ADDR(vec, i), arg))
		{
			ivector_remove_at(vec, i);
			counter++;
		}
	}

	return counter;
}

ivector_t *ivector_sort(ivector_t *vec, int (*comparer)(void *, void *))
{
	if (!vec) return NULL;
	if (!comparer) return NULL;

	for (size_t gap = vec->count / 2; gap > 0; gap >>= 1)
	{
		for (size_t i = gap; i < vec->count; i++)
		{
			void *tmp = ADDR(vec, i);

			size_t j;
			for (j = i; j >= gap && comparer(ADDR(vec, j - gap), tmp) > 0; j -= gap)
				memcpy(ADDR(vec, j), ADDR(vec, j - gap), vec->element_size);

			memcpy(ADDR(vec, j), tmp, vec->element_size);
		}
	}

	return vec;
}
