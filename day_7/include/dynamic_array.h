#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// :TODO:
// swap
// reserve
// resize
// erase

// nice to have:::
// insert_range
// push_range

// must have::::::
// clear				OK
// insert   		OK
// push_back		OK
// pop_back 		OK

static const size_t da_initial_size = 256;

typedef struct {
  int *items;
  size_t count;
  size_t capacity;
} Integers;

typedef struct {
  double *items;
  size_t count;
  size_t capacity;
} Doubles;

typedef struct line_t {
  char *line;
  size_t size;
} line_t;

typedef struct {
  line_t *items;
  size_t count;
  size_t capacity;
} Lines;

// push item to array
#define da_push(array, item)                                                   \
  do {                                                                         \
    if ((array).count >= (array).capacity) {                                   \
      if ((array).capacity == 0) {                                             \
        (array).capacity = da_initial_size;                                    \
      } else {                                                                 \
        (array).capacity *= 2;                                                 \
      }                                                                        \
      void *ptr =                                                              \
          realloc((array).items, (array).capacity * sizeof(*(array).items));   \
      assert(ptr);                                                             \
      (array).items = ptr;                                                     \
    }                                                                          \
    (array).items[(array).count++] = item;                                     \
  } while (0)

// insert item to index
#define da_insert(array, item, index)                                          \
  do {                                                                         \
    if ((index) >= (array).count) {                                            \
      da_push(array, (item));                                                  \
    } else {                                                                   \
      if ((array).count + 1 >= (array).capacity) {                             \
        void *ptr = realloc((array).items,                                     \
                            (array).capacity * 2 * sizeof(*(array).items));    \
        assert(ptr);                                                           \
        (array).items = ptr;                                                   \
        (array).capacity *= 2;                                                 \
      }                                                                        \
      memmove(((array).items + (index) + 1), ((array).items + (index)),        \
              (array).count - (index));                                        \
      (array).items[index] = item;                                             \
      (array).count++;                                                         \
    }                                                                          \
  } while (0)

// remove item from index
#define da_remove(array, item, index)                                          \
  do {                                                                         \
    if ((array).count > 0) {                                                   \
      if ((index) < (array).count) {                                           \
        (item) = (array).items[index];                                         \
        memmove(((array).items + (index)), ((array).items + (index) + 1),      \
                ((array).count - (index)) * sizeof(*(array).items));           \
        (array).count--;                                                       \
      } else if ((index) >= (array).count) {                                   \
        da_pop(array, item);                                                   \
      }                                                                        \
    } else {                                                                   \
      (item) = 0;                                                              \
    }                                                                          \
  } while (0)

// pop item from array
#define da_pop(array, item)                                                    \
  do {                                                                         \
    if ((array).count > 0) {                                                   \
      (item) = (array).items[--(array).count];                                 \
      (array).items[(array).count] = (item);                                   \
    }                                                                          \
  } while (0)

// get item at index
#define da_get(array, item, index)                                             \
  do {                                                                         \
    if ((index) < (array).count) {                                             \
      (item) = (array).items[index];                                           \
    } else {                                                                   \
      (item) = (item);                                                         \
    }                                                                          \
  } while (0)

// set index to a value
#define da_set(array,index,item)                                             \
  do {                                                                         \
		assert((index) < (array).count);\
    if ((index) < (array).count) {                                             \
      (array).items[index] = item;                                             \
    }                                                                          \
  } while (0)

// sets the count to 0 and memsets the used memory to 0
#define da_clear(array)                                                        \
  do {                                                                         \
    memset((array).items, 0, (array).count * sizeof(*(array).items));          \
    (array).count = 0;                                                         \
  } while (0);

// free the dynamic array
#define da_free(array)                                                         \
  do {                                                                         \
    free((array).items);                                                       \
    (array).items = nullptr;                                                   \
  } while (0)

#endif
