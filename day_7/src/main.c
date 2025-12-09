#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"
#include "helpers.h"

// #define FILENAME "day7-example.input"
#define FILENAME "day7.input"
//
#define LAZER  	'|'
#define BG     	'.'
#define SOURCE 	'S'
#define DIV			'^'

int64_t parse_input(Lines *array) {
	int64_t divided = 0;
	for (size_t row = 1; row < array->count; row++) {
		for (size_t col = 0; col < array->items[row].size; col++) {
			char *upper = array->items[row - 1].line;
			char *current = array->items[row].line;
			char *lower = (row == array->count - 1) ? nullptr : array->items[row + 1].line;

			if ((upper[col] == SOURCE || upper[col] == LAZER)
					&& current[col] == BG
				) {
				current[col] = LAZER;
			}

			if (lower) {
				if (lower[col] == DIV
						&& current[col] == LAZER) {
					lower[col - 1] = LAZER;
					lower[col + 1] = LAZER;
					divided++;
				}
			}
		}
	}
	return divided;
}

void print_array(Lines *array) {
	for (size_t i = 0; i < array->count; i++) {
		line_t line = {0};
		da_get(*array, line, i);
		printf("%s\n", line.line);
	}
}

int main() { //NOLINT
	FILE *file = nullptr;
	file = fopen(FILENAME, "re");
	if (file == nullptr) {
		return fprintf(stderr, "ERROR: when opening the file %s for reading\n", FILENAME); 
	}

	Lines line_array defer = {0};

	benchmark_start();

	while (!feof(file)) {
		// char *buf defer = nullptr;
		line_t line = {0};
		if(getline(&line.line, &line.size, file) <= 0) {
			free(line.line);
			break;
		}

		// maybe there could be some more generic way to do this
		// but I want to keep the helpers.h as simple as possible
		line.line = strip_newline(line.line);
		line.size /= sizeof(*line.line); // because line size is in bits

		da_push(line_array, line);
	}

	printf("%ld\n", parse_input(&line_array));
	print_array(&line_array);
	
	benchmark_end();

	if (fclose(file) == EOF) {
		return fprintf(stderr, "ERROR: when closing the file %s\n", FILENAME); 
	}

	for (size_t i = 0; i < line_array.count; i++) {
		free(line_array.items[i].line);
	}

	return 0;
}
