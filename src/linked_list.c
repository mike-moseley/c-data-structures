#include "linked_list.h"
#include <stdlib.h>

linked_list_t *createLinkedList(void) {
	linked_list_t *list = malloc(sizeof(linked_list_t));
	if (list == NULL) return NULL;
	list->head = NULL;
	list->size = 0;
	return list;
}

int pushNode(linked_list_t *list, void *data) {
	node_t *new_node;
	if (list == NULL) {
		return 0;
	}
	new_node = malloc(sizeof(node_t));
	if (new_node == NULL) {
		return 0;
	}
	new_node->data = data;
	new_node->next = list->head;
	list->head = new_node;
	list->size++;
	return 1;
}

int appendNode(linked_list_t *list, void *data) {
	node_t *new_node;
	node_t *tracking_node;
	if (list == NULL) {
		return 0;
	}
	new_node = malloc(sizeof(node_t));
	if (new_node == NULL) {
		return 0;
	}
	new_node->data = data;
	new_node->next = NULL;

	if (list->head == NULL) {
		list->head = new_node;
		list->size++;
		return 1;
	}

	tracking_node = list->head;
	while( tracking_node->next != NULL) {
		tracking_node = tracking_node->next;
	}
	tracking_node->next = new_node;
	list->size++;
	return 1;
}

int removeNode(linked_list_t *list, void *target, int (*cmp)(void *, void*)) {
	node_t *tracking_node;
	node_t *previous_node;
	int found;

	if (list == NULL) {
		return 0;
	}

	found = 0;
	if (list->head == NULL) {
		return found;
	}
	if (cmp(list->head->data, target)){
		found = 1;
		previous_node = list->head;
		list->head = list->head->next;
		free(previous_node);
		list->size--;
		return found;
	}
	tracking_node = list->head->next;
	previous_node = list->head;
	while (tracking_node != NULL) {
		if (cmp(tracking_node->data, target)) {
			found = 1;
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

node_t *findNode(linked_list_t *list, void *target, int(*cmp)(void *, void *)){
	node_t *tracking_node;
	if (list == NULL) {
		return NULL;
	}
	if (list->head == NULL){
		return NULL;
	}
	tracking_node = list->head;
	while (tracking_node != NULL) {
		if (cmp(tracking_node->data, target)){
			return tracking_node;
		}
		tracking_node = tracking_node->next;
	}

	return NULL;
}

int freeLinkedList(linked_list_t *list, void (*free_data)(void *)) {
	node_t *tracking_node;
	node_t *delete_node;

	if (list == NULL) {
		return 0;
	}
	if (free_data == NULL) {
		return 0;
	}
	if (list->head == NULL) {
		free(list);
		return 1;
	}

	tracking_node = list->head;
	while(tracking_node != NULL) {
		delete_node = tracking_node;
		tracking_node = tracking_node->next;
		free_data(delete_node->data);
		free(delete_node);
	}
	free(list);
	return 1;
}
