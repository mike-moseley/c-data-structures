#include "linked_list.h"
#include "cds_types.h"
#include <stdlib.h>

linked_list_t *createLinkedList(void) {
	linked_list_t *list = malloc(sizeof(linked_list_t));
	if(list == NULL) return NULL;
	list->head = NULL;
	list->size = 0;
	return list;
}

int pushNode(linked_list_t *list, void *data) {
	node_t *new_node;
	if(list == NULL) {
		return CDS_ERR_NULL;
	}
	new_node = malloc(sizeof(node_t));
	if(new_node == NULL) {
		return CDS_ERR_OOM;
	}
	new_node->data = data;
	new_node->next = list->head;
	list->head = new_node;
	list->size++;
	return CDS_OK;
}

int appendNode(linked_list_t *list, void *data) {
	node_t *new_node;
	node_t *tracking_node;
	if(list == NULL) {
		return CDS_ERR_NULL;
	}
	new_node = malloc(sizeof(node_t));
	if(new_node == NULL) {
		return CDS_ERR_OOM;
	}
	new_node->data = data;
	new_node->next = NULL;

	if(list->head == NULL) {
		list->head = new_node;
		list->size++;
		return CDS_OK;
	}

	tracking_node = list->head;
	while(tracking_node->next != NULL) {
		tracking_node = tracking_node->next;
	}
	tracking_node->next = new_node;
	list->size++;
	return CDS_OK;
}

int removeNode(linked_list_t *list, void *target, int (*cmp)(void *, void *)) {
	node_t *tracking_node;
	node_t *previous_node;

	if(list == NULL) {
		return CDS_ERR_NULL;
	}
	if(target == NULL) {
		return CDS_ERR_NULL;
	}

	/* cmp function should handle NULL case! */
	if(list->head == NULL) {
		return CDS_ERR_NULL;
	}
	if(cmp(list->head->data, target) == 0) {
		previous_node = list->head;
		list->head = list->head->next;
		free(previous_node);
		list->size--;
		return CDS_OK;
	}
	tracking_node = list->head->next;
	previous_node = list->head;
	while(tracking_node != NULL) {
		if(cmp(tracking_node->data, target) == 0) {
			previous_node->next = tracking_node->next;
			free(tracking_node);
			list->size--;
			return CDS_OK;
		} else {
			previous_node = tracking_node;
			tracking_node = tracking_node->next;
		}
	}

	return CDS_ERR_INVALID;
}

/* cmp function should handle NULL case! */
node_t *findNode(linked_list_t *list, void *target,
                 int (*cmp)(void *, void *)) {
	node_t *tracking_node;
	if(list == NULL) {
		return NULL;
	}
	if(list->head == NULL) {
		return NULL;
	}
	if(target == NULL) {
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
int freeLinkedList(linked_list_t *list, void (*free_data)(void *)) {
	node_t *tracking_node;
	node_t *delete_node;

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
