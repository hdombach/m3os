#include "node.hpp"
#include "../util.hpp"
#include "../error.hpp"
#include <vector>

DefFuncNode::DefFuncNode(): StatementNode() {};

DefFuncNode::DefFuncNode(Token *tokens): StatementNode() {
	int tempSize = 0;

	if (tokens->type == FUNC) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	if (tokens->type == LABEL) {
		name = tokens->content;
		tokenSize++;
		tokens++;
	} else {
		logTokenError(*tokens, LABEL);
		return;
	}

	if (tokens->type == OPENPARAN) {
		tokenSize++;
		tokens++;
	} else {
		logTokenError(*tokens, OPENPARAN);
		return;
	}

	while (true) {
		DefParamNode tempParam = DefParamNode(tokens);
		if (tempParam.tokenSize > 0) {
			params.push_back(tempParam);
			tempSize += tempParam.tokenSize;
			tokens += tempParam.tokenSize;
		} else {
			break;
		}
	}

	if (tokens->type == CLOSEPARAN) {
		tokenSize++;
		tokens++;
	} else {
		logTokenError(*tokens, CLOSEPARAN);
		return;
	}

	//TODO: add returns

	if (tokens->type == OPENCURLY) {
		tokenSize++;
		tokens++;
	} else {
		logTokenError(*tokens, OPENCURLY);
		return;
	}

	block = BlockNode(tokens);
	if (block.tokenSize > 0) {
		tempSize += block.tokenSize;
		tokens += block.tokenSize;
	} else {
		logTokenError(*tokens, BLOCK_NODE);
		return;
	}

	if (tokens->type == CLOSECURLY) {
		tokenSize++;
		tokens++;
	} else {
		logTokenError(*tokens, CLOSECURLY);
		return;
	}

	for (int i = 0; i < params.size(); i++) {
		params[i].parent = this;
	}
	returnType.parent = this;
	block.parent = this;

	tokenSize = tempSize;
	type = DEFFUNC_NODE;
	return;
};

DefFuncNode::operator string() const {
	string result = "";

	if (params.size() > 0) {
		for (int i = 0; i <  params.size(); i++) {
			DefParamNode param = params[i];
			result += string(param) + ",\n";
		}
		result.pop_back();
		result.pop_back();
		result = "Params {\n" + indentString(result) + "\n},\n";
	}

	result += string(block);

	return "Def func {\n" + indentString(result) + "\n}";

};

TypeNode DefFuncNode::getFuncType() {
	FunctionTypeNode result;
	result.returnType = &returnType;
	result.position = position;

	for (int i = 0; i < params.size(); i++) {
		DefParamNode param = params[i];
		result.params.push_back(param.varType);
	}

	return result;
};

vector<Node*> DefFuncNode::getChildren() {
	vector<Node*> result;

	for (int i = 0; i < params.size(); i++) {
		result.push_back(&params[i]);
	}
	result.push_back(&returnType);
	result.push_back(&block);

	return result;
};
