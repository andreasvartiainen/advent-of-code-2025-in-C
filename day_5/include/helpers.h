#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>

// own defer macro for making defer a bit cleaner
#define defer __attribute__((__cleanup__(cleanup_free)))

static inline void cleanup_free(void *data) {
	free(*(void**) data);
}

#endif
