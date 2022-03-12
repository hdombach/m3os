#include <stdio.h>
#include <string.h>
#include "word.h"
#include "../shared/util.h"
#include "../shared/darray.h"

struct Darray getWords(char *data) {
	char whitespaces[] = {' ', '\n', '\t'};
	int whitespacesSize = sizeof(whitespaces) / sizeof(char);

	struct Darray word = createDarray(sizeof(char), 16);
	struct Darray result = createDarray(sizeof(char *), 16);

	int index = 0;

	while (1) {
		char current = data[index];
		if (current == '\0') {
			break;
		}
		int isWhitespace = 0;
		int whitespaceIndex = 0;
		while (whitespacesSize > whitespaceIndex) {
			if (current == whitespaces[whitespaceIndex]) {
				isWhitespace = 1;
			}
			whitespaceIndex++;
		}

		if (isWhitespace == 1) {
			if (word.size > 0) {
				push(&result, word.data);
				word = createDarray(sizeof(char), 16);
			}
		} else {
			push(&word, &current);
		}
		index++;
	}

	if (word.size > 0) {
		push(&result, word.data);
	}
	return result;
}

