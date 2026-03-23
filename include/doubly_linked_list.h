#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "cds_types.h"

typedef struct DNode {
	void *data;
	struct DNode *next;
	struct DNode *prev;
} dnode_t;

typedef struct DoublyLinkedList {
	dnode_t *head;
	dnode_t *tail;
	size_t size;
} doubly_linked_list_t;

doubly_linked_list_t *createDoublyLinkedList(void);
cds_err_t freeDoublyLinkedList(doubly_linked_list_t* list, void(*free_data)(void *));
cds_err_t pushDNode(doubly_linked_list_t *list, void *data);
cds_err_t appendDNode(doubly_linked_list_t *list, void *data);
cds_err_t removeDNode(doubly_linked_list_t *list, void *target, int (*cmp)(void *, void *));
dnode_t *findDNode(doubly_linked_list_t *list, void *target, int (*cmp)(void *, void *));

#endif
