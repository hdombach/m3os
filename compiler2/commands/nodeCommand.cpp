#include "command.hpp"
#include "../nodes/node.hpp"

vector<Command *> command(StatementNode *node) {
	auto type = node->type;
	if (ExpressionNode::isChild(type)) {
		return command((ExpressionNode *) node);
	}
	if (type == CREATEVAR_NODE) {
		return command((CreateVarNode *) node);
	}
	if (type == DEFFUNC_NODE) {
		return command((DefFuncNode *) node);
	}
	if (type == DEFSTRUCT_NODE) {
		return command((DefStructNode *) node);
	}
	if (type == SETVAR_NODE) {
		return command((SetVarNode *) node);
	}
	if (type == SETPOINTER_NODE) {
		return command((SetPointerNode *) node);
	}
	if (type == IF_NODE) {
		return command((IfNode *) node);
	}
	if (type == IFELSE_NODE) {
		return command((IfElseNode *) node);
	}
	if (type == WHILE_NODE) {
		return command((WhileNode *) node);
	}
	if (type == RETURN_NODE) {
		return command((ReturnNode *) node);
	}
	if (type == BREAK_NODE) {
		return command((BreakNode *) node);
	}
	return {};
};

vector<Command *> command(BlockNode *node) {
	vector<Command *> result;
	for (int i = 0; i < node->statements.size(); i++) {
		append(result, command(node->statements[i]));
	}
	node->createdCommands = result;
	return result;
};

vector<Command *> command(PageNode *node) {
	return command(&node->block);
};

vector<Command *> command(ExpressionNode *node) {
	auto type = node->type;
	if (type == FLOAT_NODE) {
		return command((FloatNode *) node);
	}
	if (type == INT_NODE) {
		return command((IntNode *) node);
	}
	if (type == STRING_NODE) {
		return command((StringNode *) node);
	}
	if (type == FUNCTIONCALL_NODE) {
		return command((FunctionCallNode *) node);
	}
	if (type == OPERATION_NODE) {
		return command((OperationNode *) node);
	}
	if (type == POINTER_NODE) {
		return command((PointerNode *) node);
	}
	if (type == GETPOINTER_NODE) {
		return command((GetPointerNode *) node);
	}
	if (type == GETVAR_NODE) {
		return command((GetPointerNode *) node);
	}
	return {};
}

vector<Command *> command(CreateVarNode *node) {
	return {};
};

vector<Command *> command(DefParamNode *node) {
	return {};
};

vector<Command *> command(DefFuncNode *node) {
	return command(&node->block);
};

vector<Command *> command(DefStructNode *node) {
	return command(node->content);
};

vector<Command *> command(SetVarNode *node) {
	vector<Command *> result;
	append(result, command(node->expression));
	append(result, popVarCommand(node->name, node->getParentBlock()->getTable()));
	return result;
};

vector<Command *> command(SetPointerNode *node) {
	return {};
};

vector<Command *> command(IfNode *node) {
	return {};
};

vector<Command *> command(IfElseNode *node) {
	return {};
};

vector<Command *> command(WhileNode *node) {
	return {};
};

vector<Command *> command(ReturnNode *node) {
	return {};
};

vector<Command *> command(BreakNode *node) {
	return {};
};

vector<Command *> command(FloatNode *node) {
	return {};
};

vector<Command *> command(IntNode *node) {
	vector<Command *> result;
	append(result, rawCommand(REG_4, (unsigned int) node->value));
	append(result, getStackEndAdrCommand());
	append(result, storeCommand(REG_4, 4));
	return {};
};

vector<Command *> command(StringNode *node) {
	return {};
};

vector<Command *> command(FunctionCallNode *node) {
	return {};
};

vector<Command *> command(OperationNode *node) {
	return {};
}

vector<Command *> command(PointerNode *node) {
	return {};
};

vector<Command *> command(GetPointerNode *node) {
	return {};
};

vector<Command *> command(GetVarNode *node) {
	return {};
};
