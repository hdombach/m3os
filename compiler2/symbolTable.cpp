#include "symbolTable.hpp"
#include "nodes/node.hpp"
#include <iostream>
#include <vector>
#include "error.hpp"
#include "util.hpp"

using namespace std;

SymbolTable::SymbolTable() {};

void SymbolTable::addFunctions(BlockNode *block) {
	vector<Node*> children = block->getNestedChildren(false);
	for (int i = 0; i < children.size(); i++) {
		Node *child = children[i];
		if (child->type == DEFFUNC_NODE) {
			addFunction(*(DefFuncNode *) child);
		}
	}
}

void SymbolTable::addVars(BlockNode *block) {
	vector<Node*> children = block->getNestedChildren(false);
	for (int i = 0; i < children.size(); i++) {
		Node *child = children[i];
		if (child->type == CREATEVAR_NODE) {
			addVar(*(CreateVarNode *) child);
		}
	}
};

void SymbolTable::addVar(CreateVarNode node) {
	symbols.push_back(make_tuple(node.name, node.getVarType()));
}

void SymbolTable::addFunction(DefFuncNode node) {
	symbols.push_back(make_tuple(node.name, node.getFuncType()));
}

vector<TypeNode *> SymbolTable::getTypes(string name) {
	vector<TypeNode *> result;

	for (int i = 0; symbols.size() > i; i++) {
		if (get<0>(symbols[i]) == name) {
			result.push_back(get<1>(symbols[i]));
		}
	}
	return result;
};

TypeNode *SymbolTable::getVarType(string name) {
	vector<TypeNode *> types = getTypes(name);
	if (types.size() > 0) {
		logError("Too many symbols with name " + name);
	}
	if (types.empty()) {
		logError("No symbols of name " + name);
	}
	return types[0];
}

TypeNode *SymbolTable::getFunctionReturnType(string name, vector<TypeNode *> params) {
	vector<TypeNode *> types = getTypes(name);
	vector<FunctionTypeNode *> filtered;
	for (int i = 0; types.size() > i; i++) {
		TypeNode *type = types[i];
		if (type->type == FUNCTIONTYPE_NODE || type->type == TEMPLATEFUNCTIONTYPE_NODE) {
			FunctionTypeNode *functionType = (FunctionTypeNode *) type;
			if (functionType->params == params) {
				filtered.push_back(functionType);
			}
		}
	}

	string paramsString = "";
	for (int i = 0; i < params.size(); i++) {
		paramsString += string(*params[i]) + ",\n";
	}
	if (paramsString.size() > 2) {
		paramsString.pop_back();
		paramsString.pop_back();
	}
	paramsString = "{\n" + indentString(paramsString) + "\n}";

	if (filtered.size() > 1) {
		logError("more than one function of name " + name + " and params " + paramsString);
	}
	if (filtered.size() == 0) {
		logError("no function with name " + name + " and params " + paramsString);
	}
	return filtered[0];
};
