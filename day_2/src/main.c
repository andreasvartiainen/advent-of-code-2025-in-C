#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t handle_number(const int64_t num) {
	char buf[256] = {};
	sprintf(buf, "%ld", num);

	int len = strlen(buf);
	// if number is not even we know that there can't be two identical sequences
	// printf("BUF: %s\n", buf);
	if (len % 2 != 0) {
		return 0;
	}
	// len = 8
	// len/2 = 4
	// i = 0
	for (int i = 0; i < len / 2; i++) {
		if(buf[i] != buf[i + (len / 2)]) {
			// printf("%c -- ", buf[i]);
			// printf("%c\n", buf[i + (len / 2)]);
			return 0;
		}
	}
	printf("INVALID: %s\n", buf);
	return num;
}

int handle_range(char *range, int64_t *sum) {
	char sRange[256] = {};
	char eRange[256] = {};

	char *split = strstr(range, "-");
	if (split == nullptr) {
		return 0;
	}

	*split = '\0';
	split++;

	strcpy(sRange, range);
	strcpy(eRange, split);

	int64_t sRangeInt = strtol(sRange, nullptr,10);
	int64_t eRangeInt = strtol(eRange, nullptr,10);

	for (int64_t i = sRangeInt; i <= eRangeInt; i++) {
		*sum += handle_number(i);
	}

	return 0;
}

int main() {
	FILE *file = {};
	file = fopen("ids.input", "r");
	if (file == nullptr) {
		return 1;
	}

	char buf[256] = {};
	int index = 0;
	int64_t sumOfInvalid = 0;
	while (!feof(file)) {
		char cBuf = (char)fgetc(file);

		if (isascii(cBuf)) {
			if (cBuf == ',') {
				handle_range(buf, &sumOfInvalid);
				index = 0;
				buf[index] = '\0';
				buf[index+1] = '\0';
			} else {
				buf[index] = cBuf;
				buf[index+1] = '\0';
				index++;
			}
		}
	}
	handle_range(buf, &sumOfInvalid);
	
	printf("sum of invalid: %ld\n", sumOfInvalid);

	return 0;
}
