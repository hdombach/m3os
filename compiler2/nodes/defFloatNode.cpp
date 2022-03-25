#include "node.hpp"
#include "defaults.hpp"

DefFloatNode::DefFloatNode() {
	name = "float";
	content = new BlockNode();
	type = DEFFLOAT_NODE;
}

DefFloatNode::operator string() const {
	return "Defing float";
};

int DefFloatNode::getAllocatedSize() {
	return 4;
};
