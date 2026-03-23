#include "hash_map.h"
#include "cds_types.h"
#include <bits/stdint-intn.h>
#include <stdlib.h>
#include <string.h>

static int keycmp(hashmap_t *hashmap, void *bucket_key, void *key) {
	int matched;
	if(hashmap->key_size == 0) {
		matched = strcmp(key, bucket_key) == 0;
	} else {
		matched = memcmp(key, bucket_key, hashmap->key_size) == 0;
	}
	return matched;
}

/* FNV-1a hash */
static size_t hash_function(void *key, size_t key_size) {
	size_t hash;
	unsigned char *bytes;
	/* key is not a string */
	if(key_size > 0) {
		size_t i;
		hash = 2166136261u;
		bytes = (unsigned char *)key;
		for(i = 0; i < key_size; i++) {
			hash ^= *(bytes + i);
			hash *= 16777619u;
		}
	} else {
		bytes = (unsigned char *)key;
		hash = 2166136261u;
		while(*(bytes) != '\0') {
			hash ^= *(bytes);
			hash *= 16777619u;
			bytes++;
		}
	}
	return hash;
}

hashmap_t *createHashMap(size_t key_size, size_t value_size,
                         size_t initial_cap) {
	hashmap_t *hashmap;
	hnode_t **buckets;

	if(initial_cap == 0) {
		return NULL;
	}
	hashmap = malloc(sizeof(hashmap_t));
	if(hashmap == NULL) {
		return NULL;
	}
	buckets = calloc(initial_cap, sizeof(hnode_t *));
	if(buckets == NULL) {
		free(hashmap);
		return NULL;
	}
	hashmap->buckets = buckets;
	hashmap->len = 0;
	hashmap->cap = initial_cap;
	hashmap->key_size = key_size;
	hashmap->value_size = value_size;

	return hashmap;
}

/* void freeHashMap(hashmap_t *hashmap, void(*free_data)(void *)); */
cds_err_t insertToHashMap(hashmap_t *hashmap, void *key, void *value) {
	size_t hash;
	int found;
	hnode_t *hash_node;
	hnode_t *current_bucket;
	void *node_key;
	void *node_value;

	if(hashmap == NULL) {
		return CDS_ERR_NULL;
	}
	if(key == NULL) {
		return CDS_ERR_NULL;
	}
	if(value == NULL) {
		return CDS_ERR_NULL;
	}

	found = 0;
	hash = hash_function(key, hashmap->key_size) % hashmap->cap;
	hash_node = malloc(sizeof(hnode_t));
	if(hash_node == NULL) {
		return CDS_ERR_OOM;
	}
	node_key = malloc(hashmap->key_size);
	if(node_key == NULL) {
		free(hash_node);
		return CDS_ERR_OOM;
	}
	node_value = malloc(hashmap->value_size);
	if(node_value == NULL) {
		free(node_key);
		free(hash_node);
		return CDS_ERR_OOM;
	}
	memcpy(node_key, key, hashmap->key_size);
	memcpy(node_value, value, hashmap->value_size);
	hash_node->key = node_key;
	hash_node->value = node_value;
	hash_node->next = NULL;
	if(hashmap->buckets[hash] == NULL) {
		hashmap->buckets[hash] = hash_node;
		hashmap->len++;
	} else {
		current_bucket = hashmap->buckets[hash];
		while(current_bucket->next != NULL) {
			if(keycmp(hashmap, current_bucket->key, key)) {
				memcpy(current_bucket->value, value, hashmap->value_size);
				free(hash_node);
				free(node_key);
				free(node_value);
				found = 1;
				break;
			} else {
				current_bucket = current_bucket->next;
			}
		}
		if(!found) {
			if(keycmp(hashmap, current_bucket->key, key)) {
				memcpy(current_bucket->value, value, hashmap->value_size);
				found = 1;
				free(hash_node);
				free(node_key);
				free(node_value);
			} else {
				current_bucket->next = hash_node;
				hashmap->len++;
			}
		}
	}
		return CDS_OK;
}
/* void *getFromHashMap(hashmap_t *hashmap, void *key); */
/* cds_err_t removeFromHashMap(hashmap_t *hashmap, void *key); */
