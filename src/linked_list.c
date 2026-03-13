#include "linked_list.h"
#include <stdlib.h>

linked_list_t *createLinkedList(void) {
	linked_list_t *list = malloc(sizeof(linked_list_t));
	list->head = NULL;
	list->size = 0;
	return list;
}

void pushNode(linked_list_t *list, void *data) {
	node_t *new_node = malloc(sizeof(node_t));
	new_node->data = data;
	new_node->next = list->head;
	list->head = new_node;
	list->size++;
}

void appendNode(linked_list_t *list, void *data) {
	node_t *new_node = malloc(sizeof(node_t));
	node_t *tracking_node;

	new_node->data = data;
	new_node->next = NULL;

	if (list->head == NULL) {
		list->head = new_node;
		list->size++;
		return;
	}

	tracking_node = list->head;
	while( tracking_node->next != NULL) {
		tracking_node = tracking_node->next;
	}
	tracking_node->next = new_node;
	list->size++;
}
