#ifndef NODE_HPP
#define NODE_HPP

#include "../token.hpp"
#include <vector>
#include <string>

using namespace std;

enum NodeType {
	PAGE_NODE,
	BLOCK_NODE,
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
	GETPOINTER_NODE,
	DEFPARAM_NODE,
	GETVAR_NODE,
	VARTYPE_NODE,
	TEMPLATETYPE_NODE,
	FUNCTIONTYPE_NODE,
	TEMPLATEFUNCTIONTYPE_NODE,
	ERROR_NODE,
};

class BlockNode;

/**
	*	A generic node for the syntax tree.
	*/
class Node {
public:

	/**
	* The type for node.
	*/
	NodeType type;

	/**
	*	Description: Where the corresponding text is in the file.
	*/
	TokenPosition position;

	/**
	*	The number of tokens used to define the node.
	*/
	int tokenSize;

	/**
	 * Create a node from a list of tokens
	 * @param tokens The list to generate the node from.
	 * Note: This should not be called. Instead, create a node from one of the inherited classes such as PageNode
	 */
	Node(Token *tokens);

	/**
	 * Create an empty node.
	 * Note: should note be used. Instead, create a node from one of the inherited classes such as Pagenode
	 */
	Node();

	virtual operator string() const;

	/**
	* Gets any children nodes.
	*/
	virtual vector<Node*> getChildren();

	/**
	*	Recursively gets all nodes that are under this node
	*	@param includeChildScope Whether to get the children of blocks which have there own scope.
	*/
	virtual vector<Node*> getNestedChildren(bool includeChildScope=true);

	/**
	*	Recursively get all blocks that are children of this node
	*/
	virtual vector<BlockNode*> getNestedBlocks();

	/**
	*	The parent node
	*/
	Node *parent;
	//void runFunc(void (*func)(Node *node), bool includeChildScope=true);

protected:
	//vector<Token> getOffset(Token *tokens, int offset);
	BlockNode *getParentBlock();
};

class TypeNode: public Node {
	public:
	/**
	*	Creates an empty TypeNode
	*	note: Should not be called. Instead, use create(Token *tokens)
	*/
	TypeNode();

	/**
	*	Create a subclass of TypeNode from the tokens.
	* @param tokens The array of tokens to create the node from
	*/
	static TypeNode *create(Token *tokens);

	/**
	*	Gets the children of this node.
	*/
	virtual vector<Node*> getChildren();

	virtual bool operator == (const TypeNode& b);
};


class StatementNode: public Node {
	public:
	/**
	*	Creates an empty statement node
	*	Note: should not be called. Instead, use StatementNode::create(Token *tokens);
	*/
	StatementNode();

	/**
	*	Creates a subclass of StatementNode from the tokens.
	*	@param tokens The array of tokens to create the node from
	*	@return One of the subsclasses of StatementNode
	*/
	static StatementNode *create(Token *tokens);

	virtual operator string() const;
};

//foward declare the symbol table
class SymbolTable;

class BlockNode: public Node {
	public:
	vector<StatementNode *> statements;

	BlockNode(Token *tokens);
	BlockNode();

	operator string() const;

	virtual vector<Node*> getChildren();

	SymbolTable *getTable();
	void setTable(SymbolTable *table);

private:
	SymbolTable *table;
};

class PageNode: public Node {
	public:
	BlockNode block;

	PageNode(Token *tokens);
	PageNode();

	operator string() const;

	virtual vector<Node*> getChildren();
};

class ExpressionNode: public StatementNode {
	public:
	ExpressionNode();

	static ExpressionNode *create(Token *tokens, bool includeOperation = true);

	virtual operator string() const;

	virtual TypeNode *getResultType();

	virtual vector<Node*> getChildren();
};


class CreateVarNode: public StatementNode {
	public:
	string name;
	TypeNode *valueType;
	ExpressionNode *expression;

	CreateVarNode(Token *tokens);
	CreateVarNode();

	virtual operator string() const;

	TypeNode *getVarType();

	virtual vector<Node*> getChildren();
};


class DefParamNode: public Node {
	public:
	string name;
	TypeNode *varType;

	DefParamNode(Token *tokens);
	DefParamNode();

	virtual operator string() const;

	virtual vector<Node*> getChildren();
};

class VarTypeNode: public TypeNode {
	public:
	string name;

	VarTypeNode(Token *tokens);
	VarTypeNode();
	VarTypeNode(string name);

	virtual operator string() const;

	virtual vector<Node*> getChildren();

	virtual bool operator == (const VarTypeNode &b);
};

//type<inerTypes>
class TemplateTypeNode: public VarTypeNode {
	public:
	vector<TypeNode*> types;
	
	TemplateTypeNode(Token *tokens);
	TemplateTypeNode();
	TemplateTypeNode(string name, vector<TypeNode*> types);

	virtual operator string() const;

	virtual vector<Node*> getChildren();

	virtual bool operator == (const TemplateTypeNode &b);
};

