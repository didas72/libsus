#include "unity/unity.h"

#include <stdlib.h>

#include "sus.h"
#include "sus_internals.h"
#include "ivector.h"

void setUp() {}
void tearDown() {}

void test_ivector_create_good()
{
	ivector_t *vec;

	vec = ivector_create(1);
	TEST_ASSERT_NOT_NULL(vec);
	TEST_ASSERT_NOT_NULL(vec->data);
	TEST_ASSERT_EQUAL(vec->element_size, 1);

	vec = ivector_create(sizeof(int));
	TEST_ASSERT_NOT_NULL(vec);
	TEST_ASSERT_NOT_NULL(vec->data);
	TEST_ASSERT_EQUAL(vec->element_size, sizeof(int));

	vec = ivector_create(256);
	TEST_ASSERT_NOT_NULL(vec);
	TEST_ASSERT_NOT_NULL(vec->data);
	TEST_ASSERT_EQUAL(vec->element_size, 256);
}

void test_ivector_create_bad()
{
	ivector_t *vec;

	vec = ivector_create(0);
	TEST_ASSERT_NULL_MESSAGE(vec, "ivector_create allowed zero-sized elements");

	vec = ivector_create(1ul << 63);
	TEST_ASSERT_NULL_MESSAGE(vec, "ivector_create allowed planned failed allocation");
}

void test_ivector_destroy_good()
{
	ivector_t *vec = calloc(1, sizeof(ivector_t));
	int err;

	err = ivector_destroy(&vec);
	TEST_ASSERT_EQUAL(SUS_SUCCESS, err);
}

void test_ivector_destroy_bad()
{
	int err;

	err = ivector_destroy(NULL);
	TEST_ASSERT_EQUAL_MESSAGE(SUS_INVALID_ARG, err, "ivector_destroy allowed NULL vec");
}

void test_ivector_duplicate_good()
{
	TEST_IGNORE();
	
	ivector_t *vec = calloc(1, sizeof(ivector_t));
	int err;
	vec->capacity = 4;
	vec->count = 1;
	vec->data = calloc(1, sizeof(int));
	vec->element_size = sizeof(int);

	err = ivector_duplicate(vec);
	//TODO: Test

	free(vec);
}

int main() {
	UNITY_BEGIN();

	RUN_TEST(test_ivector_create_good);
	RUN_TEST(test_ivector_create_bad);
	RUN_TEST(test_ivector_destroy_good);
	RUN_TEST(test_ivector_destroy_bad);
	RUN_TEST(test_ivector_duplicate_good);

	return UNITY_END();
}
