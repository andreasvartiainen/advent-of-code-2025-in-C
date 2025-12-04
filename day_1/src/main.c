#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "dial.h"

int main() {
	FILE *file = {};
	file = fopen("puzzle.input", "r");
	if (file == nullptr) {
		int ignore = fprintf(stderr, "ERROR: when opening file\n"); 
		return 1;
	}

	int dialPos = 50;
	printf("initial dial position: %d\n", dialPos);
	int count = 0;

	char line[10];

	printf("running the dial sequence\n");

	while (fgets(line, sizeof(line), file) != nullptr) {
		if (line[ strlen(line) - 1 ] == '\n') {
			line[ strlen(line) - 1 ] = '\0';
		}

		turn_dial(&dialPos, line);
		// get the password from when the dial hits 0
		if (dialPos == 0) {
			count++;
		}
		// printf("with %s Dial is turned to: %d\n", line, dialPos);
	}
	printf("password is: %d\n", count);

	return fclose(file);
}
