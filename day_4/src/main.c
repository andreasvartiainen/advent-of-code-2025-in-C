#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define FILENAME "rolls-example.input"
#define FILENAME "rolls.input"
#define BUF_SIZE 256
#define LINES 1000
#define ROLLSYM '@'
#define DELETESYM 'X'

void strip_newline(char *line) {
	if (line[strlen(line) - 1] == '\n') {
		line[strlen(line) - 1] = '\0';
	}
}

// count rolls that are adjacent to the item in rolls[row][col]
// x x x
// x o x
// x x x
int count_adjacent(
		char rolls[LINES][BUF_SIZE], 
		const int lines, 
		const int len,
		const int row, 
		const int col
		) {
	int adj_count = 0;
	for (int k = -1; k <= 1; k++) {
		if (row + k >= lines || row + k < 0) {
			// printf("-");
			continue;
		}
		for (int kk = -1; kk <= 1; kk++) {
			// if we are at the center (same index as the source, skip
			if (k == 0 && kk == 0) {
				// printf("x");
				continue;
			}
			// if row + k is more than lines
			// or
			// if row + k is less than 0 
			// means that both ends of list is checked and if one
			// of them fail we skip this iteration
			if (col + kk >= len || col + kk < 0) {
				// printf("u");
				continue;
			}
			// if the location is roll symbol add one, if not add 0
			// printf("%c", rolls[row + k][col + kk]);
		  if (rolls[row + k][col + kk] == ROLLSYM
					|| rolls[row + k][col + kk] == DELETESYM
					) {
				adj_count++;
			}
		}
		// printf("\n");
	}
	// printf("adjacent: %d\n", adj_count);
	return adj_count;
}

// return the count of all the valid rolls
int handle_rolls(char rolls[LINES][BUF_SIZE], int lines) {
	int len = (int)strlen(rolls[0]);

	int valid_roll_count = 0; // rolls that can be accessed by the forklift (adj < 4)
	for (int row = 0; row < lines; row++) {
		for (int col = 0; col < len; col++) {
			// if we are at an item that is not a roll, skippp
			if (rolls[row][col] == ROLLSYM) {
				if (count_adjacent(rolls, lines, len, row, col) < 4) {
					rolls[row][col] = DELETESYM;
					valid_roll_count++;
				}
			}
		}
	}
	return valid_roll_count;
}

// return the count of all the valid rolls
void print_rolls(char rolls[LINES][BUF_SIZE], int lines) {
	int len = (int)strlen(rolls[0]);

	for (int row = 0; row < lines; row++) {
		for (int col = 0; col < len; col++) {
			printf("%c", rolls[row][col]);
		}
		printf("\n");
	}
}

void update_rolls(char rolls[LINES][BUF_SIZE], int lines) {
	int len = (int)strlen(rolls[0]);

	for (int row = 0; row < lines; row++) {
		for (int col = 0; col < len; col++) {
			if (rolls[row][col] == DELETESYM) {
				rolls[row][col] = '.';
			}
		}
	}
}

int main() {
	FILE *file = fopen(FILENAME, "re");
	if (file == nullptr) {
		return fprintf(stderr, "ERROR: when opening the file %s for reading\n", FILENAME); 
	}

	char lines[LINES][BUF_SIZE] = {{'\0'}};

	int line_count = 0;
	while (!feof(file)) {
		char buf[BUF_SIZE] = {};
		if(!fgets(buf, BUF_SIZE, file)) {
			break;
		}
		strip_newline(buf);
		strcpy(lines[line_count], buf);
		line_count++;
	}

	// print_rolls(lines, line_count);
	int removed = 0;
	int to_be_removed = INT32_MAX;
	while (to_be_removed > 0) {
		to_be_removed = handle_rolls(lines, line_count);
    removed += to_be_removed;
		update_rolls(lines, line_count);
		// print_rolls(lines, line_count);
	}

	printf("removed: %d\n", removed);

	if (fclose(file) == EOF) {
		return fprintf(stderr, "ERROR: when closing the file %s\n", FILENAME); 
	}

	return 0;
}
