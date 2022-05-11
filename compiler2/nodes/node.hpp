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
	DEFSTRUCT_NODE,
	DEFCHAR_NODE,
	DEFSHORT_NODE,
	DEFINT_NODE,
	DEFLONG_NODE,
	DEFFLOAT_NODE,
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
class Command;

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
	 * @note This should not be called. Instead, create a node from one of the inherited classes such as PageNode
	 */
	Node(Token *tokens);

	/**
	 * Create an empty node.
	 * @note should note be used. Instead, create a node from one of the inherited classes such as Pagenode
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

	//vector<Token> getOffset(Token *tokens, int offset);
	BlockNode *getParentBlock();
};

/**
 * A type that exists in a certain scope.
 */
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
	*	@note should not be called. Instead, use StatementNode::create(Token *tokens);
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

/**
	* Contains all statements for a particular scope
	*/
class BlockNode: public Node {
	public:
	/**
	*	The statements taht are in teh scope
	*/
	vector<StatementNode *> statements;

	vector<Command *> createdCommands;

	/**
	*	Creates a block node from a list of tokens
	*	@param tokens The array of tokens to create the block from
	*/
	BlockNode(Token *tokens);
	/**
	*	Creates an empty block node.
	*	@note should use BlockNode(Token *tokens) instead.
	*/
	BlockNode();

	/**
	 *	Creates a block node from the provided data
	 *	@param statements The 
	 */
	BlockNode(vector<StatementNode *> statements);

	operator string() const;

	/**
	*	Gets any children nodes.
	*/
	virtual vector<Node*> getChildren();

	/**
	*	Gets the symbol table that contains all symboles for this scope
	*/
	SymbolTable *getTable();

	/**
	* Sets the table. Should only be called once.
	*/
	void setTable(SymbolTable *table);

private:
	SymbolTable *table;
};

/**
 *	Represents the code in a files
 */
class PageNode: public Node {
	public:
	BlockNode block;

	/**
	* Creates a page node from a list of tokens
	* @param tokens The array of tokens to create the page from.
	*/
	PageNode(Token *tokens);
	
	/**
	*	Creats an empty page node.
	*	@note should use PageNode(Token *tokens) instead.
	*/
	PageNode();

	operator string() const;

	/**
	*	Gets any children nodes.
	*/
	virtual vector<Node*> getChildren();
};

/**
	*Represents code that evaluates to a value.
	*/
class ExpressionNode: public StatementNode {
	public:

	/**
	*	Creates an empty expression node.
	*	Node should use create(Token *tokens, bool includeOperation) instead
	*/
	ExpressionNode();

	/**
	* Create a subclase of ExpressionNode from the tokens
	* @param tokens The array of tokesn to create a node from.
	*/
	static ExpressionNode *create(Token *tokens, bool includeOperation = true);

	virtual operator string() const;

	/**
	*	Get the type of the value the expression evaluates to.
	*/
	virtual TypeNode *getResultType();

	/**
	*	Gets the children of this node.
	*/
	virtual vector<Node*> getChildren();

	/**
	 *	Returns whether a type is an expression or not
	 */
	static bool isChild(NodeType type);
};

/**
	* A node when you define a var.
	*/
class CreateVarNode: public StatementNode {
	public:

	/**
	*	The name of the declared variable
	*/
	string name;

	/**
	*	The type declared for the variable.
	*/
	TypeNode *valueType;

	/**
	* The expression for the initial value
	*/
	ExpressionNode *expression;

	/**
	*	Creates a create var node from the list of tokens
	*	@param tokens The array of tokens to create the page from.
	*/
	CreateVarNode(Token *tokens);

	/**
	*	Creates an empty CreateVarNode
	*	@note should use CreateVarNode(Token *tokens)
	*/
	CreateVarNode();

	virtual operator string() const;

	/**
	*	Gets the type of the declared variable.
	*/
	TypeNode *getVarType();

	/**
	* Gets any children nodes.
	*/
	virtual vector<Node*> getChildren();
};


/**
	* The definition for a param in teh function decleration
	*/
class DefParamNode: public Node {
	public:
	
	/**
	*	The name of the paramater
	*/
	string name;
	
	/**
	* The type of the paramater
	*/
	TypeNode *varType;

	/**
	*	Creates a DefParam node from the list of tokens
	*	@param tokens The array of tokens to creaet the DefParam from.
	*/
	DefParamNode(Token *tokens);

