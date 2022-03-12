#include "node.hpp"
#include "../util.hpp"
#include "../symbolTable.hpp"

IntNode::IntNode(Token *tokens): ExpressionNode() {
	int tempSize = 0;

	if (tokens->type == INT) {
		value = stoi(tokens->content);
		tempSize++;
		tokens++;
	} else {
		return;
	}

	tokenSize = tempSize;
	type = INT_NODE;
};

IntNode::operator string() const {
	return "Int (" + to_string(value) + ")";
};

vector<Node*> IntNode::getChildren() {
	vector<Node*> result;

	return result;
};

TypeNode *IntNode::getResultType() {
	return getParentBlock()->getTable()->getVarType("int");
};
