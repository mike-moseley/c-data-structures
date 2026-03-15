#include "doubly_linked_list.h"
#include <stdlib.h>

doubly_linked_list_t *createDoublyLinkedList(void) {
	doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
	if(list == NULL) return NULL;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}
int freeDoublyLinkedList(doubly_linked_list_t *list,
                         void (*free_data)(void *)) {
	dnode_t *tracking_node;
	dnode_t *delete_node;

	if(list == NULL) {
		return 0;
	}
	if(list->head == NULL) {
		free(list);
		return 1;
	}

	tracking_node = list->head;
	while(tracking_node != NULL) {
		delete_node = tracking_node;
		tracking_node = tracking_node->next;
		if(free_data != NULL) {
			free_data(delete_node->data);
		}
		free(delete_node);
	}
	free(list);
	return 1;
}
int pushDNode(doubly_linked_list_t *list, void *data) {
	dnode_t *new_node;
	if(list == NULL) {
		return 0;
	}
	new_node = malloc(sizeof(dnode_t));
	if(new_node == NULL) {
		return 0;
	}
	new_node->data = data;
	new_node->next = list->head;
	new_node->prev = NULL;
	if(list->head != NULL) {
		list->head->prev = new_node;
	}
	if(list->size == 0) {
		list->tail = new_node;
	}
	list->head = new_node;
	list->size++;
	return 1;
}
int appendDNode(doubly_linked_list_t *list, void *data) {
	dnode_t *new_node;
	if(list == NULL) {
		return 0;
	}
	new_node = malloc(sizeof(dnode_t));
	if(new_node == NULL) {
		return 0;
	}
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = list->tail;
	if(list->tail != NULL) {
		list->tail->next = new_node;
	}
	if(list->size == 0) {
		list->head = new_node;
	}
	list->tail = new_node;
	list->size++;
	return 1;
}
int removeDNode(doubly_linked_list_t *list, void *target,
                int (*cmp)(void *, void *)) {
	dnode_t *tracking_node;
	dnode_t *previous_node;
	int found;

	found = 0;
	if(list == NULL) {
		return found;
	}
	if(target == NULL) {
		return found;
	}
	if(list->head == NULL) {
		return found;
	}
	if(list->tail == NULL) {
		return found;
	}
	if(cmp(list->head->data, target) == 0) {
		found = 1;
		previous_node = list->head;
		list->head = list->head->next;
		if(list->head != NULL) {
			list->head->prev = NULL;
		} else {
			list->tail = NULL;
		}
		free(previous_node);
		list->size--;
		return found;
	}
	tracking_node = list->head->next;
	previous_node = list->head;
	while(tracking_node != NULL) {
		if(cmp(tracking_node->data, target) == 0) {
			found = 1;
			if(tracking_node->next != NULL) {
				tracking_node->next->prev = previous_node;
			} else {
				list->tail = previous_node;
			}
			previous_node->next = tracking_node->next;
			free(tracking_node);
			list->size--;
			return found;
		} else {
			previous_node = tracking_node;
			tracking_node = tracking_node->next;
		}
	}

	return found;
}
dnode_t *findDNode(doubly_linked_list_t *list, void *target,
                   int (*cmp)(void *, void *)) {
	dnode_t *tracking_node;
	if(list == NULL) {
		return NULL;
	}
	if(target == NULL) {
		return NULL;
	}
	if(list->head == NULL) {
		return NULL;
	}
	if(list->tail == NULL) {
		return NULL;
	}

	tracking_node = list->head;
	while(tracking_node != NULL) {
		if(cmp(tracking_node->data, target) == 0) {
			return tracking_node;
		}
		tracking_node = tracking_node->next;
	}

	return NULL;
}
