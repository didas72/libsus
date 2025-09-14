#include "unity/unity.h"
#include "ivector.h"

void setUp() {}
void tearDown() {}

void test_ivector_create_good()
{
	ivector_t *vec;

	vec = ivector_create(1);
	TEST_ASSERT_NOT_NULL(vec);

	vec = ivector_create(sizeof(int));
	TEST_ASSERT_NOT_NULL(vec);

	vec = ivector_create(256);
	TEST_ASSERT_NOT_NULL(vec);
}

void test_ivector_create_bad()
{
	ivector_t *vec;

	vec = ivector_create(0);
	TEST_ASSERT_NULL_MESSAGE(vec, "ivector_create allowed zero-sized elements");

	vec = ivector_create(1ul << 63);
	TEST_ASSERT_NULL_MESSAGE(vec, "ivector_create allowed planned failed allocation");
}

int main() {
	UNITY_BEGIN();

	RUN_TEST(test_ivector_create_good);
	RUN_TEST(test_ivector_create_bad);

	return UNITY_END();
}
