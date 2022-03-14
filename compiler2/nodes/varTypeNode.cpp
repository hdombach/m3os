#include "node.hpp"
#include "../util.hpp"

VarTypeNode::VarTypeNode(): TypeNode() {};

VarTypeNode::VarTypeNode(Token *tokens): TypeNode() {
	if (tokens->type == LABEL) {
		tokenSize = 1;
		name = tokens->content;
		type = VARTYPE_NODE;
	}
};

VarTypeNode::operator string() const {
	 return "Var type (" + name + ")";
}

vector<Node*> VarTypeNode::getChildren() {
	return vector<Node*>();
};

bool VarTypeNode::operator == (const VarTypeNode &b) {
	return name == b.name;
};
