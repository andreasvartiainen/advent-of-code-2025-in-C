#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

#define FILENAME "cafeteria-example.input"
// #define FILENAME "cafeteria.input"
#define BUF_SIZE 256
#define LINES 1000

char *strip_newline(char *line) {
	if (line[strlen(line) - 1] == '\n') {
		line[strlen(line) - 1] = '\0';
	}
	return line;
}

int main() {
	FILE *file = fopen(FILENAME, "re");
	if (file == nullptr) {
		return fprintf(stderr, "ERROR: when opening the file %s for reading\n", FILENAME); 
	}

	while (!feof(file)) {
		char buf[BUF_SIZE] = {'\0'};
		if (!fgets(buf, BUF_SIZE, file)) {
			break;
		}
		printf("%s\n", strip_newline(buf));
	}

	if (fclose(file) == EOF) {
		return fprintf(stderr, "ERROR: when closing the file %s\n", FILENAME); 
	}

	return 0;
}
