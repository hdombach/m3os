#include "node.hpp"
#include "../error.hpp"
#include "../util.hpp"
#include <iostream>

using namespace std;

TemplateFunctionTypeNode::TemplateFunctionTypeNode(): FunctionTypeNode() {};

TemplateFunctionTypeNode::TemplateFunctionTypeNode(Token *tokens) {
	int tempSize = 0;

	if (tokens->type == OPENPARAN) {
		tokens++;
		tempSize++;
	} else {
		return;
	}

	while (true) {
		TypeNode *type = TypeNode::create(tokens);
		if (type->tokenSize > 0) {
			params.push_back(type);
			tempSize += type->tokenSize;
			tokens += type->tokenSize;
		} else {
			break;
		}
		if (tokens->type == COMMA) {
			tokens++;
			tempSize++;
		} else {
			break;
		}
	}

	if (tokens->type == CLOSEPARAN) {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, CLOSEPARAN);
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
			templateParams.push_back(type);
			tempSize += type->tokenSize;
			tokens += type->tokenSize;
		} else {
			break;
		}
		if (tokens->type == COMMA) {
			tokens++;
			tempSize++;
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

	if (tokens->type == RETURNS) {
		tempSize++;
		tokens++;
	} else {
		logTokenError(*tokens, RETURNS);
		return;
	}

	returnType = TypeNode::create(tokens);
	if (returnType->tokenSize > 0) {
		tempSize += returnType->tokenSize;
		tokens += returnType->tokenSize;
		cout << "the return type is of length " + to_string(returnType->tokenSize) + "\n";
	} else {
		logTokenError(*tokens, "expected return type");
		return;
	}

	for (int i = 0; i < params.size(); i++) {
		params[i]->parent = this;
	};
	for (int i = 0; i < templateParams.size(); i++) {
		templateParams[i]->parent = this;
	};
	returnType->parent = this;

	tokenSize = tempSize;
	type = TEMPLATEFUNCTIONTYPE_NODE;
};

TemplateFunctionTypeNode::operator string() const {
	string result = "";
	result += "params:\n";
	
	for (int i = 0; i < params.size(); i++) {
		result += string(*params[i]);
	}
	result.pop_back();
	result.pop_back();

	result += "\n";
	result += "template types:\n";

	for (int i = 0; i < templateParams.size(); i++) {
		result += string (*params[i]);
	}
	result.pop_back();
	result.pop_back();

	result += "returns:\n";
	result += string(*returnType);

	return "Template function type {\n" + indentString(result) + "\n}";
};

vector<Node*> TemplateFunctionTypeNode::getChildren() {
	vector<Node*> result;

	for (int i = 0; i < params.size(); i++) {
		result.push_back(params[i]);
	};
	for (int i = 0; i < templateParams.size(); i++) {
		result.push_back(templateParams[i]);
	};
	result.push_back(returnType);

	return result;
};

bool TemplateFunctionTypeNode::operator == (const TemplateFunctionTypeNode &b) {
	bool b1 = params == b.params;
	bool b2 = returnType == b.returnType;
	bool b3 = templateParams == b.templateParams;
	return b1 && b3 && b3;
};
