#include "unity.h"
#include "linked_list.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}
/*
Comparison casting void* to int* for when the nodes contain ints
*/
int cmp_int(void *a, void *b) {
	if (a == NULL || b == NULL) {
		return 1;
	}
	return *(int *)a - *(int *)b;
}

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

void test_appendNode(void) {
	linked_list_t *list;
	char *data1;
	char *data2;

	list = createLinkedList();

	data1 = "Hello ";
	data2 = "World!";
	appendNode(list, data1);
	appendNode(list, data2);

	TEST_ASSERT_EQUAL_INT(list->size,2);
	TEST_ASSERT_TRUE(list->head->data == data1);
	TEST_ASSERT_TRUE(list->head->next->data == data2);
	freeLinkedList(list, NULL);
}
void test_appendNodeNullData(void) {
	linked_list_t *list;
	list = createLinkedList();
	TEST_ASSERT_EQUAL_INT(1, appendNode(list, NULL));
	freeLinkedList(list, NULL);
}
void test_appendNodeNullList(void) {
	linked_list_t *list;
	list = NULL;
	TEST_ASSERT_EQUAL_INT(0, appendNode(list, NULL));
}
void test_removeNode(void){
	linked_list_t *list;
	int int1;
	int int2;
	int int3;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createLinkedList();
	pushNode(list, &int1);
	pushNode(list, &int2);
	pushNode(list, &int3);
	removeNode(list, &int2, cmp_int);
	TEST_ASSERT_EQUAL_INT(7,*(int *)list->head->data);
	TEST_ASSERT_EQUAL_INT(3,*(int *)list->head->next->data);
	freeLinkedList(list, NULL);
}
void test_removeNodeNull(void) {
	linked_list_t *list;
	int int1;
	int int2;
	int int3;
	int error;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createLinkedList();
	pushNode(list, &int1);
	pushNode(list, &int2);
	pushNode(list, &int3);
	error = removeNode(list, NULL, cmp_int);
	TEST_ASSERT_EQUAL_INT(0, error);
	freeLinkedList(list, NULL);
}
void test_removeNodeDNE(void) {
	linked_list_t *list;
	int int1;
	int int2;
	int int3;
	int error;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createLinkedList();
	pushNode(list, &int1);
	pushNode(list, &int2);
	error = removeNode(list, &int3, cmp_int);
	TEST_ASSERT_EQUAL_INT(0, error);
	freeLinkedList(list, NULL);
}
void test_removeNodeListNull(void) {
	linked_list_t *list;
	int int1;
	int error;
	list = NULL;
	int1 = 0;
	error = removeNode(list, &int1, cmp_int);
	TEST_ASSERT_EQUAL_INT(0, error);
	freeLinkedList(list, NULL);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_createLinkedList);
	RUN_TEST(test_pushNode);
	RUN_TEST(test_pushNodeNullData);
	RUN_TEST(test_pushNodeNullList);
	RUN_TEST(test_appendNode);
	RUN_TEST(test_appendNodeNullData);
	RUN_TEST(test_appendNodeNullList);
	RUN_TEST(test_removeNode);
	RUN_TEST(test_removeNodeNull);
	RUN_TEST(test_removeNodeDNE);
	RUN_TEST(test_removeNodeListNull);
	return UNITY_END();
}
