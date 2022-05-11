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

	/**
	 *	Adds the function defintions in the provided block
	 */
	void addFunctions(BlockNode *block);

	/**
	 *	Adds the var definitions in the provided block
	 */
	void addVars(BlockNode *block);

	/**
	 *	Adds the struct definitions in the provided block
	 */
	void addDefinitions(BlockNode *block);

	TypeNode *getVarType(string name, bool throwError = true);
	TypeNode *getFunctionReturnType(string name, vector<TypeNode*> params, bool throwError = true);
	DefFuncNode *getFunctionDefinition(string name, vector<TypeNode*> params);
	DefStructNode *getStructDefinition(string name);
	SymbolTable *getRootTable();
	SymbolTable *getParent();

	bool isRoot();

	int getAllocatedSize(string name);
	int getAllocatedSize(string name, vector<TypeNode *> params);

	int getTotalAllocatedSize();

	operator string();

	/**
	* Gets the offset of the given var
	* @note returns -1 if the var is in a parent scope or does not exise
	*/
	int getMemoryOffset(string name); //(includes  functions)

	int getMemoryOffset(string name, vector<TypeNode*> params);
	
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
