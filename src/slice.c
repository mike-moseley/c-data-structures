#include "slice.h"
#include <stdlib.h>
#include <string.h>

slice_t *createSlice(size_t element_size, size_t initial_len) {
	slice_t *slice;
	size_t initial_cap;
	void *arr;

	initial_cap = initial_len + initial_len/2;
	arr = calloc(initial_cap, element_size);
	if(arr == NULL) {return NULL;}

	slice = malloc(sizeof(slice_t));
	if(slice == NULL) {return NULL;}
	slice->arr = arr;
	slice->element_size = element_size;
	slice->len = initial_len;
	slice->cap = initial_cap;

	return slice;
}

static int growSlice(slice_t *slice) {
	size_t new_cap;
	void *new_arr;

	new_cap = slice->cap + slice->cap/2;
	new_arr = realloc(slice->arr, new_cap * slice->element_size);
	if(new_arr == NULL) {return 0;}
	slice->cap = new_cap;
	slice->arr = new_arr;
	
	return 1;
}

int appendSlice(slice_t *slice, void *data){
	int err;
	if (slice == NULL) {
		return 0;
	}
	if (data == NULL) {
		return 0;
	}
	if (slice->len >= slice->cap) {
		err = growSlice(slice);
		if (err != 1) {return err;}
	}
	memcpy((char *)slice->arr + (slice->len * slice->element_size), data, slice->element_size);
	slice->len++;
	return 1;
}

slice_t *sliceOf(slice_t *slice, size_t start_idx, size_t end_idx) {

	return NULL;
}

int freeSlice(slice_t *slice, void (*free_data)(void *)) {

	return 1;
}
int insert(slice_t *slice, void *data, size_t idx) {

	return 1;
}
int removeElement(slice_t *slice, size_t idx) {

	return 1;
}
void *get(slice_t *slice, size_t idx){
	
	return NULL;
}
