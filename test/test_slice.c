#include "slice.h"
#include "unity.h"


void setUp(void) {}
void tearDown(void) {}

void test_sliceOf(void)
{
	slice_t *slice;
	slice_t *sub_slice;
	int i;
	int slice_val;
	int sub_slice_val;

	slice = createSlice(sizeof(int), 0);

	for (i=0; i<4; i++) {
		appendSlice(slice, &i);
	}

	sub_slice = subSlice(slice, 2, 3);

	slice_val = *(int *)((char *)slice->arr + (2 * slice->element_size));
	sub_slice_val = *(int *)(sub_slice->arr);

	TEST_ASSERT_EQUAL_INT(slice_val, sub_slice_val );	

	freeSlice(slice, NULL);
	freeSlice(sub_slice, NULL);

}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_sliceOf);
	return UNITY_END();
}
