#include "defaults.hpp"
#include "node.hpp"

DefIntNode::DefIntNode() {
	name = "int";
	content = new BlockNode();
	type = DEFINT_NODE;
}

DefIntNode::operator string() const {
	return "Defing int node";
};

int DefIntNode::getAllocatedSize() {
	return 4;
};
