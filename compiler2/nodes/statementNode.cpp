#include "node.hpp"
#include "../util.hpp"
#include "../error.hpp"
#include <iostream>

using namespace std;

StatementNode::StatementNode(): Node() {};
StatementNode *StatementNode::create(Token *tokens) {
	StatementNode *result;

	result = new DefFuncNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new CreateVarNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new SetVarNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new SetPointerNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = ExpressionNode::create(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new IfElseNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new IfNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new WhileNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new ReturnNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new BreakNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		//delete result;
	}

	return result;

};

StatementNode::operator string() const { return "error"; };
