#include "arg.h"

struct Arguments getArg(int argc, char *argv[]) {
	struct Arguments result;
	result.sourceFile = "main.asm";
	return result;
}
