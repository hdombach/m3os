#include "node.hpp"
#include "../util.hpp"
#include "../error.hpp"

SetPointerNode::SetPointerNode(Token *tokens): StatementNode() {
	int tempSize = 0;

	if (tokens->type == AT) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	pointerExpression = ExpressionNode::create(tokens);
	if (pointerExpression->tokenSize > 0) {
		tempSize += pointerExpression->tokenSize;
		tokens += pointerExpression->tokenSize;
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

	pointerExpression->parent = this;
	expression->parent = this;

	tokenSize = tempSize;
	type = SETPOINTER_NODE;
};

SetPointerNode::operator string() const {
	string result = "";
	result += string(*pointerExpression);
	result += ",\n";
	result += string(*expression);

	return "Set Pointer {\n" + indentString(result) + "\n}";
};

vector<Node*> SetPointerNode::getChildren() {
	vector<Node*> result;

	result.push_back(pointerExpression);
	result.push_back(expression);

	return result;
};
