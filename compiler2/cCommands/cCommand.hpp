#ifndef CCOMAND_HPP
#define CCOMAND_HPP

#include "../nodes/node.hpp"

string ccommand(StatementNode *node);
string ccommand(BlockNode *node);
string ccommand(PageNode *node);
string ccommand(ExpressionNode *node);
string ccommand(CreateVarNode *node);
string ccommand(DefParamNode *node);
string ccommand(DefFuncNode *node);
string ccommand(DefStructNode *node);
string ccommand(SetVarNode *node);
string ccommand(SetPointerNode *node);
string ccommand(IfNode *node);
string ccommand(IfElseNode *node);
string ccommand(WhileNode *node);
string ccommand(ReturnNode *node);
string ccommand(BreakNode *node);
string ccommand(FloatNode *node);
string ccommand(IntNode *node);
string ccommand(StringNode *node);
string ccommand(FunctionCallNode *node);
string ccommand(OperationNode *node);
string ccommand(PointerNode *node);
string ccommand(GetPointerNode *node);
string ccommand(GetVarNode *node);

#endif
