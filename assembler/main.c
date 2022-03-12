#include "word.h"
#include <stdio.h>
#include "../shared/darray.h"
#include "../shared/util.h"
#include <stdlib.h>
#include "arg.h"

int main(int argc, char *argv[]) {
	struct Arguments arg = getArg(argc, argv);
	
	char *data = readFile(arg.sourceFile);

	struct Darray words = getWords(data);

	int c = 0;
	while (words.size > c) {
		printf("%s\n", (char *) get(words, c));
		c++;
	}

}
