#include "node.hpp"
#include "../util.hpp"

GetVarNode::GetVarNode(Token *tokens): ExpressionNode() {
	int tempSize = 0;

	if (tokens->type == LABEL) {
		name = tokens->content;
		tempSize++;
		tokens++;
	} else {
		return;
	}

	tokenSize = tempSize;
	type = GETVAR_NODE;
};

GetVarNode::operator string() const {
	return "Get var (" + name + ")";
};

vector<Node*> GetVarNode::getChildren() {
	vector<Node*> result;
	return result;
};
