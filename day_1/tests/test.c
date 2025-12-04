#include "dial.h"
#include <assert.h>
#include <stdio.h>

int fail(const char* msg) {
	return fprintf(stderr, "TEST FAILED: %s\n", msg);
}

#define TEST(X, Y) \
if (!(X)) { \
	return fail(Y);\
}

int main() {
	int position = 50;

	turn_dial(&position, "R50");
	TEST(position == 0, "position is 0 after move to right 50 from 50");
	turn_dial(&position, "R50");
	TEST(position == 50, "position is 50 after move to right 50 from 0");
	turn_dial(&position, "L50");
	TEST(position == 0, "position is 0 after move to left 50 from 50");
	turn_dial(&position, "L50");
	TEST(position == 50, "position is 50 after move to left 50 from 0");

	// reset the position
	position = 50;
	turn_dial(&position, "L300");
	TEST(position == 50, "position is 50 after move to left 300 from 50");
	turn_dial(&position, "R300");
	TEST(position == 50, "position is 50 after move to right 300 from 50");

	position = 0;
	turn_dial(&position, "L1");
	TEST(position == 99, "position is 99 after move to left 1 from 0");
	turn_dial(&position, "R2");
	TEST(position == 1, "position is 1 after move to right 2 from 99");
}
