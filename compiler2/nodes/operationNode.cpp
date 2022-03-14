#include "node.hpp"
#include "../util.hpp"
#include "../error.hpp"
#include <vector>
#include "../symbolTable.hpp"

//TODO: add ()

OperationNode::OperationNode(Token *tokens): ExpressionNode() {
	int tempSize = 0;

	leftExpression = ExpressionNode::create(tokens, false);
	if (leftExpression->tokenSize > 0) {
		tempSize += leftExpression->tokenSize;
		tokens += leftExpression->tokenSize;
	} else {
		return;
	}

	if (tokens->type == OPERAND) {
		operation = tokens->content;
		tempSize++;
		tokens++;
	} else {
		return;
	}

	rightExpression = ExpressionNode::create(tokens);
	if (rightExpression->tokenSize > 0) {
		tempSize += rightExpression->tokenSize;
		tokens += rightExpression->tokenSize;
	} else {
		logTokenError(*tokens, "expected expression");
		return;
	}

	leftExpression->parent = this;
	rightExpression->parent = this;

	tokenSize = tempSize;
	type = OPERATION_NODE;
};

OperationNode::operator string() const {
	string result = "";
	result += string(*leftExpression) + ",\n";
	result += string(*rightExpression);

	return "Operation (" + operation + ") {\n" + indentString(result) + "\n}";
};

vector<Node*> OperationNode::getChildren() {
	vector<Node*> result;

	result.push_back(leftExpression);
	result.push_back(rightExpression);

	return result;
};

TypeNode *OperationNode::getResultType() {
	vector<TypeNode*> types;
	types.push_back(leftExpression->getResultType());
	types.push_back(rightExpression->getResultType());

	return getParentBlock()->getTable()->getFunctionReturnType(operation, types);
};
