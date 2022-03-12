#include "node.hpp"

TypeNode::TypeNode() {};

TypeNode *TypeNode::create(Token *tokens) {
	TypeNode *result;

	result = new TemplateFunctionType(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new FunctionTypeNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new TemplateTypeNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new VarTypeNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	return result;
};

vector<Node*> TypeNode::getChildren() {return vector<Node*>();};
