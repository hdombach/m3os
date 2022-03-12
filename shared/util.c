#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "darray.h"
#include <stdarg.h>


void *resize(void *old, int newSize) {
	void *result = malloc(newSize);
	result = memcpy(result, old, newSize);
	free(old);
	return result;
}

char *readFile(char *filename) {
	FILE *fp;

	size_t r;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Unable to open %s\n", filename);
		return "";
	}

	struct Darray result = createDarray(sizeof(char), 16);
	
	while (1) {
		char current = getc(fp);
		if (feof(fp)) {
			break;
		}
		push(&result, &current);
	}
	return result.data;
}

void println(const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);
		printf("\n");
}

int strcstr(char *a, char *b) {
	if (strncmp(a, b, strlen(b)) == 0) {
		return 1;
	} else {
		return 0;
	}
}
