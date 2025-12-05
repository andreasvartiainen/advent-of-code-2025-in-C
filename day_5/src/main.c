#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// #define FILENAME "cafeteria-example.input"
#define FILENAME "cafeteria.input"
#define BUF_SIZE 256
#define LINES 2000

char *strip_newline(char *line) {
	if (line[strlen(line) - 1] == '\n') {
		line[strlen(line) - 1] = '\0';
	}
	return line;
}

typedef struct range_t {
	int64_t start;
	int64_t end;
} range_t;

range_t create_ranges(char *line) {
	int len = (int)strlen(line);
	range_t range = {.start = -1, .end = -1 };
	// if the length is less than 3 so x-x doesn't fit return
	if (len < 3) {
		return range;
	}

	sscanf(line, "%ld-%ld", &range.start, &range.end);

	return range;
}

bool check_ranges(const range_t *ranges, const int64_t value) {
	int index = 0;
	while (ranges[index].start != -1) {
		if (ranges[index].start <= value && ranges[index].end >= value) {
			// printf("FRESH: %d\n", value);
			return true;
		}
		index++;
	}
	// printf("SPOILED: %d\n", value);
	return false;
}

int main() {
	FILE *file = fopen(FILENAME, "re");
	if (file == nullptr) {
		return fprintf(stderr, "ERROR: when opening the file %s for reading\n", FILENAME); 
	}

	range_t ranges[LINES] = {{.start = -1, .end = -1}};
	for (int i = 0; i < LINES; i++) {
		ranges[i].start = -1;
		ranges[i].end = -1;
	}

	int line_count = 0;
	while (!feof(file)) {
		char buf[BUF_SIZE] = {'\0'};
		if (!fgets(buf, BUF_SIZE, file) || buf[0] == '\n' || line_count >= LINES) {
			break;
		}
		ranges[line_count++] = create_ranges(buf);
	}

	line_count = 0;
	int fresh = 0;
	while (!feof(file)) {
		char buf[BUF_SIZE] = {'\0'};
		if (!fgets(buf, BUF_SIZE, file) || line_count >= LINES) {
			break;
		}
		if (buf[0] == '\n') {
			continue;
		}
		int64_t value = 0;
		sscanf(buf, "%ld", &value);
		fresh += (int)(check_ranges(ranges, value)) ? 1 : 0;
		line_count++;
	}

	printf("total fresh: %d\n", fresh);

	int index = 0;
	while (ranges[index].end != -1) {
		// printf("start: %d end: %d\n", ranges[index].start, ranges[index].end);
		index++;
	}

	if (fclose(file) == EOF) {
		return fprintf(stderr, "ERROR: when closing the file %s\n", FILENAME); 
	}

	return 0;
}
