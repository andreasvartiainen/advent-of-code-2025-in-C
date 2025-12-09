#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// #define FILENAME "day7-example.input"
#define FILENAME "day7.input"
#define BUF_SIZE 256
#define LINES 2000
#define INITIAL_BUCKET_SIZE 256

char *strip_newline(char *line) {
	if (line[strlen(line) - 1] == '\n') {
		line[strlen(line) - 1] = '\0';
	}
	return line;
}

void parse_input() {
}

int main() {
	FILE *file = nullptr;
	file = fopen(FILENAME, "re");
	if (file == nullptr) {
		return fprintf(stderr, "ERROR: when opening the file %s for reading\n", FILENAME); 
	}

	benchmark_start();

	while (!feof(file)) {
		char *buf defer = nullptr;
		size_t line_size = 0;
		if(getline(&buf, &line_size, file) <= 0) {
			break;
		}
		printf("%s\n", strip_newline(buf));
		// parse_input();
	}
	
	benchmark_end();

	if (fclose(file) == EOF) {
		return fprintf(stderr, "ERROR: when closing the file %s\n", FILENAME); 
	}

	return 0;
}
