#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include "token.hpp"
#include "nodes/node.hpp"

using namespace std;

void logError(string e);
void logTokenError(Token t, string msg);
void logTokenError(Token t, TokenType expected);
void logTokenError(Token t, NodeType expected);
void logInternalError(string e);
string getErrors();
int getErrorLength();
void printErrors();

#endif
