#include "node.hpp"
#include "../util.hpp"
#include <string>
#include "../error.hpp"
#include "../symbolTable.hpp"

using namespace std;

FloatNode::FloatNode(Token *tokens): ExpressionNode() {
	int tempSize = 0;

	if (tokens->type == INT) {
		value = stof(tokens->content);
		tempSize++;
		tokens++;
	} else {
		return;
	}

	if (tokens->type == PERIOD) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	//TODO: make it so you don't have to define something after .

	if (tokens->type == INT) {
		value += stof("0." + tokens->content);
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, INT);
		return;
	}

	tokenSize = tempSize;
	type = FLOAT_NODE;
};

FloatNode::operator string() const {
	return "Float (" + to_string(value) + ")";
};

vector<Node*> FloatNode::getChildren() {
	vector<Node*> result;

	return result;
};

TypeNode *FloatNode::getResultType() {
	return getParentBlock()->getTable()->getVarType("float");
};
