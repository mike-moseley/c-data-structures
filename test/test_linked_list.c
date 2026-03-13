#include "unity.h"
#include "linked_list.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_createLinkedList(void)
{
	linked_list_t *list;
	list = createLinkedList();

	TEST_ASSERT_TRUE(list != NULL);
	TEST_ASSERT_TRUE(list->head == NULL);
	TEST_ASSERT_TRUE(list->size == 0);
}
void test_pushNode(void) {
	linked_list_t *list;

	char *data1;
	char *data2;

	data1 = "Hello ";
	data2 = "World!";

	list = createLinkedList();

	pushNode(list, data2);
	pushNode(list, data1);

	TEST_ASSERT_EQUAL_INT(list->size,2);
	TEST_ASSERT_TRUE(list->head->data == data1);
	TEST_ASSERT_TRUE(list->head->next->data == data2);
	free(list->head->next);
	free(list->head);
	free(list);
}
void test_pushNodeNullData(void) {
	linked_list_t *list;
	list = createLinkedList();
	TEST_ASSERT_EQUAL_INT(1, pushNode(list, NULL));
	free(list->head);
	free(list);
}
void test_pushNodeNullList(void) {
	linked_list_t *list;
	list = NULL;
	TEST_ASSERT_EQUAL_INT(0, pushNode(list, NULL));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_createLinkedList);
	RUN_TEST(test_pushNode);
	RUN_TEST(test_pushNodeNullData);
	RUN_TEST(test_pushNodeNullList);
	return UNITY_END();
}