	/**
	* Creates an empty Defparam node
	* @note should use DefParam(Token *tokens) instead.
	*/
	DefParamNode();

	virtual operator string() const;

	/**
	*	Gets any children nodes.
	*/
	virtual vector<Node*> getChildren();
};

/**
	*	The type for a value
	*/
class VarTypeNode: public TypeNode {
	public:

	/**
	*	The name of the type
	*/
	string name;

	/**
	*	Creates a VarType node from a list of tokens
	*/
	VarTypeNode(Token *tokens);

	/**
	*	Creates an empty VarType node.
	*	@note should use VarTypeNode(Token *tokens) or VarTypeNode(string name) instead
	*/
	VarTypeNode();

	/**
	*	Creates a VarType node for a name
	*/
	VarTypeNode(string name);

	virtual operator string() const;

	/**
	* Gets any children nodes
	*/
	virtual vector<Node*> getChildren();

	virtual bool operator == (const VarTypeNode &b);
};

/**
	* Represents a template data type
	* will look like type<innerTypes>
	*/
class TemplateTypeNode: public VarTypeNode {
	public:

	/**
	*	The template types
	*/
	vector<TypeNode*> types;
	
	/**
	*	Creates a TemplateType node from a list of tokens
	*	@param tokens The list of tokens
	*/
	TemplateTypeNode(Token *tokens);

	/**
	*	Creates an empty TemplateType node.
	*	@note should use TemplateTypeNode(Token *tokens) or TemplateTypeNode(string name, vector<TypeNode*> types) instead.
	*/
	TemplateTypeNode();

	/**
	* Creates a Template type node from the provided info
	* @param name The name of the enclosing type
	* @param types The list of inner types
	*/
	TemplateTypeNode(string name, vector<TypeNode*> types);

	virtual operator string() const;

	/**
	*	Returns any children
	*/
	virtual vector<Node*> getChildren();

	virtual bool operator == (const TemplateTypeNode &b);
};

/**
	*	The type that represents a function
	*	Format lookes like (params) => type
	*/
class FunctionTypeNode: public TypeNode {
	public:
	/**
	*	The types for the params
	*/
	vector<TypeNode*> params;

	/**
	* The type for the return value
	*/
	TypeNode *returnType;

	/**
	 * A marker that denotes whether this function should be handeled as an operator
	 * Operators are handeled differently in that they can be accessed from the parent scope.
	 * (They are self contained funciton that exist alonside a struct and not in a struct)
	 */
	bool isOperator = false;

	/**
	*	Creates a FunctionType node from a list of tokens
	*	@param tokens The list of tokens
	*/
	FunctionTypeNode(Token *tokens);

	/**
	* Creates an empty FunctionType node
	* @note should use FunctionTypeNode(Token *tokens) or FunctionTypeNode(vector<TypeNode*> paramTypes, TypeNode *returnType) instead
	*/
	FunctionTypeNode();

	/**
	*	Creates a FunctionType node from the provided info
	*	@param paramTypes The types of the param
	*	@param returnType The expected return type
	*/
	FunctionTypeNode(vector<TypeNode*> paramTypes, TypeNode *returnType);

	virtual operator string() const;

	/**
	*	Returns ansy children
	*/
	virtual vector<Node*> getChildren();

	virtual bool operator == (const FunctionTypeNode &b);
};

/**
	*	The type that represents a tempate functions
	*	Format looks like (params)<temlate> => type
	*/
class TemplateFunctionTypeNode: public FunctionTypeNode {
	public:

	/**
	* The types for the templates
	*/
	vector<TypeNode*> templateParams;

	/**
	* Creaes a FunctionType node from a list of tokens
	* @param tokens The list of tokens
	*/
	TemplateFunctionTypeNode(Token *tokens);
	
	/**
	*	Creates an empty TemplateFunctionType node
	*	@note should use FunctionTypeNode(Token *tokens) or TemplateFunctionTypeNode(vector<TypeNode*> paramTypes, vector<TypeNode*> templateParams, TypeNode *returnType) instead.
	*/
	TemplateFunctionTypeNode();
	/**
	*	Creates a TemplateFunctionType node from the prodid info
	*	@param paramTypes the types of the params
	*	@param templateParams the types for the template
	*	@param returnType The expected return type
	*/
	TemplateFunctionTypeNode(vector<TypeNode*> paramTypes, vector<TypeNode*> templateParams, TypeNode *returnType);

