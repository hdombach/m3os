#include "symbolTable.hpp"
#include "nodes/node.hpp"
#include <iostream>
#include <tuple>
#include <vector>
#include "error.hpp"
#include "util.hpp"

using namespace std;

SymbolTable::SymbolTable() {};

void SymbolTable::addFunctions(BlockNode *block) {
	vector<Node*> children = block->getNestedChildren(false);
	debug("size: " + to_string(children.size()) + ", " + to_string(block->getChildren().size()));
	for (int i = 0; i < children.size(); i++) {
		Node *child = children[i];
		if (child->type == DEFFUNC_NODE) {
			addFunction(*(DefFuncNode *) child);
		}
	}
}

void SymbolTable::addVars(BlockNode *block) {
	vector<Node*> children = block->getNestedChildren(false);
	debug("size: " + to_string(children.size()));
	for (int i = 0; i < children.size(); i++) {
		Node *child = children[i];
		if (child->type == CREATEVAR_NODE) {
			addVar(*(CreateVarNode *) child);
		}
	}
};


TypeNode *SymbolTable::getVarType(string name, bool throwError) {
	vector<TypeNode *> types = getTypes(name);
	if (throwError) {
		if (types.size() > 0) {
			logError("Too many symbols with name " + name);
		}
		if (types.empty()) {
			logError("No symbols of name " + name);
		}
	}
	return types[0];
}

TypeNode *SymbolTable::getFunctionReturnType(string name, vector<TypeNode *> params, bool throwError) {
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

	if (throwError) {
		if (filtered.size() > 1) {
			logError("more than one function of name " + name + " and params " + paramsString);
		}
		if (filtered.size() == 0) {
			logError("no function with name " + name + " and params " + paramsString);
		}
	}
	return filtered[0];
};

SymbolTable *SymbolTable::getRootTable() {
	if (isRootTable) {
		return NULL;
	} else if (SymbolTable::rootTable == NULL) {
		createRootTable();
	}
	return SymbolTable::rootTable;
}

SymbolTable *SymbolTable::getParent() {
	if (parent == NULL) {
		return getRootTable();
	} else {
		return parent;
	}
}

SymbolTable::operator string() {
	string result = "";
	string name;
	TypeNode *type;
	for (int i = 0; i < symbols.size(); i++) {
		tie(name, type) = symbols[i];	
		result += name + ": " + string(*type) + ",\n";
	};
	if (result.size() > 1) {
		result.pop_back();
		result.pop_back();
	}
	return "Symbol table:\n" + indentString(result) + "\n";
}

void SymbolTable::createRootTable() {
	SymbolTable::rootTable = new SymbolTable();
	SymbolTable::rootTable->addDefaults();
	SymbolTable::rootTable->isRootTable = true;
};

void SymbolTable::setParent(BlockNode *block) {
	Node *current = block;
	while (current->parent != NULL) {
		current = current->parent;
		if (current->type == BLOCK_NODE) {
			BlockNode *parentBlock = (BlockNode *) current;
			parent = parentBlock->getTable();
		}
	}
}

void SymbolTable::addDefaults() {
	addFunction("+", {"int", "int"}, "int");
	addFunction("-", {"int", "int"}, "int");
	addFunction("*", {"int", "int"}, "int");
	addFunction("/", {"int", "int"}, "int");
	addFunction("+", {"float", "float"}, "float");
	addFunction("-", {"float", "float"}, "float");
	addFunction("*", {"float", "float"}, "float");
	addFunction("/", {"float", "float"}, "float");
};

void SymbolTable::addVar(CreateVarNode node) {
	addVar(node.name, (VarTypeNode *) node.getVarType());
}

void SymbolTable::addVar(string name, TypeNode *type) {
	/*if (getVarType(name, false) != NULL) {
		logError("var with name " + name + " is already defined");
	}*/
	symbols.push_back(make_tuple(name, type));
}

void SymbolTable::addFunction(DefFuncNode node) {
	addFunction(node.name, node.getFuncType());
}

void SymbolTable::addFunction(string name, TypeNode *func) {
	/*auto trueFunc = (FunctionTypeNode *) func;
	if (getFunctionReturnType(name, trueFunc->params, false) != NULL) {
		logError("function with name " + name + " already defined");
	}*/
	symbols.push_back(make_tuple(name, func));
};

void SymbolTable::addFunction(string name, vector<string> paramTypes, string resultType) {
	FunctionTypeNode *type = new FunctionTypeNode();
	for (int i = 0; i < paramTypes.size(); i++) {
		string param = paramTypes[i];
		type->params.push_back(new VarTypeNode(param));
	}
	type->returnType = new VarTypeNode(resultType);
	addFunction(name, type);
};

vector<TypeNode *> SymbolTable::getTypes(string name) {
	vector<TypeNode *> result;

	debug("m1");
	debug("m1.1 " + to_string(symbols.size()));
	for (int i = 0; symbols.size() > i; i++) {
		if (get<0>(symbols[i]) == name) {
			result.push_back(get<1>(symbols[i]));
		}
	}
	debug("m2");
	if (getParent() != nullptr) {
		auto parentResult = getParent()->getTypes(name);
		result.insert(result.end(), parentResult.begin(), parentResult.end());
	}
	return result;
};

vector<SymbolTable*> createAllTables(Node *root) {
	auto blocks = root->getNestedBlocks();
	vector<SymbolTable*> result;
	for (int i = 0; i < blocks.size(); i++) {
		auto block = blocks[i];
		auto table = new SymbolTable();
		result.push_back(table);
		block->setTable(table);
		table->addFunctions(block);
	}
	for (int i = 0; i < blocks.size(); i++) {
		auto block = blocks[i];
		block->getTable()->addVars(block);
	}
	return result;
}
