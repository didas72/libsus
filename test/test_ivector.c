#include <stdlib.h>

#include "unity.h"

#include "sus.h"
#include "sus_internals.h"
#include "ivector.h"

#ifndef TEST_CASE
#define TEST_CASE(...)
#endif
#ifndef TEST_RANGE
#define TEST_RANGE(...)
#endif
#ifndef TEST_MATRIX
#define TEST_MATRIX(...)
#endif

TEST_CASE(sizeof(int))
TEST_CASE(1)
TEST_CASE(256)
void test_ivector_create_good(size_t element_size)
{
	ivector_t *vec;

	vec = ivector_create(element_size);
	TEST_ASSERT_NOT_NULL(vec);
	TEST_ASSERT_NOT_NULL(vec->data);
	TEST_ASSERT_EQUAL(element_size, vec->element_size);
}

void test_ivector_create_bad()
{
	ivector_t *vec;

	//Zero-sized elements
	vec = ivector_create(0);
	TEST_ASSERT_NULL_MESSAGE(vec, "ivector_create allowed zero-sized elements");

	//Too large elements (guaranteed to fail malloc)
	vec = ivector_create(1ul << 50);
	TEST_ASSERT_NULL_MESSAGE(vec, "ivector_create allowed planned failed allocation");
}

void test_ivector_destroy_good()
{
	ivector_t *vec = calloc(1, sizeof(ivector_t));
	int err;

	//Simple destroy
	err = ivector_destroy(vec);
	TEST_ASSERT_EQUAL(SUS_SUCCESS, err);
}

void test_ivector_destroy_bad()
{
	int err;

	//NULL destroy
	err = ivector_destroy(NULL);
	TEST_ASSERT_EQUAL_MESSAGE(SUS_INVALID_ARG, err, "ivector_destroy allowed NULL vec");
}

TEST_MATRIX([sizeof(int), 1], [1, 4, 16, 25])
void test_ivector_duplicate_good(size_t element_size, size_t count)
{	
	ivector_t *new, *old;
	
	//Fake ivector setup
	old = calloc(1, sizeof(ivector_t));
	old->capacity = count;
	old->count = count;
	old->data = calloc(count, element_size);
	old->element_size = element_size;

	//Actual test
	new = ivector_duplicate(old);
	TEST_ASSERT_NOT_NULL(new);
	TEST_ASSERT_GREATER_OR_EQUAL(count, new->capacity);
	TEST_ASSERT_EQUAL(count, new->count);
	TEST_ASSERT_NOT_NULL(new->data);
	TEST_ASSERT_EQUAL(element_size, new->element_size);

	//Fake ivector cleanup
	free(old->data);
	free(old);
}
