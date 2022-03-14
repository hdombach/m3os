#include "node.hpp"
#include "../error.hpp"
#include "../util.hpp"

TemplateTypeNode::TemplateTypeNode(): VarTypeNode() {};

TemplateTypeNode::TemplateTypeNode(Token *tokens) {
	int tempSize = 0;

	if (tokens->type == LABEL) {
		name = tokens->content;
		tempSize++;
		tokens++;
	} else {
		return;
	}

	if (tokens->type == OPERAND && tokens->content == "<") {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	while (true) {
		TypeNode *type = TypeNode::create(tokens);
		if (type->tokenSize > 0) {
			types.push_back(type);
			tempSize += type->tokenSize;
			tokens += type->tokenSize;
		} else {
			break;
		}
		if (tokens->type == COMMA) {
			tempSize++;
			tokens++;
		} else {
			break;
		}
	}

	if (tokens->type == OPERAND && tokens->content == ">") {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, "expected >");
		return;
	}

	for (int i = 0; i < types.size(); i++) {
		types[i]->parent = this;
	};

	tokenSize = tempSize;
	type = TEMPLATETYPE_NODE;
};

TemplateTypeNode::operator string() const {
	string result = "";

	for (int i = 0; i < types.size(); i++) {
		result += string(*types[i]) + ",\n";
	};
	if (result.size() > 0) {
		result.pop_back();
		result.pop_back();
	}

	return "Template type (" + name + ") {\n" + indentString(result) + "\n}";
};

vector<Node*> TemplateTypeNode::getChildren() {
	vector<Node*> result;

	for (int i = 0; i < types.size(); i++) {
		result.push_back(types[i]);
	}	

	return result;
};

bool TemplateTypeNode::operator == (const TemplateTypeNode &b) {
	bool b1 = name == b.name;
	bool b2 = types == b.types;
	return b1 && b2;
};
