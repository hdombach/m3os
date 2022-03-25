#include "defaults.hpp"
#include "node.hpp"

DefCharNode::DefCharNode() {
	name = "char";
	content = new BlockNode();

	type = DEFCHAR_NODE;
};

DefCharNode::operator string() const {
	return "Defing char";
};

int DefCharNode::getAllocatedSize() {
	return 1;
};
