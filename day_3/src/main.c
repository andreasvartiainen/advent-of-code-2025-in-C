#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define FILENAME "joltake-example.input"
#define FILENAME "joltake.input"
#define BUF_SIZE 256
#define BASE 10

int i_from_c(const char num) { return num - '0'; }

int value_from_string(const char *str) {
  int value = {};
  value = (int)strtol(str, nullptr, BASE);
  return value;
}

void free_bbuf(int **bbuf) { free(*bbuf); }

int64_t calculate_joltage(const char *line, int battery_count) {
  int len = (int)strlen(line);
  // { 3 (>3) (>4) (>5) ... (>n) }
  // battery_index saves the indexes of the batteries
  int *battery_index __attribute__((__cleanup__(free_bbuf))) =
      (int *)malloc(sizeof(int) * battery_count);
  for (int i = 0; i < battery_count; i++) {
    battery_index[i] = 0;
  }

  // this goes through all the batteries in order
  for (int bat = 0; bat < battery_count; bat++) {
    // set the current battery index to be one more than the last one
    // to ignore the previous index
    if (bat != 0) {
      battery_index[bat] = battery_index[bat - 1] + 1;
    }
    // this i starts looking at the line[i] from the index in current
    // battery index (bat)
    // when looking at the first battery we have to return the first index
    for (int i = (bat == 0) ? battery_index[bat]
                            : battery_index[bat - 1] +
                                  1;        // this should look behind one and
                                            // add one to the index
         i < len - battery_count + bat + 1; // len - battery_count
         i++) {
      // if the current item line[i] is bigger than line[battery_index[bat]
      // save the index to the battery_index[bat]
      // here the second round starts from 0 index again
      // because battery_index[bat] = 0 so we compare the first item again
      if (line[i] > line[battery_index[bat]]) {
        battery_index[bat] = i;
      }
    }
  }

  int64_t return_val = 0;
  const int ten_mul = 10;
  for (int i = 0; i < battery_count; i++) {
    // 0 + 9 = 9
    // 9 * 10 = 90
    // 90 + 5 = 95
    // ...
    return_val += i_from_c(line[battery_index[i]]);
    return_val *= ten_mul;
  }
  return_val /= ten_mul;

  // free(battery_index);
  return return_val;
}

void strip_newline(char *line) {
  if (line[strlen(line) - 1] == '\n') {
    line[strlen(line) - 1] = '\0';
  }
}

int main() {
  FILE *file = fopen(FILENAME, "re");
  if (file == nullptr) {
    return fprintf(stderr, "ERROR: when opening the file %s for reading\n",
                   FILENAME);
  }

  int64_t sum = 0;
  const int battery_count = 12;
  while (!feof(file)) {
    char buf[BUF_SIZE] = {};
    if (!fgets(buf, BUF_SIZE, file)) {
      break;
    }
    strip_newline(buf);
    sum += calculate_joltage(buf, battery_count);
  }

  printf("joltake rating: %ld", sum);

  if (fclose(file) == EOF) {
    return fprintf(stderr, "ERROR: when closing the file %s\n", FILENAME);
  }

  return 0;
}
