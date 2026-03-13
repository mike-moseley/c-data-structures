#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "cds_types.h"

typedef struct Node {
	void *data;
	struct Node *next;
} node_t;

typedef struct LinkedList {
	struct Node *head;
	size_t size;
} linked_list_t;

linked_list_t *createLinkedList(void);
void freeLinkedList(linked_list_t* list, void(*free_data)(void *));
void pushNode(linked_list_t *list, void *data);
void appendNode(linked_list_t *list, void *data);
int removeNode(linked_list_t *list, void *target, int (*cmp)(void *, void *));
node_t *findNode(linked_list_t *list, void *target, int (*cmp)(void *, void *));

#endif