//() -> ()
class FunctionTypeNode: public TypeNode {
	public:
	vector<TypeNode*> params;
	TypeNode *returnType;

	FunctionTypeNode(Token *tokens);
	FunctionTypeNode();
	FunctionTypeNode(vector<TypeNode*> paramTypes, TypeNode *returnType);

	virtual operator string() const;

	virtual vector<Node*> getChildren();

	virtual bool operator == (const FunctionTypeNode &b);
};

//()<> -> ()
class TemplateFunctionTypeNode: public FunctionTypeNode {
	public:

	vector<TypeNode*> templateParams;

	TemplateFunctionTypeNode(Token *tokens);
	TemplateFunctionTypeNode();
	TemplateFunctionTypeNode(vector<TypeNode*> paramTypes, vector<TypeNode*> templateParams, TypeNode *returnType);

	virtual operator string() const;

	virtual vector<Node*> getChildren();

	virtual bool operator == (const TemplateFunctionTypeNode &b);
};
	

class DefFuncNode: public StatementNode {
	public:
	string name;
	vector<DefParamNode> params;
	VarTypeNode *returnType;
	BlockNode block;

	DefFuncNode(Token *tokens);
	DefFuncNode();

	virtual operator string() const;

	TypeNode *getFuncType();

	virtual vector<Node*> getChildren();
};

class SetVarNode: public StatementNode {
	public:
	string name;
	ExpressionNode *expression;

	SetVarNode(Token *tokens);
	SetVarNode();

	operator string() const;

	virtual vector<Node*> getChildren();
};

class SetPointerNode: public StatementNode {
	public:
	ExpressionNode *pointerExpression;
	ExpressionNode *expression;

	SetPointerNode(Token *tokens);
	SetPointerNode();

	operator string() const;

	virtual vector<Node*> getChildren();
};

class IfNode: public StatementNode {
	public:
	ExpressionNode *expression;
	BlockNode block;

	IfNode(Token *tokens);
	IfNode();

	operator string() const;

	virtual vector<Node*> getChildren();
};

class IfElseNode: public StatementNode {
	public:
	ExpressionNode *expression;
	BlockNode trueBlock;
	BlockNode falseBlock;

	IfElseNode(Token *tokens);
	IfElseNode();

	operator string() const;

	virtual vector<Node*> getChildren();
};

class WhileNode: public StatementNode {
	public:
	ExpressionNode *expression;
	BlockNode block;

	WhileNode(Token *tokens);
	WhileNode();

	operator string() const;
	
	virtual vector<Node*> getChildren();
};

class ReturnNode: public StatementNode {
	public:
	ExpressionNode *expression;

	ReturnNode(Token *tokens);
	ReturnNode();

	operator string() const;

	virtual vector<Node*> getChildren();
};

class BreakNode: public StatementNode {
	public:
	BreakNode(Token *tokens);
	BreakNode();

	operator string() const;

	virtual vector<Node*>getChildren();
};

class FloatNode: public ExpressionNode {
	public:
	float value;

	FloatNode(Token *tokens);
	FloatNode();

	operator string() const;

	virtual vector<Node*> getChildren();

	virtual TypeNode *getResultType();
};

class IntNode: public ExpressionNode {
	public:
	int value;

	IntNode(Token *tokens);
	IntNode();

	operator string() const;

	virtual vector<Node*> getChildren();

	virtual TypeNode *getResultType();
};

class StringNode: public ExpressionNode {
	public:
	string value;

	StringNode(Token *tokens);
	StringNode();

	operator string() const;

	virtual vector<Node*> getChildren();

	virtual TypeNode *getResultType();
};

class FunctionCallNode: public ExpressionNode {
	public:
	string name;
	vector<ExpressionNode *> expressions;

	FunctionCallNode(Token *tokens);
	FunctionCallNode();

	operator string() const;

	virtual vector<Node*> getChildren();

	virtual TypeNode *getResultType();
};

class OperationNode: public ExpressionNode {
	public:
	string operation;
	ExpressionNode *leftExpression;
	ExpressionNode *rightExpression;

	OperationNode(Token *tokens);
	OperationNode();

	operator string() const;

	virtual vector<Node*> getChildren();

	virtual TypeNode *getResultType();
};

class PointerNode: public ExpressionNode {
	public:
	ExpressionNode *expression;

	PointerNode(Token *tokens);
	PointerNode();

	operator string() const;

	virtual vector<Node*> getChildren();

	virtual TypeNode *getResultType();
};

class GetPointerNode: public ExpressionNode {
	public:
	ExpressionNode *expression;

	GetPointerNode(Token *tokens);
	GetPointerNode();

	operator string() const;

	virtual vector<Node*> getChildren();

	virtual TypeNode *getResultType();
};

class GetVarNode: public ExpressionNode {
	public:
	string name;

	GetVarNode(Token *tokens);
	GetVarNode();

	operator string() const;

	virtual vector<Node*> getChildren();

	virtual TypeNode *getResultType();
};

string nodeTypeString(NodeType t);

#endif
