#include "node.hpp"
#include "../util.hpp"
#include "../error.hpp"
#include <iostream>

using namespace std;

CreateVarNode::CreateVarNode(): StatementNode() {};

//TODO: make it so you don't have to declare a var

CreateVarNode::CreateVarNode(Token *tokens): StatementNode() {
	int tempOffset = 0;
	if (tokens->type == VAR) {
		tempOffset++;
		tokens++;
	} else {
		return;
	}

	if (tokens->type == LABEL) {
		name = tokens->content;
		tempOffset++;
		tokens++;
	} else {
		logTokenError(*tokens, "expected label");
		return;
	}

	if (tokens->type == COLON) {
		tempOffset++;
		tokens++;

		
		valueType = TypeNode::create(tokens);
		if (valueType->tokenSize > 0) {
			tempOffset += valueType->tokenSize;
			tokens += valueType->tokenSize;
		} else {
			logTokenError(*tokens, "expected type");
			return;
		}
	}

	if (tokens->type == EQUALS) {
		tempOffset++;
		tokens++;
	} else {
		logTokenError(*tokens, "expected equals");
		return;
	}

	expression = ExpressionNode::create(tokens);
	if (expression->tokenSize > 0) {
		tempOffset += expression->tokenSize;
		tokens += expression->tokenSize;
	} else {
		logTokenError(*tokens, "expected expression");
		return;
	}

	valueType->parent = this;
	expression->parent = this;

	tokenSize = tempOffset;
	type = CREATEVAR_NODE;
	return;
};

CreateVarNode::operator string() const {
	string result = "";
	if (valueType != NULL) {
		result += "type: " + string(*valueType) + ",\n";
	}
	result += "expression: " + string(*expression);
	return "Create var (" + name + ") {\n" + indentString(result) + "\n}";
};

TypeNode *CreateVarNode::getVarType() {
	return expression->getResultType();
};

vector<Node*> CreateVarNode::getChildren() {
	vector<Node*> result;

	result.push_back(valueType);
	result.push_back(expression);

	return result;
};
