#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "memory_arena.h"

int fail(const char* msg) {
	return fprintf(stderr, "TEST FAILED: %s\n", msg);
}

#define TEST(X, Y) \
if (!(X)) { \
	return fail(Y);\
}

int main() {
	arena_t arena;

	printf("start tests:\n");
	arena_init(&arena, 1024);

	TEST(arena.size == 0, "initialized arena has size 0");

	TEST(arena.data != nullptr, "empty arena data is NOT a null pointer");

	TEST(arena.capacity == 1024, "empty arena capacity is 1024");

	TEST(arena.size == 0, "empty arena size is 0");

	char *string = arena_alloc(&arena, 20);
	memcpy(string, "null terminated str", 20);

	TEST(arena.size == 20, "size after allocating 20 bytes is 20")

	TEST(strcmp(string, "null terminated str") == 0, "allocated content matches the test string")

	arena_reset(&arena);
	TEST(arena.size == 0, "reseted arena size is 0")

	arena_delete(&arena);
	TEST(arena.size == 0, "deleted arena size is 0")

	TEST(arena.capacity == 0, "deleted arena capacity is 0")

	TEST(arena.data == nullptr, "deleted arena data is nullptr")

	return 0;
}
