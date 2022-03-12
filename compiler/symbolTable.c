#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "../shared/darray.h"
#include "../shared/util.h"

struct SymbolTable createEmptyTable(struct Node blockNode) {
	struct SymbolTable result;

	result.children = createDarray(sizeof(struct SymbolTable), 4);
	result.tokens = createDarray(sizeof(struct Symbol), 4);

	if (blockNode.type == BLOCK_NODE) {
		result.blockNode = blockNode;
	}

	return result;
}

void recursive(struct Node n, struct SymbolTable *t) {
	

	int c = 0;
	struct Node child;
	while (n.children.size > c) {
		child = *(struct Node*)get(n.children, c);


		if (child.type == CREATEVAR_NODE) {
			struct Symbol s;
			s.type = VAR_SYMBOL;
			s.content = malloc(strlen(child.content));
			strcpy(s.content, child.content);
			push(&t->tokens, &s);
			s = *(struct Symbol*)get(t->tokens, t->tokens.size - 1);
		}

		if (child.type == DEFFUNC_NODE) {
			struct Symbol s;
			s.type = FUNC_SYMBOL;
			s.content = malloc(strlen(child.content));
			strcpy(s.content, child.content);
			push(&t->tokens, &s);
		}

		if (child.type == BLOCK_NODE) {
			struct SymbolTable new = createEmptyTable(child);
			recursive(child, &new);
			push(&t->children, &new);
		} else {
			recursive(child, t);
		}
		c++;
	}
}

struct SymbolTable createTable(struct Node n) {
	struct SymbolTable result = createEmptyTable(n);
	recursive(n, &result);
	return result;
};

char *symbolString(struct Symbol s) {
	struct Darray result = createDarray(sizeof(char), 16);
	if (s.type == VAR_SYMBOL) {
		appendString(&result, "Var Symbol: ");
		appendString(&result, s.content);
		appendString(&result, "\n");
	}
	if (s.type == FUNC_SYMBOL) {
		appendString(&result, "Function Symbol: ");
		appendString(&result, s.content);
		appendString(&result, "\n");
	}
	if (s.type == TYPE_SYMBOL) {
		appendString(&result, "Type Symbol: ");
		appendString(&result, s.content);
		appendString(&result, "\n");
	}

	return result.data;
}

char *_symbolTableString(struct SymbolTable s, int indent) {
	struct Darray result = createDarray(sizeof(char), 16);
	
	int c = 0;
	int lineC = 0;

	while (indent - 1 > lineC) {
		appendString(&result, "| ");
		lineC++;
	}
	appendString(&result, "Table:\n");

	while (s.tokens.size > c) {
		lineC = 0;
		while (indent > lineC) {
			appendString(&result, "| ");
			lineC++;
		}
		struct Symbol symbol = *(struct Symbol *)get(s.tokens, c);
		appendString(&result, symbolString(symbol));
		c++;
	}

	c = 0;
	while (s.children.size > c) {
		struct SymbolTable childTable;
		childTable = *(struct SymbolTable *)get(s.children, c);
		appendString(&result, _symbolTableString(childTable, indent + 1));
		c++;
	}

	return result.data;
}

char *symbolTableString(struct SymbolTable s) {
	return _symbolTableString(s, 1);
}
