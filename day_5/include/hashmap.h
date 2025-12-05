#ifndef HASHMAP_H
#define HASHMAP_H

// #define BUCKET_SIZE 1 << 10
#include <stdint.h>
#define BUCKET_SIZE (1 << 16)
#define VALUES (1 << 15)

typedef struct hashmap_t {
	int64_t value;
	bool reserved;
} hashmap_t;

static hashmap_t hashmap[BUCKET_SIZE] = {};

static inline void hashmap_init() {
	for (int i = 0; i < BUCKET_SIZE; i++) {
		hashmap[i].value = 0;
		hashmap[i].reserved = false;
	}
}

static inline int hash_function(int64_t value) {
	int key = (int)(value % BUCKET_SIZE);
	return key;
}

static inline void hashmap_insert(const int64_t value) {
	int hash = hash_function(value);
	// while hash is smaller than the bucket size
	while (hash < BUCKET_SIZE) {
		if (!hashmap[hash].reserved) {
			hashmap[hash].value = value;
			hashmap[hash].reserved = true;
			return;
		}
		hash++;
	}
}

static inline int64_t hashmap_count_items() {
	int64_t count = 0;
	for (int i = 0; i < BUCKET_SIZE; i++) {
		if (hashmap[i].reserved) {
			count++;
		}
	}
	return count;
}

static inline int64_t hashmap_get(const int64_t key) {
	int hash = hash_function(key);
	while (hash < BUCKET_SIZE) {
		if (!hashmap[hash].reserved) {
			return -1;
		}
		if (hashmap[hash].value == key) {
			return key;
		}
		hash++;
	}
	return -1;
}

#endif
