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
	return 0;
}
