#ifndef MEMORY_ARENA_H
#define MEMORY_ARENA_H

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum type_t {
	INT,
	DOUBLE,
	CHAR,
} type_t;

typedef struct data_t {
	type_t type;
	union {
		int i_number;
		char letter;
		double f_number;
	};
} data_t;

typedef struct arena_t {
	size_t capacity;
	size_t size;
	uint8_t *data;
} arena_t;

void arena_init(arena_t *arena, size_t capacity) {
	arena->data = malloc(1 * capacity);
	arena->capacity = capacity;
	arena->size = 0;
}

void *arena_alloc(arena_t *arena, size_t size) {
	assert(arena->size + size < arena->capacity);
	uint8_t *data = &arena->data[arena->size];
	arena->size += size;
	return data;
}

void arena_reset(arena_t *arena) {
	arena->size = 0;
}

void arena_delete(arena_t *arena) {
	arena->capacity = 0;
	arena->size = 0;
	free(arena->data);
	arena->data = nullptr;
}

void print_arena(arena_t *arena) {
	printf("size: %zu\n", arena->size);
	printf("capacity: %zu\n", arena->capacity);
}

#endif
