#include "node.hpp"
#include "../util.hpp"
#include "../error.hpp"
#include <vector>
#include "../symbolTable.hpp"

FunctionCallNode::FunctionCallNode(Token *tokens): ExpressionNode() {
	int tempSize = 0;
	
	if (tokens->type == LABEL) {
		name = tokens->content;
		tempSize++;
		tokens++;
	} else {
		return;
	}

	if (tokens->type == OPENPARAN) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	while (true) {
		ExpressionNode *expression = ExpressionNode::create(tokens);
		if (expression->tokenSize > 0) {
			expressions.push_back(expression);
			tempSize += expression->tokenSize;
			tokens += expression->tokenSize;
		} else {
			break;
		}
	}

	if (tokens->type == CLOSEPARAN) {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, CLOSEPARAN);
		return;
	}

	for (int i = 0; i < expressions.size(); i++) {
		expressions[i]->parent = this;
	};

	tokenSize = tempSize;
	type = FUNCTIONCALL_NODE;
};

FunctionCallNode::operator string() const {
	string result = "";
	for (int c = 0; c < expressions.size(); c++) {
		ExpressionNode *expression = expressions[c];
		result += string(*expression) + ",\n";
	}
	return "Function Call (" + name + ") {\n" + indentString(result) + "}";
};

vector<Node*> FunctionCallNode::getChildren() {
	vector<Node *> result;

	for (int i = 0; i < expressions.size(); i++) {
		result.push_back(expressions[i]);
	};

	return result;
};



TypeNode *FunctionCallNode::getResultType() {
	vector<TypeNode*> types;
	for (int i = 0; i < expressions.size(); i++) {
		types.push_back(expressions[i]->getResultType());
	}
	return getParentBlock()->getTable()->getFunctionReturnType(name, types);
};
