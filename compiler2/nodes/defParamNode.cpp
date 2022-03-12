#include "node.hpp"
#include "../util.hpp"
#include "../error.hpp"
#include <vector>

DefParamNode::DefParamNode(Token *tokens): Node() {
	int tempSize = 0;

	if (tokens->type == LABEL) {
		name = tokens->content;
		tempSize++;
		tokens++;
	} else {
		return;
	}

	if (tokens->type == COLON) {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, COLON);
		return;
	}

	varType = new VarTypeNode(tokens);
	if (varType->tokenSize > 0) {
		tempSize += varType->tokenSize;
		tokens += varType->tokenSize;
	} else {
		logTokenError(*tokens, VARTYPE_NODE);
		return;
	}

	varType->parent = this;

	tokenSize = tempSize;
	type = DEFPARAM_NODE;
	return;
};

DefParamNode::operator string() const {
	string result = string(*varType);
	result = indentString(result);
	return "Def param (" + name + ") {\n" + result + "\n}";
};

vector<Node*> DefParamNode::getChildren() {
	vector<Node*> result;
	result.push_back(varType);
	return result;
};
