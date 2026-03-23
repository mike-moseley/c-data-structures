#include "cds_types.h"
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
	TEST_ASSERT_EQUAL_INT(CDS_OK, pushNode(list, NULL));
	free(list->head);
	free(list);
}
void test_pushNodeNullList(void) {
	linked_list_t *list;
	list = NULL;
	TEST_ASSERT_EQUAL_INT(CDS_ERR_NULL, pushNode(list, NULL));
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
	TEST_ASSERT_EQUAL_INT(CDS_OK, appendNode(list, NULL));
	freeLinkedList(list, NULL);
}
void test_appendNodeNullList(void) {
	linked_list_t *list;
	list = NULL;
	TEST_ASSERT_EQUAL_INT(CDS_ERR_NULL, appendNode(list, NULL));
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
	TEST_ASSERT_EQUAL_INT(3, list->size);
	removeNode(list, &int2, cmp_int);
	TEST_ASSERT_EQUAL_INT(2, list->size);
	TEST_ASSERT_EQUAL_INT(7,*(int *)list->head->data);
	TEST_ASSERT_EQUAL_INT(3,*(int *)list->head->next->data);
	freeLinkedList(list, NULL);
}
void test_removeNodeHead(void){
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
	TEST_ASSERT_EQUAL_INT(3, list->size);
	removeNode(list, &int3, cmp_int);
	TEST_ASSERT_EQUAL_INT(2, list->size);
	TEST_ASSERT_EQUAL_INT(5,*(int *)list->head->data);
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
	TEST_ASSERT_EQUAL_INT(3, list->size);
	error = removeNode(list, NULL, cmp_int);
	TEST_ASSERT_EQUAL_INT(CDS_ERR_NULL, error);
	TEST_ASSERT_EQUAL_INT(3, list->size);
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
	TEST_ASSERT_EQUAL_INT(2, list->size);
	error = removeNode(list, &int3, cmp_int);
	TEST_ASSERT_EQUAL_INT(CDS_ERR_NOT_FOUND, error);
	TEST_ASSERT_EQUAL_INT(2, list->size);
	freeLinkedList(list, NULL);
}
void test_removeNodeListNull(void) {
	linked_list_t *list;
	int int1;
	int error;
	list = NULL;
	int1 = 0;
	error = removeNode(list, &int1, cmp_int);
	TEST_ASSERT_EQUAL_INT(CDS_ERR_NULL, error);
}
void test_removeNodeListSingle(void) {
	linked_list_t *list;
	int int1;
	int error;
	list = createLinkedList();
	int1 = 7;
	pushNode(list, &int1);
	TEST_ASSERT_EQUAL_INT(1, list->size);
	error = removeNode(list, &int1, cmp_int);
	TEST_ASSERT_EQUAL_INT(CDS_OK, error);
	TEST_ASSERT_EQUAL_INT(0, list->size);
	freeLinkedList(list, NULL);
}

void test_findNode(void) {
	linked_list_t *list;
	node_t *node;
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
	node = findNode(list, &int1, cmp_int);
	TEST_ASSERT_EQUAL_INT(int1, *(int *)node->data);
	freeLinkedList(list, NULL);
}

void test_findNodeNull(void) {
	linked_list_t *list;
	node_t *node;
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
	node = findNode(list, NULL, cmp_int);
	TEST_ASSERT_NULL(node);
	freeLinkedList(list, NULL);
}
void test_findNodeDNE(void) {
	linked_list_t *list;
	node_t *node;
	int int1;
	int int2;
	int int3;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createLinkedList();
	pushNode(list, &int1);
	pushNode(list, &int2);
	node = findNode(list, &int3, cmp_int);
	TEST_ASSERT_NULL(node);
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
	RUN_TEST(test_removeNodeHead);
	RUN_TEST(test_removeNodeNull);
	RUN_TEST(test_removeNodeDNE);
	RUN_TEST(test_removeNodeListNull);
	RUN_TEST(test_removeNodeListSingle);
	RUN_TEST(test_findNode);
	RUN_TEST(test_findNodeNull);
	RUN_TEST(test_findNodeDNE);
	return UNITY_END();
}
