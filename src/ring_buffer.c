#include "ring_buffer.h"
#include <stdlib.h>

ringbuffer_t *createRingBuffer(size_t initial_cap, size_t element_size) {
	ringbuffer_t *ringbuffer;
	void *buf;

	if(initial_cap < 1) initial_cap = 1;
	if(element_size == 0) return NULL;

	ringbuffer = malloc(sizeof(ringbuffer_t));
	if(ringbuffer == NULL) return NULL;

	buf = calloc(initial_cap, element_size);
	if(buf == NULL) {
		free(ringbuffer);
		return NULL;
	};
	ringbuffer->buf = buf;
	ringbuffer->len = 0;
	ringbuffer->cap = initial_cap;
	ringbuffer->head = 0;
	ringbuffer->tail = 0;
	ringbuffer->element_size = element_size;

	return ringbuffer;
}
