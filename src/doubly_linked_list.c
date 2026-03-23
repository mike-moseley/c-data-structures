#include "doubly_linked_list.h"
#include "cds_types.h"
#include <stdlib.h>

doubly_linked_list_t *createDoublyLinkedList(void) {
	doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
	if(list == NULL) return NULL;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}
cds_err_t freeDoublyLinkedList(doubly_linked_list_t *list,
                         void (*free_data)(void *)) {
	dnode_t *tracking_node;
	dnode_t *delete_node;

	if(list == NULL) {
		return CDS_ERR_NULL;
	}
	if(list->head == NULL) {
		free(list);
		return CDS_OK;
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
	return CDS_OK;
}
cds_err_t pushDNode(doubly_linked_list_t *list, void *data) {
	dnode_t *new_node;
	if(list == NULL) {
		return CDS_ERR_NULL;
	}
	new_node = malloc(sizeof(dnode_t));
	if(new_node == NULL) {
		return CDS_ERR_OOM;
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
	return CDS_OK;
}
cds_err_t appendDNode(doubly_linked_list_t *list, void *data) {
	dnode_t *new_node;
	if(list == NULL) {
		return CDS_ERR_NULL;
	}
	new_node = malloc(sizeof(dnode_t));
	if(new_node == NULL) {
		return CDS_ERR_OOM;
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

	return CDS_OK;
}
cds_err_t removeDNode(doubly_linked_list_t *list, void *target,
                int (*cmp)(void *, void *)) {
	dnode_t *tracking_node;
	dnode_t *previous_node;

	if(list == NULL) {
		return CDS_ERR_NULL;
	}
	if(target == NULL) {
		return CDS_ERR_NULL;
	}
	if(list->head == NULL) {
		return CDS_ERR_NULL;
	}
	if(list->tail == NULL) {
		return CDS_ERR_NULL;
	}
	if(cmp(list->head->data, target) == 0) {
		previous_node = list->head;
		list->head = list->head->next;
		if(list->head != NULL) {
			list->head->prev = NULL;
		} else {
			list->tail = NULL;
		}
		free(previous_node);
		list->size--;
		return CDS_OK;
	}
	tracking_node = list->head->next;
	previous_node = list->head;
	while(tracking_node != NULL) {
		if(cmp(tracking_node->data, target) == 0) {
			if(tracking_node->next != NULL) {
				tracking_node->next->prev = previous_node;
			} else {
				list->tail = previous_node;
			}
			previous_node->next = tracking_node->next;
			free(tracking_node);
			list->size--;
			return CDS_OK;
		} else {
			previous_node = tracking_node;
			tracking_node = tracking_node->next;
		}
	}

	return CDS_ERR_NOT_FOUND;
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
