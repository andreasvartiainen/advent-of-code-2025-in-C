#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define FILENAME "joltake-example.input"
// #define FILENAME "joltake.input"

int calculate_joltage(const char *line) {
	return 0;
}

int main() {
	FILE *file = fopen(FILENAME, "r");
	if (file == nullptr) {
		return fprintf(stderr, "ERROR: when opening the file %s for reading\n", FILENAME); 
	}

	int sum = 0;
	while (!feof(file)) {
		char buf[80] = {};
		if(!fgets(buf, 80, file)) {
			break;
		}
		sum += calculate_joltage(buf);
	}

	if (fclose(file) == EOF) {
		return fprintf(stderr, "ERROR: when closing the file %s\n", FILENAME); 
	}

	return 0;
}
