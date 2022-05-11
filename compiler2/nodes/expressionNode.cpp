#include "node.hpp"
#include "../util.hpp"
#include <iostream>
#include "unistd.h"

ExpressionNode::ExpressionNode(): StatementNode() {};

ExpressionNode *ExpressionNode::create(Token *tokens, bool includeOperation) {
	ExpressionNode *result;

	if (includeOperation) {
		result = new OperationNode(tokens);
		if (result->tokenSize > 0) {
			return result;
		} else {
			delete result;
		}
	}

	result = new FloatNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new IntNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new StringNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new FunctionCallNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new PointerNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new GetPointerNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		delete result;
	}

	result = new GetVarNode(tokens);
	if (result->tokenSize > 0) {
		return result;
	} else {
		//needs to have a valid pointer when returned
		//delete result;
	}

	return result;
};

ExpressionNode::operator string() const {
	return "Error node";
};

vector<Node*> ExpressionNode::getChildren() {return vector<Node*>();};

TypeNode *ExpressionNode::getResultType() {return new TypeNode();};

bool ExpressionNode::isChild(NodeType type) {
	if (type == OPERATION_NODE) {
		return true;
	}
	if (type == FLOAT_NODE) {
		return true;
	}
	if (type == INT_NODE) {
		return true;
	}
	if (type == STRING_NODE) {
		return true;
	}
	if (type == FUNCTIONCALL_NODE) {
		return true;
	}
	if (type == POINTER_NODE) {
		return true;
	}
	if (type == GETPOINTER_NODE) {
		return true;
	}
	if (type == GETVAR_NODE) {
		return true;
	}
	return false;
};
