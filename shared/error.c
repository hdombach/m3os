#include "error.h"
#include "darray.h"
#include "util.h"

struct Darray errors;

void initErrors() {
	errors = createDarray(sizeof(char **), 16);
}

void logError(char *e) {
	push(&errors, &e);
}

void printErrors() {
	int c = 0;
	println("%d error(s).", errors.size);

	while (errors.size > c) {
		println("Error: %s", *(char **)get(errors, c));
		c++;
	}
}

