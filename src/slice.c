#include "slice.h"
#include <stdlib.h>
#include <string.h>

slice_t *createSlice(size_t element_size, size_t initial_len) {
	slice_t *slice;
	size_t initial_cap;
	void *arr;

	if(initial_len == 0) {
		initial_cap = 1;
	} else {
		initial_cap = initial_len + initial_len / 2;
	}
	arr = calloc(initial_cap, element_size);
	if(arr == NULL) {
		return NULL;
	}

	slice = malloc(sizeof(slice_t));
	if(slice == NULL) {
		return NULL;
	}
	slice->arr = arr;
	slice->element_size = element_size;
	slice->len = initial_len;
	slice->cap = initial_cap;

	return slice;
}

static int growSlice(slice_t *slice) {
	size_t new_cap;
	void *new_arr;

	new_cap = slice->cap + slice->cap / 2;
	if (new_cap == slice->cap) new_cap = slice->cap + 1; 
	new_arr = realloc(slice->arr, new_cap * slice->element_size);
	if(new_arr == NULL) {
		return 0;
	}
	slice->cap = new_cap;
	slice->arr = new_arr;

	return 1;
}

int appendSlice(slice_t *slice, void *data) {
	int err;
	if(slice == NULL) {
		return 0;
	}
	if(data == NULL) {
		return 0;
	}
	if(slice->len >= slice->cap) {
		err = growSlice(slice);
		if(err != 1) {
			return err;
		}
	}
	memcpy((char *)slice->arr + (slice->len * slice->element_size), data,
	       slice->element_size);
	slice->len++;
	return 1;
}

slice_t *subSlice(slice_t *slice, size_t start_idx, size_t end_idx) {
	slice_t *new_slice;
	size_t num_entries;
	void *new_arr;

	if(slice == NULL) {
		return NULL;
	}
	if(start_idx >= end_idx) {
		return NULL;
	}
	if(end_idx > slice->len) {
		return NULL;
	}

	num_entries = end_idx - start_idx;
	new_arr = calloc(num_entries, slice->element_size);
	if(new_arr == NULL) {
		return NULL;
	}
	memcpy(new_arr, (char *)slice->arr + (start_idx * slice->element_size),
	       num_entries * slice->element_size);
	new_slice = malloc(sizeof(slice_t));
	if(new_slice == NULL) {
		free(new_arr);
		return NULL;
	}

	new_slice->element_size = slice->element_size;
	new_slice->arr = new_arr;
	new_slice->len = num_entries;
	new_slice->cap = num_entries + num_entries / 2;

	return new_slice;
}

int freeSlice(slice_t *slice, void (*free_data)(void *)) {
	int i;
	char *arr;
	if (slice == NULL) {
		return 0;
	}
	if (free_data == NULL) {
		free(slice->arr);
		free(slice);
		return 1;
	} 
	
	arr = (char *)slice->arr;
	for (i=0; i<(int)slice->len; i++) {
		free_data(arr + i * slice->element_size);
	}
	free(slice->arr);
	free(slice);
	return 1; 
}
int insertToSlice(slice_t *slice, void *data, size_t idx) {
	char *arr_idx;
	char *shifted_idx;
	if (slice == NULL) {
		return 0;
	}
	if (data == NULL) {
		return 0;
	}
	if (idx > slice->len) {
		return 0;
	}
	if (slice->len >= slice->cap) {
		if (growSlice(slice) != 1) return 0;
	}
	arr_idx = ((char *)slice->arr + idx * slice->element_size);
	shifted_idx = (char *)slice->arr + (idx+1) * slice->element_size;
	memmove(shifted_idx,arr_idx,(slice->len - idx)*slice->element_size);
	memcpy(arr_idx, data, slice->element_size);
	slice->len++;
	return 1;
}
int removeElement(slice_t *slice, size_t idx, void(*free_data)(void *)) { 
	void *element_ptr;
	void *move_ptr;
	if (slice == NULL) {
		return 0;
	}
	if (idx >= slice->len) {
		return 0;
	}
	element_ptr = (char *)slice->arr + idx * slice->element_size;
	move_ptr = (char *)slice->arr + (idx+1)* slice->element_size;
	if (free_data != NULL) {
		free_data(element_ptr);
	} 
	memmove(element_ptr, move_ptr,(slice->len - idx - 1) * slice->element_size);
	slice->len--;

	return 1;
}
void *getFromSlice(slice_t *slice, size_t idx) { 
	if (slice == NULL) return NULL; 

	return ((char *)slice->arr + idx * slice->element_size);
}
