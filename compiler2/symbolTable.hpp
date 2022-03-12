#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include "nodes/node.hpp"
#include <vector>
#include <tuple>
#include <string>

using namespace std;

class SymbolTable {
public:
	SymbolTable *parent;
	vector<tuple<string, TypeNode>> symbols;

	SymbolTable();

	void addFunctions(BlockNode *block);
	void addVars(BlockNode *block);

	TypeNode *getVarType(string name);
	TypeNode *getFunctionReturnType(string name, vector<TypeNode> params);

	private:
	void addVar(CreateVarNode node);
	void addFunction(DefFuncNode node);
};

#endif
