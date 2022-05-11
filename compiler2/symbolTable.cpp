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

void SymbolTable::addDefinitions(BlockNode *block) {
	vector<Node*> children = block->getNestedChildren(false);
	for (int i = 0; i < children.size(); i++) {
		Node *child = children[i];
		if (child->type == DEFFUNC_NODE && child->type == DEFSTRUCT_NODE) {
			definitions.push_back(child);
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

DefFuncNode *SymbolTable::getFunctionDefinition(string name, vector<TypeNode*> params) {
	for (int i = 0; i < definitions.size(); i++) {
		Node *definition = definitions[i];
		if (definition->type == DEFFUNC_NODE) {
			DefFuncNode *funcDefinition = (DefFuncNode *) definition;
			if (funcDefinition->name == name ) {
				bool passed = true;
				for (int j = 0; j < funcDefinition->params.size(); j++) {
					if (funcDefinition->params[j].type != params[j]->type) {
						passed = false;
					}
				}
				if (passed) {
					return funcDefinition;
				}
			}
		}
	}
	if (getParent() != nullptr) {
		return getParent()->getFunctionDefinition(name, params);
	}
	return NULL;
};

DefStructNode *SymbolTable::getStructDefinition(string name) {
	for (int i = 0; i < definitions.size(); i++) {
		Node *definition = definitions[i];
		if (definition->type == DEFSTRUCT_NODE) {
			DefStructNode *structDefinition = (DefStructNode *) definition;
			if (structDefinition->name == name) {
				return structDefinition;
			}
		}
	}
	if (getParent() != nullptr) {
		return getParent()->getStructDefinition(name);
	}
	return NULL;
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

bool SymbolTable::isRoot() {
	return isRootTable;
};

int SymbolTable::getAllocatedSize(string name) {
	auto tempType = getVarType(name);
	if (tempType->type == VARTYPE_NODE || TEMPLATETYPE_NODE) {
		auto varType = (VarTypeNode *) tempType;
		return getStructDefinition(varType->name)->getAllocatedSize();
	} else {
		return getStructDefinition("function")->getAllocatedSize();
	}
};

int SymbolTable::getAllocatedSize(string name, vector<TypeNode *> params) {
	return getStructDefinition("funciton")->getAllocatedSize();
};

int SymbolTable::getTotalAllocatedSize() {
	int result = 0;
	for (int i = 0; i < symbols.size(); i++) {
		TypeNode *symbol = get<1>(symbols[i]);
		if (symbol->type == VARTYPE_NODE || symbol->type == TEMPLATETYPE_NODE) {
			DefStructNode *defStruct = getStructDefinition(get<0>(symbols[i]));
			result += defStruct->getAllocatedSize();
		} else {
			result += getStructDefinition("function")->getAllocatedSize();
		}
	};
	return result;
};

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

int SymbolTable::getMemoryOffset(string name) {
	int result = 0;
	string tempName;
	TypeNode *tempType;
	for (int i = 0; i < symbols.size(); i++) {
		tie(tempName, tempType) = symbols[i];
		if (tempType->type == VARTYPE_NODE || tempType->type == TEMPLATETYPE_NODE) {
			auto tempVarType = (VarTypeNode *) tempType;
			if (tempVarType->name == name) {
				return result;
			};
			result += getStructDefinition(tempVarType->name)->getAllocatedSize();
		} else {
			if (tempName == name) {
				return result;
			}
			result += getStructDefinition("function")->getAllocatedSize();
		};
	};
	return -1;
};

int SymbolTable::getMemoryOffset(string name, vector<TypeNode*> params) {
	int result = 0;
	string tempName;
	TypeNode *tempType;
	for (int i = 0; i < symbols.size(); i++) {
		tie(tempName, tempType) = symbols[i];
		if (tempType->tokenSize == FUNCTIONTYPE_NODE || tempType->tokenSize == TEMPLATEFUNCTIONTYPE_NODE) {
			auto tempFunctionType = (FunctionTypeNode *) tempType;
			if (tempName == name && tempFunctionType->params == params) {
				return result;
			}
			result += getStructDefinition("function")->getAllocatedSize();
		} else {
			auto tempVarType = (VarTypeNode *) tempType;
			result += getStructDefinition(tempVarType->name)->getAllocatedSize();
		};
	};
	return -1;
};

int SymbolTable::getPrevFrameMemoryOffset() {
	int result = 0;
	string tempName;
	TypeNode *tempType;
	for (int i = 0; i < symbols.size(); i++) {
		tie(tempName, tempType) = symbols[i];
		if (tempType->type == VARTYPE_NODE || tempType->type == TEMPLATETYPE_NODE) {
			auto tempVarType = (VarTypeNode *) tempType;
			result += getStructDefinition(tempVarType->name)->getAllocatedSize();
		} else {
			result += getStructDefinition("function")->getAllocatedSize();
		}
	};
	return result;
};

int SymbolTable::getReturnOffset() {
	return getPrevFrameMemoryOffset() + 2;
};

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

	for (int i = 0; symbols.size() > i; i++) {
		if (get<0>(symbols[i]) == name) {
			result.push_back(get<1>(symbols[i]));
		}
	}
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
	for (int i = 0; i < blocks.size(); i++) {
		auto block = blocks[i];
		block->getTable()->addVars(block);
	}
	return result;
}
