#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include "nodes/node.hpp"
#include <vector>
#include <tuple>
#include <string>

using namespace std;

class SymbolTable {
public:
	SymbolTable();

	void addFunctions(BlockNode *block);

	void addVars(BlockNode *block);

	void addDefinitions(BlockNode *block);

	TypeNode *getVarType(string name, bool throwError = true);
	TypeNode *getFunctionReturnType(string name, vector<TypeNode*> params, bool throwError = true);
	DefFuncNode *getFunctionDefinition(string name, vector<TypeNode*> params);
	DefStructNode *getStructDefinition(string name);
	SymbolTable *getRootTable();
	SymbolTable *getParent();

	int getAllocatedSize();

	operator string();

	/**
	* Gets the offset of the given var
	* @note returns -1 if the var is in a parent scope or does not exise
	*/
	int getMemoryOffset(string name); //(includes  functions)
	
	/**
	*	Gets the offset of the frame pointer
	*/
	int getPrevFrameMemoryOffset();

	/**
	*	Gets the offset of the return value
	*/
	int getReturnOffset();

	private:
	vector<tuple<string, TypeNode*>> symbols;
	vector<Node *> definitions;
	SymbolTable *parent;
	inline static SymbolTable *rootTable;
	static void createRootTable();
	bool isRootTable = false;
	void setParent(BlockNode *block);
	void addDefaults();
	void addVar(CreateVarNode node);
	void addVar(string name, TypeNode *type);
	void addFunction(DefFuncNode node);
	void addFunction(string name, TypeNode *func);
	void addFunction(string name, vector<string> paramTypes, string resultType);
	vector<TypeNode *> getTypes(string name);
};

vector<SymbolTable*> createAllTables(Node *root);

#endif
