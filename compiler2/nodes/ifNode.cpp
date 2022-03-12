#include "node.hpp"
#include "../util.hpp"
#include "../error.hpp"

IfNode::IfNode(): StatementNode() {};

IfNode::IfNode(Token *tokens): StatementNode() {
	int tempSize = 0;

	if (tokens->type == IF) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	expression = ExpressionNode::create(tokens);
	if (expression->tokenSize > 0) {
		tempSize += expression->tokenSize;
		tokens += expression->tokenSize;
	} else {
		logTokenError(*tokens, "expected expression");
		return;
	}

	if (tokens->type == OPENCURLY) {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, OPENCURLY);
		return;
	}

	block = BlockNode(tokens);
	if (block.tokenSize > 0) {
		tempSize += block.tokenSize;
		tokens += block.tokenSize;
	} else {
		logTokenError(*tokens, BLOCK_NODE);
		return;
	}

	if (tokens->type == CLOSECURLY) {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, CLOSECURLY);
		return;
	}

	expression->parent = this;
	block.parent = this;

	tokenSize = tempSize;
	type = IF_NODE;
};

IfNode::operator string() const {
	string result = "";
	result += string(*expression);
	result += ",\n";
	result += string(block);
	return "If {\n" + indentString(result) + "\n}";
}

vector<Node*> IfNode::getChildren() {
	vector<Node*> result;

	result.push_back(expression);
	result.push_back(&block);

	return result;
};
