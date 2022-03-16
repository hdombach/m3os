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

	TypeNode *getVarType(string name, bool throwError = true);
	TypeNode *getFunctionReturnType(string name, vector<TypeNode*> params, bool throwError = true);
	SymbolTable *getRootTable();
	SymbolTable *getParent();

	operator string();


	private:
	vector<tuple<string, TypeNode*>> symbols;
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
