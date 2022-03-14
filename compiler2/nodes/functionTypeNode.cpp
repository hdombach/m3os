#include "node.hpp"
#include "../error.hpp"
#include "../util.hpp"

FunctionTypeNode::FunctionTypeNode(): TypeNode() {};

FunctionTypeNode::FunctionTypeNode(Token *tokens) {
	int tempSize = 0;

	if (tokens->type == OPENPARAN) {
		tempSize++;
		tokens++;
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
			tokenSize++;
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
	} else {
		logTokenError(*tokens, "expected return type");
		return;
	}

	for (int i = 0; i < params.size(); i++) {
		params[i]->parent = this;
	};
	returnType->parent = this;

	tokenSize = tempSize;
	type = FUNCTIONTYPE_NODE;
};

FunctionTypeNode::operator string() const {
	string result = "";
	result += "params:\n";

	for (int i = 0; i < params.size(); i++) {
		result += string(*params[i]) + ",\n";
	}

	result.pop_back();
	result.pop_back();

	result += "\nreturns:\n";
	result += string(*returnType);

	return "Function type {\n" + indentString(result) + "\n}";
};

vector <Node*> FunctionTypeNode::getChildren() {
	vector<Node*> result;

	for (int i = 0; i < params.size(); i++) {
		result.push_back(&parent[i]);
	}
	result.push_back(returnType);

	return result;
};

bool FunctionTypeNode::operator == (const FunctionTypeNode &b) {
	bool b1 = params == b.params;
	bool b2 = returnType == b.returnType;

	return b1 && b2;
};
