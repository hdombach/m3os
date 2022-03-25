#include "error.hpp"
#include "token.hpp"
#include "nodes/node.hpp"
#include "util.hpp"
#include <vector>
#include <iostream>

using namespace std;

vector<string> errors;

void logError(string e) {
	errors.push_back(e);
};

void logTokenError(Token t, string msg) {
	logError(string(t) + ": " + msg);
};

void logTokenError(Token t, TokenType expected) {
	logTokenError(t, "expected " + tokenTypeString(expected));
};

void logTokenError(Token t, NodeType expected) {
	logTokenError(t, "expected " + nodeTypeString(expected));
}

void logInternalError(string e) {
	logError("INTERNAL: " + e);
};

string getErrors() {
	string result = "";

	for (int i = 0; i < errors.size(); i++) {
		string error = errors[i];
		result += error + "\n";
	}

	return result;
};

int getErrorLength() {
	return errors.size();
};

void printErrors() {
	cout << getErrors();
};
