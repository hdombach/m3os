#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include "../shared/darray.h"
#include "node.h"

enum SymbolType {
	FUNC_SYMBOL,
	VAR_SYMBOL,
	TYPE_SYMBOL
};

struct Symbol {
	struct Node node;
	int evaluatedSize; //used when var or func
	struct Symbol *evaluatedType; //used when var or func
	enum SymbolType type;
	char *content;
	struct Darray inherited; //used when type
};

struct SymbolTable {
	struct SymbolTable *parent;
	struct Darray tokens;
	struct Darray children;
	struct Node blockNode;
};

struct SymbolTable createTable(struct Node n);
char *symbolString(struct Symbol s);
char *symbolTableString(struct SymbolTable s);


#endif
