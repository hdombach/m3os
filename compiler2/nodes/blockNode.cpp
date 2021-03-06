#include "node.hpp"
#include "../util.hpp"
#include <iostream>
#include "../symbolTable.hpp"
#include "../error.hpp"

BlockNode::BlockNode(): Node() {};

BlockNode::BlockNode(Token *tokens): Node() {
	int tempSize = 0;
	while (true) {
		StatementNode *node = StatementNode::create(tokens);
		if (node->tokenSize > 0) {
			statements.push_back(node);
			tempSize += node->tokenSize;
			tokens += node->tokenSize;
		} else {
			break;
		}
	}

	for (int i = 0; i < statements.size(); i++) {
		statements[i]->parent = this;
	};

	table = nullptr;

	tokenSize = tempSize;
	type = BLOCK_NODE;
};

BlockNode::BlockNode(vector<StatementNode *> statements): Node() {
	this->statements = statements;
};

BlockNode::operator string() const {
	string result = "";
	for (int i = 0; i < statements.size(); i++) {
		StatementNode *statement = statements[i];
		result += string(*statement) + ",\n";
	}
	if (result.size() > 2) {
		result.pop_back();
		result.pop_back();
	}

	return "Block {\n" + indentString(result) + "\n}";
};

vector<Node*> BlockNode::getChildren() {
	vector<Node*> result;

	for (int i = 0; i < statements.size(); i++) {
		result.push_back(statements[i]);
	};

	return result;
};

SymbolTable *BlockNode::getTable() {
	return table;
}

void BlockNode::setTable(SymbolTable *table) {
	if (table != nullptr) {
		logError("the table block is set more than once");
	}
	this->table = table;
};
