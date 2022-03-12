#include "node.hpp"
#include "../util.hpp"
#include "../error.hpp"

//TODO: make this work with nested if elses.

IfElseNode::IfElseNode(): StatementNode() {};

IfElseNode::IfElseNode(Token *tokens): StatementNode() {
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

	trueBlock = BlockNode(tokens);
	if (trueBlock.tokenSize > 0) {
		tempSize += trueBlock.tokenSize;
		tokens += trueBlock.tokenSize;
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

	if (tokens->type == ELSE) {
		tempSize++;
		tokens++;
	} else { //alright if this happens because that just means it is a plain if
		return;
	}

	if (tokens->type == OPENCURLY) {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, OPENCURLY);
		return;
	}

	falseBlock = BlockNode(tokens);
	if (falseBlock.tokenSize > 0) {
		tempSize += falseBlock.tokenSize;
		tokens += falseBlock.tokenSize;
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
	trueBlock.parent = this;
	falseBlock.parent = this;

	tokenSize = tempSize;
	type = IFELSE_NODE;
};

IfElseNode::operator string() const {
	string result = "";
	result += string(*expression) + ",\n";
	result += string(trueBlock) + ",\n";
	result += string(falseBlock);

	return "If else {\n" + indentString(result) + "\n}";
};

vector<Node*> IfElseNode::getChildren() {
	vector<Node*> result;

	result.push_back(expression);
	result.push_back(&trueBlock);
	result.push_back(&falseBlock);

	return result;
};
