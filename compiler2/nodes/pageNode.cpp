#include "node.hpp"
#include "../util.hpp"
#include <iostream>

PageNode::PageNode(Token *tokens): Node() {
	block = BlockNode(tokens);
	block.parent = this;
	tokenSize = block.tokenSize;
	type = PAGE_NODE;
};

PageNode::operator string() const {
	string result = string(block);

	return "Page {\n" + indentString(result) + "\n}";
};

vector<Node*> PageNode::getChildren() {
	vector<Node*> result;

	result.push_back(&block);

	return result;
}
