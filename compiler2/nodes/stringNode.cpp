#include "node.hpp"
#include "../util.hpp"
#include "../symbolTable.hpp"

StringNode::StringNode(Token *tokens): ExpressionNode() {
	int tempSize = 0;

	if (tokens->type == STRING) {
		value = tokens->content;
		tempSize++;
		tokens++;
	} else {
		return;
	}

	tokenSize = tempSize;
	type = STRING_NODE;
};

StringNode::operator string() const {
	return "String (" + value + ")";
};

vector<Node*> StringNode::getChildren() {
	vector<Node*> result;

	return result;
};

TypeNode *StringNode::getResultType() {
	return getParentBlock()->getTable()->getVarType("string");
};
