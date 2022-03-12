#include "node.hpp"
#include "../util.hpp"
#include <strings.h>
#include "../error.hpp"

PointerNode::PointerNode(Token *tokens): ExpressionNode() {
	int tempSize = 0;

	if (tokens->type == AT) {
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
	type = POINTER_NODE;
};

PointerNode::operator string() const {
	string result = "";
	result += string(*expression);
	return "Pointer {\n" + indentString(result) + "\n}";
};

vector<Node*> PointerNode::getChildren() {
	vector<Node*> result;

	result.push_back(expression);

	return result;
};