	virtual operator string() const;

	/**
	* Returns any children
	*/
	virtual vector<Node*> getChildren();

	virtual bool operator == (const TemplateFunctionTypeNode &b);
};

/**
	*	A function that representes a function definition
	*/
class DefFuncNode: public StatementNode {
	public:
	/**
	*	The name of the function
	*/
	string name;
	/**
	*	The list of param definitions
	*/
	vector<DefParamNode> params;
	/**
	*	The provided return type
	*	Can be null
	*/
	VarTypeNode *returnType;
	/**
	*	The contents of the definition
	*/
	BlockNode block;
	/**
	*	Whether this function should be handleded as an operatos.
	*	Operations are handeled slightly different from normal functions as they need to be exposed the the root scope
	*/
	bool isOperator = false;

	/**
	*	Creates a DefFunc node from a list of tokens
	*	@param tokens The list of tokens
	*/
	DefFuncNode(Token *tokens);
	/**
	*	Creates and empty DefFunc node
	*	@note should use DefFuncNode(Token *tokens) instead
	*/
	DefFuncNode();

	virtual operator string() const;

	/**
	*	Gets the function type that describes this function
	*/
	TypeNode *getFuncType();

	/**
	* Returns any children
	*/
	virtual vector<Node*> getChildren();
};

/**
	*	A function that represents a struct Definition
	*/
class DefStructNode: public StatementNode {
public:
	/**
	*	The name of the struct
	*/
	string name;
	/**
	*	The ocntents of the struct
	*/
	BlockNode *content;

	/**
	*	Creates a DefStruct node from a list of tokens
	*	@params tokens The list of tokens
	*/
	DefStructNode(Token *tokens);
	/**
	*	Creates an empty DefSTruct node.
	*	@note should use one of the other constructors
	*/
	DefStructNode();
	/**
	*	Creates a DefStruct node with the provided info
	*	@param name The provided name
	*	@param content The provided block
	*/
	DefStructNode(string name, BlockNode *content);
	/**
	*	Creates a DefSTruct node with the provided info
	*	@param name The provded name
	*	@param definitions The statemetns with which to create the content
	*/
	DefStructNode(string name, vector<StatementNode*> definitions);

	virtual operator string() const;

	/**
	*	Gets any children
	*/
	virtual vector<Node*> getChildren();

	/**
	*	Gets the bytes required by this struct
	*/
	virtual int getAllocatedSize();
};

/**
	*	A function that represents a set var operation
	*/
class SetVarNode: public StatementNode {
	public:
	/**
	*	The name of the var to set
	*/
	string name;
	/**
	* The expression to set the var to.
	*/
	ExpressionNode *expression;

	/**
	* Creates a SetVar node from a list of tokens
	* @param tokens The list of tokens
	*/
	SetVarNode(Token *tokens);
	/**
	* Creates an empty SetVar node
	* @note Should use SetVarNode(Token *tokens)
	*/
	SetVarNode();

	operator string() const;

	virtual vector<Node*> getChildren();
};

/**
	*	A function that represents setting an pointer.
	*/
class SetPointerNode: public StatementNode {
	public:

	/**
	*	The expression for the pointer
	*/
	ExpressionNode *pointerExpression;
	/**
	*	The expression for the value
	*/
	ExpressionNode *expression;

	/**
	*	Creates a setPointer node from a list of tokens
	*	@param tokens The list of tokens
	*/
	SetPointerNode(Token *tokens);
	/**
	*	Creates an empty SetPointer node
	*	@note should use SetPointerNode(Token *token)
	*/
	SetPointerNode();

	operator string() const;

	/**
	*	Returns any children
	*/
	virtual vector<Node*> getChildren();
};

class IfNode: public StatementNode {
	public:

	/**
	*	The boolean expression
	*/
	ExpressionNode *expression;
	
	/**
	*	The value to read if the expression is true
	*/
	BlockNode block;

	/**
	* Creates an if node from a list of tokens
	* @param tokens The list of tokens
	*/
	IfNode(Token *tokens);

	/**
	*	Creates an empty if node
	*	@note should use IfNode(Token *token) in most cases
	*/
	IfNode();

	operator string() const;

	/**
	*
	*/
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

	float getValue();
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
