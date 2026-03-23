#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "cds_types.h"

typedef struct Node {
	void *data;
	struct Node *next;
} node_t;

typedef struct LinkedList {
	node_t *head;
	size_t size;
} linked_list_t;

linked_list_t *createLinkedList(void);
cds_err_t freeLinkedList(linked_list_t* list, void(*free_data)(void *));
cds_err_t pushNode(linked_list_t *list, void *data);
cds_err_t appendNode(linked_list_t *list, void *data);
cds_err_t removeNode(linked_list_t *list, void *target, int (*cmp)(void *, void *));
node_t *findNode(linked_list_t *list, void *target, int (*cmp)(void *, void *));

#endif
