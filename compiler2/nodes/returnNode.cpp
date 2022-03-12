#include "node.hpp"
#include "../util.hpp"

ReturnNode::ReturnNode(): StatementNode() {};

ReturnNode::ReturnNode(Token *tokens): StatementNode() {
	int tempSize = 0;

	if (tokens->type == RETURN) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	expression = ExpressionNode::create(tokens);
	if (expression->tokenSize > 0) {
		tempSize += expression->tokenSize;
		tokens += expression->tokenSize;
	}

	expression->parent = this;

	tokenSize = tempSize;
	type = RETURN_NODE;
};

ReturnNode::operator string() const {
	string result = "";
	result += string(*expression);
	return "Return {\n" + indentString(result) + "\n}";
};

vector<Node*> ReturnNode::getChildren() {
	vector<Node*> result;

	result.push_back(expression);

	return result;
};
