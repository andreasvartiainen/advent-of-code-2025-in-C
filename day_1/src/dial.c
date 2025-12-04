#include "dial.h"
#include <ctype.h>
#include <stdio.h>

void turn_dial(int *position, const char *command) {
	char direction = (char)toupper(command[0]); // L or R
	if (direction != 'R' && direction != 'L') {
		int ignore = fprintf(stderr, "ERROR: Valid directions are R and L\n"); 
		return;
	}

	// nudge the array pointer one step forward
	// to jump over the letter
	command++;

	// parse the distance value
	int distance = {0};
	if(sscanf(command, "%d", &distance) <= 0) {
		int ignore = fprintf(stderr, "No distance specified\n"); 
		return;
	}

	if (direction == 'R') {
		*position = (*position + distance) % 100;
	} else {
		int newPosition = (*position - distance);
		// if the position is positive return it, if it is negative add it to 100 and take mod
		*position = newPosition > 0 ? newPosition : (100 + (newPosition % 100)) % 100;
	}
}
