#include "node.hpp"
#include "../util.hpp"

Node::Node() {
	type = ERROR_NODE;
	position.column = 0;
	position.line = 0;
	tokenSize = 0;
};

Node::Node(Token *tokens) {
	type = ERROR_NODE;
	position = tokens->position;
	tokenSize = 0;
};

Node::operator string() const {
	return "(" + nodeTypeString(type) + ")";
};

string nodeTypeString(NodeType t) {
	switch (t) {
		case PAGE_NODE: return "Page";
		case BLOCK_NODE: return "Block";
		case CREATEVAR_NODE: return "Create var";
		case DEFFUNC_NODE: return "Def func";
		case SETVAR_NODE: return "Set var";
		case SETPOINTER_NODE: return "Set pointer";
		case IF_NODE: return "If";
		case IFELSE_NODE: return "If else";
		case WHILE_NODE: return "While";
		case RETURN_NODE: return "Return";
		case BREAK_NODE: return "Break";
		case FLOAT_NODE: return "float";
		case INT_NODE: return "int";
		case STRING_NODE: return "string";
		case FUNCTIONCALL_NODE: return "Function call";
		case OPERATION_NODE: return "Operation";
		case POINTER_NODE: return "Pointer";
		case GETPOINTER_NODE: return "Get Pointer";
		case DEFPARAM_NODE: return "Def param";
		case GETVAR_NODE: return "get var";
		case VARTYPE_NODE: return "var type";
		case ERROR_NODE: return "ERROR";
		default: return "ERROR";
	}
};

vector<Node*> Node::getChildren() {return vector<Node*>();};

BlockNode *Node::getParentBlock() {
	Node *current = this;
	while (current->type != BLOCK_NODE) {
		current = current->parent;
	}
	return (BlockNode*) current;
};

/*void Node::runFunc(void (*func)(Node *node), bool includeChildScope) {
	if (type == BLOCK_NODE) {
		return;
	}
	func(this);
	vector<Node*> children = getChildren();
	for (int i = 0; i < children.size(); i++) {
		children[i]->runFunc(func, includeChildScope);
	}
}*/

vector<Node*> Node::getNestedChildren(bool includeChildScope) {

	vector<Node*> result;

	vector<Node*> children = this->getChildren();

	for (int i = 0; i < children.size(); i++) {

		Node *child = children[i];
		if (!(child->type == BLOCK_NODE && !includeChildScope)) {
			result.push_back(child);
			vector<Node*> childChildren = child->getNestedChildren(includeChildScope);
			result.insert(result.end(), childChildren.begin(), childChildren.end());
		}
	}

	return result;
};

vector<BlockNode*> Node::getNestedBlocks() {
	vector<Node*> children = getNestedChildren();
	vector<BlockNode*> result;

	for (int i = 0; i < children.size(); i++) {

		Node *child = children[i];
		if (child->type == BLOCK_NODE) {
			result.push_back((BlockNode *) child);
		}
	}
	return result;
};
