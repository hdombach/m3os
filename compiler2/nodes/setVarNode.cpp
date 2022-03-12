#include "node.hpp"
#include "../util.hpp"
#include "unistd.h"
#include "../error.hpp"

SetVarNode::SetVarNode(Token *tokens): StatementNode() {
	int tempSize = 0;

	if (tokens->type == LABEL) {
		name = tokens->content;
		tempSize++;
		tokens++;
	} else {
		return;
	}

	if (tokens->type == EQUALS) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	expression = ExpressionNode::create(tokens);
	if (expression->tokenSize > 0) {
		tempSize += expression->tokenSize;
		tokens += expression->tokenSize;
	} else {
		logTokenError(*tokens, "expected expression");
		return;
	}

	expression->parent = this;

	tokenSize = tempSize;
	type = SETVAR_NODE;

};

SetVarNode::operator string() const {
	string result = "";

	result += string(*expression);
	return "Set (" + name + ") to {\n" + indentString(result) + "\n}";
};

vector<Node*> SetVarNode::getChildren() {
	vector<Node*> result;

	result.push_back(expression);

	return result;
};
