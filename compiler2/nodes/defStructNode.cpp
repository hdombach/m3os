#include "node.hpp"
#include "../error.hpp"
#include "../util.hpp"
#include "../symbolTable.hpp"

DefStructNode::DefStructNode(): StatementNode() {};

DefStructNode::DefStructNode(Token *tokens): StatementNode() {
	int tempSize = 0;

	if (tokens->type == STRUCT) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	if (tokens->type == LABEL) {
		name = tokens->content;
		tokenSize++;
		tokens++;
	} else {
		logTokenError(*tokens, LABEL);
		return;
	}

	if (tokens->type == OPENCURLY) {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, OPENCURLY);
		return;
	}

	content = new BlockNode(tokens);
	if (content->tokenSize > 0) {
		tempSize += content->tokenSize;
		tokens += content->tokenSize;
	} else {
		logTokenError(*tokens, BLOCK_NODE);
		return;
	}

	if (tokens->type == CLOSECURLY) {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, CLOSECURLY);
	}

	content->parent = this;

	tokenSize = tempSize;
	type = DEFSTRUCT_NODE;
};

DefStructNode::DefStructNode(string name, BlockNode *content) {
	this->name = name;
	this->content = content;
};

DefStructNode::DefStructNode(string name, vector<StatementNode*> definitions) {
	this->name = name;
	this->content = new BlockNode(definitions);
};

DefStructNode::operator string() const {
	return "DefStruct (" + name + ") {\n" + indentString(string(*content)) + "\n}";
};

vector<Node*> DefStructNode::getChildren() {
	return {content};
};

int DefStructNode::getAllocatedSize() {
	return content->getTable()->getTotalAllocatedSize();
};
