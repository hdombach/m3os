#include "cCommand.hpp"
#include "../nodes/node.hpp"

string ccommand(StatementNode *node) {
	auto type = node->type;
	if (ExpressionNode::isChild(type)) {
		return ccommand((ExpressionNode *) node);
	}
	if (type == CREATEVAR_NODE) {
		return ccommand((CreateVarNode *) node);
	}
	if (type == DEFFUNC_NODE) {
		return ccommand((DefFuncNode *) node);
	}
	if (type == DEFSTRUCT_NODE) {
		return ccommand((DefStructNode *) node);
	}
	if (type == SETVAR_NODE) {
		return ccommand((SetVarNode *) node);
	}
	if (type == SETPOINTER_NODE) {
		return ccommand((SetPointerNode *) node);
	}
	if (type == IF_NODE) {
		return ccommand((IfNode *) node);
	}
	if (type == IFELSE_NODE) {
		return ccommand((IfElseNode *) node);
	}
	if (type == WHILE_NODE) {
		return ccommand((WhileNode *) node);
	}
	if (type == RETURN_NODE) {
		return ccommand((ReturnNode *) node);
	}
	if (type == BREAK_NODE) {
		return ccommand((BreakNode *) node);
	}
	return {};
};
