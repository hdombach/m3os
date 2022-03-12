#include "node.hpp"
#include "../util.hpp"

BreakNode::BreakNode(): StatementNode() {};

BreakNode::BreakNode(Token *tokens): StatementNode() {
	int tempSize = 0;

	if (tokens->type == BREAK) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	tokenSize = tempSize;
	type = BREAK_NODE;
};

BreakNode::operator string() const {
	return "Break";
};

vector<Node*> BreakNode::getChildren() {
	vector<Node*> result;

	return result;
};
