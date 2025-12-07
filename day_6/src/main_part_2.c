#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#define FILENAME "day6-example.input"
// #define FILENAME "day6.input"
#define BUF_SIZE 80
#define LINES 2000
#define INITIAL_BUCKET_SIZE 256

char *strip_newline(char *line) {
	if (line[strlen(line) - 1] == '\n') {
		line[strlen(line) - 1] = '\0';
	}
	return line;
}

typedef struct node_t {
	struct node_t *next;
	char value[BUF_SIZE];
} node_t;

typedef struct bucket_t {
	node_t **array; // 2d vector of values
	uint64_t capacity;
	uint64_t size;
} bucket_t;

void bucket_init(bucket_t *bucket) {
	bucket->capacity = INITIAL_BUCKET_SIZE;
	bucket->size = 0;
	bucket->array = (node_t**)malloc(sizeof(node_t*) * bucket->capacity);
	assert(bucket->array != nullptr);
	// initialize safely
	memset((void*)bucket->array, 0, bucket->capacity * sizeof(node_t*));
}

char search_symbol(char value[BUF_SIZE]) {
	if (strstr(value, "+")) {
		return '+';
	} 
	if (strstr(value, "*")) {
		return '*';
	}
	return '\0';
}

char nodes_calculate(node_t *node, int64_t *result) {
	if (node->next == nullptr) {
		char sym = search_symbol(node->value);
		if (sym == '*') {
			*result = 1;
		}
		return sym;
	}
	char symbol = nodes_calculate(node->next, result);

	int64_t val = strtol(node->value, nullptr, 10);

	switch (symbol) {

		case '+': 
			{
			*result += val;
			break;
			}
		case '*':
			{
			*result *= val;
			break;
			}
		default:
	}
	return symbol;
}

// inserts a value in index in bucket if the size of bucket is large enough
// if the size of bucket is smaller add it to the first empty spot
void bucket_insert(bucket_t *bucket, const char value[BUF_SIZE], uint64_t index) {
	node_t *node = (node_t*)malloc(sizeof(node_t));
	strcpy(node->value, value);
	node->next = nullptr;

	// add node to the linked list
	if (index < bucket->size) {
		if (bucket->array[index]->next == nullptr) {
			bucket->array[index]->next = node;
		} else {
			node_t *ptr = bucket->array[index];
			while(ptr->next != nullptr) {
				ptr = ptr->next;
			}
			ptr->next = node;
		}
		return;
	}

	// add node to bucket
	if (*bucket->array == nullptr) {
		*bucket->array = node;
		bucket->size++;
	} else {
		// while the index is larger than i or the current bucket is empty
		uint64_t ind = 0;
		for(;ind < index && bucket->array[ind] != nullptr; ind++) {
		}
		// if index is bigger than capacity make larger array
		if (ind >= bucket->capacity) {
			bucket->array = (node_t**)realloc((void*)
					bucket->array,
					(bucket->capacity * 2) * sizeof(node_t*)); // here we had a horrible bug
																										 // forgot to multiply cap with sizeof
																										 // allocated 8 times less memory
			bucket->capacity *= 2;
		}
		bucket->array[ind] = node;
		bucket->size++;
	}
}

void parse_input(bucket_t *bucket, char *line) {
	uint64_t len = strlen(line);
	char buf[BUF_SIZE] = {0};

	// this expects arbitrary spaces before numbers
	// but only one space after, this is wrong
	uint64_t columns = 0;
	for (uint64_t i = 0; i < len; i++) {
		if (isascii(line[i])) {
			int index = 0;
			while(isspace(line[i])) {
				buf[index++] = line[i++];
			}
			while(isalnum(line[i])) {
				buf[index++] = line[i++];
			}
			while(ispunct(line[i])) {
				buf[index++] = line[i++];
			}
			buf[index] = '\0';
		}

		// printf("inserting\n");
		bucket_insert(bucket, buf, columns++);

		// skips one space
	}
}

int main() {
	FILE *file = nullptr;
	file = fopen(FILENAME, "re");
	if (file == nullptr) {
		return fprintf(stderr, "ERROR: when opening the file %s for reading\n", FILENAME); 
	}

	benchmark_start();

	bucket_t bucket = {};
	bucket_init(&bucket);

	while (!feof(file)) {
		char *buf defer = nullptr;
		size_t line_size = 0;
		if(getline(&buf, &line_size, file) <= 0) {
			break;
		}
		// printf("%s\n", strip_newline(buf));
		parse_input(&bucket, strip_newline(buf));
	}
	
	printf("size of bucket: %ld\n", bucket.size);
	int64_t total = 0;
	for (uint64_t i = 0; i < bucket.size - 1; i++) { // numbers in bucket is one less than size
		int64_t result = 0;

		nodes_calculate(bucket.array[i], &result);
		total += result;
	}

	benchmark_end();

	printf("\ntotal: %ld\n", total);

	if (fclose(file) == EOF) {
		return fprintf(stderr, "ERROR: when closing the file %s\n", FILENAME); 
	}

	return 0;
}
