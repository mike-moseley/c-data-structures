#ifndef SLICE_H
#define SLICE_H

#include "cds_types.h"

typedef struct Slice {
	void *arr;
	size_t element_size;
	size_t len;
	size_t cap;
} slice_t;

slice_t *createSlice(size_t element_size, size_t initial_len);
int freeSlice(slice_t *slice, void (*free_data)(void *));
int appendSlice(slice_t *slice, void *data);
slice_t *subSlice(slice_t *slice, size_t start_idx, size_t end_idx);
int insertToSlice(slice_t *slice, void *data, size_t idx);
int removeElement(slice_t *slice, size_t idx, void(*free_data)(void *));
void *getFromSlice(slice_t *slice, size_t idx);

#endif
