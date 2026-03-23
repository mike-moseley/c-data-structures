#include "cds_types.h"
#include "doubly_linked_list.h"
#include "unity.h"
#include <stdlib.h>

void
setUp (void)
{
}
void
tearDown (void)
{
}

/*
Comparison casting void* to int* for when the nodes contain ints
*/
int
cmp_int (void *a, void *b)
{
	if (a == NULL || b == NULL)
	{
		return 1;
	}
	return *(int *)a - *(int *)b;
}

void
test_createDoublyLinkedList (void)
{
	doubly_linked_list_t *list;
	list = createDoublyLinkedList ();

	TEST_ASSERT_TRUE (list != NULL);
	TEST_ASSERT_TRUE (list->head == NULL);
	TEST_ASSERT_TRUE (list->tail == NULL);
	TEST_ASSERT_TRUE (list->size == 0);
}

void
test_pushDNode (void)
{
	doubly_linked_list_t *list;
	char *data1;
	char *data2;

	data1 = "Hello ";
	data2 = "World!";

	list = createDoublyLinkedList ();

	pushDNode (list, data2);
	pushDNode (list, data1);

	TEST_ASSERT_EQUAL_INT (2, list->size);
	TEST_ASSERT_TRUE (list->head->data == data1);
	TEST_ASSERT_TRUE (list->head->next->data == data2);
	TEST_ASSERT_TRUE (list->tail->data == data2);
	TEST_ASSERT_TRUE (list->tail->prev->data == data1);
	freeDoublyLinkedList (list, NULL);
}

void
test_pushDNodeNullData (void)
{
	doubly_linked_list_t *list;
	list = createDoublyLinkedList ();
	TEST_ASSERT_EQUAL_INT (CDS_OK, pushDNode (list, NULL));
	freeDoublyLinkedList (list, NULL);
}

void
test_pushDNodeNullList (void)
{
	doubly_linked_list_t *list;
	list = NULL;
	TEST_ASSERT_EQUAL_INT (CDS_ERR_NULL, pushDNode (list, NULL));
}

void
test_appendDNode (void)
{
	doubly_linked_list_t *list;
	char *data1;
	char *data2;

	list = createDoublyLinkedList ();

	data1 = "Hello ";
	data2 = "World!";
	appendDNode (list, data1);
	appendDNode (list, data2);

	TEST_ASSERT_EQUAL_INT (2, list->size);
	TEST_ASSERT_TRUE (list->head->data == data1);
	TEST_ASSERT_TRUE (list->head->next->data == data2);
	TEST_ASSERT_TRUE (list->tail->data == data2);
	TEST_ASSERT_TRUE (list->tail->prev->data == data1);
	freeDoublyLinkedList (list, NULL);
}

void
test_appendDNodeNullData (void)
{
	doubly_linked_list_t *list;
	list = createDoublyLinkedList ();
	TEST_ASSERT_EQUAL_INT (CDS_OK, appendDNode (list, NULL));
	freeDoublyLinkedList (list, NULL);
}

void
test_appendDNodeNullList (void)
{
	doubly_linked_list_t *list;
	list = NULL;
	TEST_ASSERT_EQUAL_INT (CDS_ERR_NULL, appendDNode (list, NULL));
}

void
test_removeDNode (void)
{
	doubly_linked_list_t *list;
	int int1;
	int int2;
	int int3;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createDoublyLinkedList ();
	pushDNode (list, &int1);
	pushDNode (list, &int2);
	pushDNode (list, &int3);
	TEST_ASSERT_EQUAL_INT (3, list->size);
	removeDNode (list, &int2, cmp_int);
	TEST_ASSERT_EQUAL_INT (2, list->size);
	TEST_ASSERT_EQUAL_INT (7, *(int *)list->head->data);
	TEST_ASSERT_EQUAL_INT (3, *(int *)list->head->next->data);
	TEST_ASSERT_EQUAL_INT (3, *(int *)list->tail->data);
	TEST_ASSERT_EQUAL_INT (7, *(int *)list->tail->prev->data);
	freeDoublyLinkedList (list, NULL);
}

void
test_removeDNodeHead (void)
{
	doubly_linked_list_t *list;
	int int1;
	int int2;
	int int3;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createDoublyLinkedList ();
	pushDNode (list, &int1);
	pushDNode (list, &int2);
	pushDNode (list, &int3);
	TEST_ASSERT_EQUAL_INT (3, list->size);
	removeDNode (list, &int3, cmp_int);
	TEST_ASSERT_EQUAL_INT (2, list->size);
	TEST_ASSERT_EQUAL_INT (5, *(int *)list->head->data);
	TEST_ASSERT_EQUAL_INT (3, *(int *)list->head->next->data);
	TEST_ASSERT_TRUE (list->head->prev == NULL);
	TEST_ASSERT_EQUAL_INT (3, *(int *)list->tail->data);
	TEST_ASSERT_EQUAL_INT (5, *(int *)list->tail->prev->data);
	freeDoublyLinkedList (list, NULL);
}

