#include "ring_buffer.h"
#include "cds_types.h"
#include <stdlib.h>
#include <string.h>

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

cds_err_t pushRingBuffer(ringbuffer_t *ringbuffer, void *data) {
	if(ringbuffer == NULL) return CDS_ERR_NULL;
	if(ringbuffer->len == ringbuffer->cap) {
		ringbuffer->head = (ringbuffer->head + 1) % ringbuffer->cap;
	};
	memcpy((char *)ringbuffer->buf + ringbuffer->tail * ringbuffer->element_size, data, ringbuffer->element_size);
	ringbuffer->tail = (ringbuffer->tail + 1) % ringbuffer->cap;
	if(ringbuffer->len < ringbuffer->cap) ringbuffer->len++;
	return CDS_OK;
}
