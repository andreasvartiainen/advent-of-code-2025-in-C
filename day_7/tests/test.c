// this is a file for writing tests in
// this is added in the cmake file as target
// and as a test
#include <assert.h>
#include <stdio.h>

int fail(const char* msg) {
	return fprintf(stderr, "TEST FAILED: %s\n", msg);
}

// test macro that returns != 0 if the (CASE) is not true
// so ( true = false ) = 0 => !(CASE) == 1 and the fail triggers
// MSG should be in format "when variable is 1 the output is 1"
#define TEST(CASE, MSG) \
if (!(CASE)) { \
	return fail(MSG);\
}

int main() {
	return 0;
}
