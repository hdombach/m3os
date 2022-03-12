#include "token.h"
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "../shared/util.h"
#include  "arg.h"
#include "node.h"
#include "../shared/error.h"
#include "tests.h"
#include "symbolTable.h"

void handler(int sig) {
  void *array[10];
  size_t size;
  

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}


int main(int argc, char *argv[]) {
	signal(SIGSEGV, handler);   // install our handler	g

  initErrors();

  struct Arguments arg = getArg(argc, argv);
  char *data = readFile(arg.sourceFile);

	struct Darray tokens = tokenize(data);
	int c = 0;
  println("Tokens:");
	while (c < tokens.size) {
		struct Token token = *(struct Token *)get(tokens, c);
		printf("%s", tokenString(token));
		c++;
	}

  struct Node root = pageNode(tokens.data);
  println("nodes:\n%s", nodeString(root, 0));
  
  struct SymbolTable table = createTable(root);
  println("%s", symbolTableString(table));

  printErrors();
  println("just printed errors");
#ifdef DEBUG_TESTS
  addCompilerTests();
#endif
}