void
test_removeDNodeTail (void)
{
	doubly_linked_list_t *list;
	int int1;
	int int2;
	int int3;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createDoublyLinkedList ();
	pushDNode (list, &int1);
	pushDNode (list, &int2);
	pushDNode (list, &int3);
	TEST_ASSERT_EQUAL_INT (3, list->size);
	removeDNode (list, &int1, cmp_int);
	TEST_ASSERT_EQUAL_INT (2, list->size);
	TEST_ASSERT_EQUAL_INT (7, *(int *)list->head->data);
	TEST_ASSERT_EQUAL_INT (5, *(int *)list->head->next->data);
	TEST_ASSERT_TRUE (list->head->prev == NULL);
	TEST_ASSERT_EQUAL_INT (5, *(int *)list->tail->data);
	TEST_ASSERT_EQUAL_INT (7, *(int *)list->tail->prev->data);
	TEST_ASSERT_TRUE (list->head->next->next == NULL);
	freeDoublyLinkedList (list, NULL);
}

void
test_removeDNodeNull (void)
{
	doubly_linked_list_t *list;
	int int1;
	int int2;
	int int3;
	int error;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createDoublyLinkedList ();
	pushDNode (list, &int1);
	pushDNode (list, &int2);
	pushDNode (list, &int3);
	TEST_ASSERT_EQUAL_INT (3, list->size);
	error = removeDNode (list, NULL, cmp_int);
	TEST_ASSERT_EQUAL_INT (CDS_ERR_NULL, error);
	TEST_ASSERT_EQUAL_INT (3, list->size);
	freeDoublyLinkedList (list, NULL);
}

void
test_removeDNodeDNE (void)
{
	doubly_linked_list_t *list;
	int int1;
	int int2;
	int int3;
	int error;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createDoublyLinkedList ();
	pushDNode (list, &int1);
	pushDNode (list, &int2);
	TEST_ASSERT_EQUAL_INT (2, list->size);
	error = removeDNode (list, &int3, cmp_int);
	TEST_ASSERT_EQUAL_INT (CDS_ERR_NOT_FOUND, error);
	TEST_ASSERT_EQUAL_INT (2, list->size);
	freeDoublyLinkedList (list, NULL);
}

void
test_removeDNodeListNull (void)
{
	doubly_linked_list_t *list;
	int int1;
	int error;
	list = NULL;
	int1 = 0;
	error = removeDNode (list, &int1, cmp_int);
	TEST_ASSERT_EQUAL_INT (CDS_ERR_NULL, error);
}

void
test_removeDNodeSingle (void)
{
	doubly_linked_list_t *list;
	int int1;
	int error;
	list = createDoublyLinkedList ();
	int1 = 7;
	pushDNode (list, &int1);
	TEST_ASSERT_EQUAL_INT (1, list->size);
	error = removeDNode (list, &int1, cmp_int);
	TEST_ASSERT_EQUAL_INT (CDS_OK, error);
	TEST_ASSERT_EQUAL_INT (0, list->size);
	TEST_ASSERT_TRUE (list->head == NULL);
	TEST_ASSERT_TRUE (list->tail == NULL);
	freeDoublyLinkedList (list, NULL);
}

void
test_findDNode (void)
{
	doubly_linked_list_t *list;
	dnode_t *node;
	int int1;
	int int2;
	int int3;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createDoublyLinkedList ();
	pushDNode (list, &int1);
	pushDNode (list, &int2);
	pushDNode (list, &int3);
	node = findDNode (list, &int1, cmp_int);
	TEST_ASSERT_EQUAL_INT (int1, *(int *)node->data);
	freeDoublyLinkedList (list, NULL);
}

void
test_findDNodeNull (void)
{
	doubly_linked_list_t *list;
	dnode_t *node;
	int int1;
	int int2;
	int int3;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createDoublyLinkedList ();
	pushDNode (list, &int1);
	pushDNode (list, &int2);
	pushDNode (list, &int3);
	node = findDNode (list, NULL, cmp_int);
	TEST_ASSERT_NULL (node);
	freeDoublyLinkedList (list, NULL);
}

void
test_findDNodeDNE (void)
{
	doubly_linked_list_t *list;
	dnode_t *node;
	int int1;
	int int2;
	int int3;
	int1 = 3;
	int2 = 5;
	int3 = 7;
	list = createDoublyLinkedList ();
	pushDNode (list, &int1);
	pushDNode (list, &int2);
	node = findDNode (list, &int3, cmp_int);
	TEST_ASSERT_NULL (node);
	freeDoublyLinkedList (list, NULL);
}

int
main (void)
{
	UNITY_BEGIN ();
	RUN_TEST (test_createDoublyLinkedList);
	RUN_TEST (test_pushDNode);
	RUN_TEST (test_pushDNodeNullData);
	RUN_TEST (test_pushDNodeNullList);
	RUN_TEST (test_appendDNode);
	RUN_TEST (test_appendDNodeNullData);
	RUN_TEST (test_appendDNodeNullList);
	RUN_TEST (test_removeDNode);
	RUN_TEST (test_removeDNodeHead);
	RUN_TEST (test_removeDNodeTail);
	RUN_TEST (test_removeDNodeNull);
	RUN_TEST (test_removeDNodeDNE);
	RUN_TEST (test_removeDNodeListNull);
	RUN_TEST (test_removeDNodeSingle);
	RUN_TEST (test_findDNode);
	RUN_TEST (test_findDNodeNull);
	RUN_TEST (test_findDNodeDNE);
	return UNITY_END ();
}
