#include <execinfo.h>
#include <iostream>
#include "arg.hpp"
#include "util.hpp"
#include "token.hpp"
#include "nodes/node.hpp"
#include <unistd.h>
#include <vector>
#include <string>
#include <signal.h>
#include <stdlib.h>
#include "error.hpp"

using namespace std;

void error_handler(int sig) {
	cout << to_string(sig);
  void *array[10];
  size_t size;
  size = backtrace(array, 10); //get the void pointers for all of the entries
  cout << "Error: signal "<< sig <<":\n"; //display error signal
  backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

int main(int argc, char* argv[]) {
	//signal(SIGBUS, error_handler);
	//signal(SIGSEGV, error_handler);
	signal(SIGSEGV, error_handler);

	Arguments arg = getArg(argc, argv);
	string data = readFile(arg.sourceFile);

	//vector<Token> tokens;
	vector<Token> tokens = tokenize(data);

	cout << "Tokens: \n";


	string result = "";
	for (int i=0; i < tokens.size(); i++) {
		Token t  = tokens[i];
		result += string(t) + "\n";
	}

	cout << result;
	PageNode temp = PageNode(tokens.data());
	Node *root = &temp;

	cout << string(*root) + "\n";


	cout << "Compiled with " + to_string(getErrorLength()) + " errors\n";
	printErrors();
}
