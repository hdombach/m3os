#include "cCommand.hpp"
#include "../error.hpp"

string ccommand(ExpressionNode *node) {
	auto type = node->type;
	if (type == FLOAT_NODE) {
		return ccommand((FloatNode*)node);
	} else if (type == INT_NODE) {
		return ccommand((IntNode*)node);
	} else if (type == STRING_NODE) {
		return ccommand((StringNode*)node);
	} else if (type == FUNCTIONCALL_NODE) {
		return ccommand((FunctionCallNode*)node);
	} else if (type == OPERATION_NODE) {
		return ccommand((OperationNode*)node);
	} else if (type == POINTER_NODE) {
		return ccommand((PointerNode*)node);
	} else if (type == GETVAR_NODE) {
		return ccommand((GetVarNode*)node);
	};
	logError("Invalid ccommand for expression node");
	return "";
};
