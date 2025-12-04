#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define FILENAME "joltake-example.input"
#define FILENAME "joltake.input"

int i_from_c(const char num) {
	return num - '0';
}

int value_from_string(const char *str) {
	int value = {};
	value = (int)strtol(str, nullptr, 10);
	return value;
}

int calculate_joltage(const char *line) {
	int len = (int)strlen(line);
	// printf("LINE LENGTH: %d\n", len);
	
	int max_index = 0;
	for (int i = 0; i < len - 1; i++) {
		if (i_from_c(line[i]) > i_from_c(line[max_index])) {
			max_index = i;
		}
	}

	// we start this search from where last stopped
	int max_index2 = max_index + 1;
	for (int i = max_index2; i < len; i++) {
		if (i_from_c(line[i]) > i_from_c(line[max_index2])) {
			max_index2 = i;
		}
	}

	// printf("%s\n", line);
	// printf("max 1: %d max 2: %d\n", i_from_c(line[max_index]), i_from_c(line[max_index2]));

	int return_val = 0;
	return_val = i_from_c(line[max_index]);
	return_val *= 10;
	return_val += i_from_c(line[max_index2]);

	return return_val;
}

void strip_newline(char *line) {
	if (line[strlen(line) - 1] == '\n') {
		line[strlen(line) - 1] = '\0';
	}
}

int main() {
	FILE *file = fopen(FILENAME, "r");
	if (file == nullptr) {
		return fprintf(stderr, "ERROR: when opening the file %s for reading\n", FILENAME); 
	}

	int sum = 0;
	const int buf_size = 256;
	while (!feof(file)) {
		char buf[buf_size] = {};
		if(!fgets(buf, buf_size, file)) {
			break;
		}
		strip_newline(buf);
		sum += calculate_joltage(buf);
	}

	printf("joltake rating: %d", sum);

	if (fclose(file) == EOF) {
		return fprintf(stderr, "ERROR: when closing the file %s\n", FILENAME); 
	}

	return 0;
}
