#ifndef NODE_H
#define NODE_H

#include "../shared/darray.h"
#include "token.h"

enum NodeType {
	PAGE_NODE,
	BLOCK_NODE,
	STATEMENT_NODE,
	EXPRESSION_NODE,
	CREATEVAR_NODE,
	DEFFUNC_NODE,
	SETVAR_NODE,
	SETPOINTER_NODE,
	IF_NODE,
	IFELSE_NODE,
	WHILE_NODE,
	RETURN_NODE,
	BREAK_NODE,
	FLOAT_NODE,
	INT_NODE,
	STRING_NODE,
	FUNCTIONCALL_NODE,
	OPERATION_NODE,
	POINTER_NODE,
	DEFPARAMS_NODE,
	DEFPARAM_NODE,
	RETURNS_NODE,
	GETVAR_NODE,
	VARTYPE_NODE,
};

struct Node {
	enum NodeType type;
	char *content;
	struct Darray children;
	int tokenSize;
	struct Node *parent;
};

char *nodeString(struct Node n, int indent);
char *nodeTypeString(enum NodeType n);

struct Node createNode();
void addParents(struct Node *n);

struct Node pageNode(struct Token *t);
struct Node blockNode(struct Token *t);
struct Node statementNode(struct Token *t);
struct Node expressionNode(struct Token *t);
struct Node simpleExpressionNode(struct Token *t); //expression exluding operations
struct Node createVarNode(struct Token *t);
struct Node defFuncNode(struct Token *t);
struct Node defParamsNode(struct Token *t);
struct Node defParamNode(struct Token *t);
struct Node returnsNode(struct Token *t);
struct Node setVarNode(struct Token *t);
struct Node setPointerNode(struct Token *t);
struct Node ifNode(struct Token *t);
struct Node ifElseNode(struct Token *t);
struct Node whileNode(struct Token *t);
struct Node returnNode(struct Token *t);
struct Node breakNode(struct Token *t);
struct Node floatNode(struct Token *t);
struct Node intNode(struct Token *t);
struct Node stringNode(struct Token *t);
struct Node functionCallNode(struct Token *t);
struct Node operationNode(struct Token *t);
struct Node pointerNode(struct Token *t);
struct Node returnsNode(struct Token *t);
struct Node getVarNode(struct Token *t);
struct Node varTypeNode(struct Token *t);
#endif
