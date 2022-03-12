#include "node.h"
#include "token.h"
#include "../shared/util.h"
#include <string.h>
#include "../shared/error.h"

char *nodeTypeString(enum NodeType n) {
	switch (n) {
		case 0:
			return "PAGE";
		case 1:
			return "BLOCK";
		case 2:
			return "STATEMENT";
		case 3:
			return "EXPRESSION";
		case 4:
			return "CREATEVAR";
		case 5:
			return "DEFFUNC";
		case 6:
			return "SETVAR";
		case 7:
			return "SETPOINTER";
		case 8:
			return "IF";
		case 9:
			return "IFELSE";
		case 10:
			return "WHILE";
		case 11:
			return "RETURN";
		case 12:
			return "BREAK";
		case 13:
			return "FLOAT";
		case 14:
			return "INT";
		case 15:
			return "STRING";
		case 16:
			return "FUNCTIONCALL";
		case 17:
			return "OPERATION";
		case 18:
			return "POINTER";
		case 19:
			return "DEFPARAMS";
		case 20:
			return "DEFPARAM";
		case 21:
			return "RETURNS";
		case 22:
			return "GETVAR_NODE";
		case 23:
			return "VARTYPE_NODE";
		default:
			return "ERROR_NODE";
	}
}

char *nodeString(struct Node n, int indent) {
	struct Darray result = createDarray(sizeof(char), 16);
	int c = 0;
	while (indent > c) {
		appendString(&result, "| ");
		c++;
	}
	appendString(&result, nodeTypeString(n.type));
	//println("text: %s, pointer: %p", n.content, n.content);
	int test = strlen(n.content);
	if (strlen(n.content) > 0) {
		appendString(&result, ": ");
		appendString(&result, n.content);
	}
	appendString(&result, "\n");
	c = 0;
	while (n.children.size > c) {
		struct Node child = *(struct Node *)get(n.children, c);
		appendString(&result, nodeString(child, indent + 1));
		c++;
	}
	return result.data;
}

struct Node createNode() {
	struct Node result;
	result.children = createDarray(sizeof(struct Node), 16);
	result.content = "";
	result.tokenSize = 0;
	result.type = 1000;
	return result;
}

void addParents(struct Node *n) {
	struct Node *child;
	int c = 0;
	while (c < n->children.size) {
		child = (struct Node *)get(n->children, c);
		child->parent = n;
		addParents(child);
		c++;
	}
}


struct Node pageNode(struct Token *t) {
	struct Node result = createNode();

	result.type = PAGE_NODE;

	struct Node child = blockNode(t);
	push(&result.children, &child);
	result.tokenSize = child.tokenSize;

	return result;
}

struct Node blockNode(struct Token *t) {
	struct Node result = createNode();
	int c = 0;

	result.type = BLOCK_NODE;
	
	while (1) {
		struct Node child = statementNode(t + c);
		if (child.tokenSize > 0) {
			push(&result.children, &child);
			c += child.tokenSize;
		} else {
			break;
		}
	}
	result.tokenSize = c;

	return result;
}

struct Node statementNode(struct Token *t) {
	struct Node result = createNode();

	result = setVarNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = defFuncNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = createVarNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = ifElseNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = ifNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = whileNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = returnNode(t);
	if (result.tokenSize > 0) {
		return result;
	}
	
	result = breakNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = setPointerNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	return result;
}

//a private function tha gets the importance of a operation
int getImportance(struct Node n) {
	if (n.type != OPERATION_NODE) {
		return 1000;
	}

	println("testing operation: %s", n.content);

	if (strcmp(n.content, "+")) {
		return 4;
	} else if (strcmp(n.content, "-")) {
		return 4;
	} else if (strcmp(n.content, "*")) {
		return 3;
	} else if (strcmp(n.content, "/")) {
		return 3;
	} else if (strcmp(n.content, "%")) {
		return 3;
	} else if (strcmp(n.content, "==")) {
		return 7;
	} else if (strcmp(n.content, "!=")) {
		return 7;
	} else if (strcmp(n.content, "&&")) {
		return 11;
	} else if (strcmp(n.content, "||")) {
		return 12;
	} else if (strcmp(n.content, "!")) {
		return 2;
	}

	return 1000;
}

struct Node expressionNode(struct Token *t) {
	struct Node result = createNode();

	result = operationNode(t);
	if (result.tokenSize > 0) {
		//8 * 4 - 3
		//8 * (4 - 3)
		//(8 * 4) - 3

		struct Node secondChild = *(struct Node *)get(result.children, 1);

		println("boolean: %d > %d : %d", getImportance(result), getImportance(secondChild), getImportance(result) > getImportance(secondChild));
		if (getImportance(result) > getImportance(secondChild)) {
			logError("We made it here");
			struct Node secondFirst = *(struct Node *)get(secondChild.children, 0);
			struct Node temp = result;
			
			result = secondChild;
			set(&temp.children, 1, &secondFirst);
			set(&result.children, 0, &temp);
		}
		
		return result;
	}
	
	result = simpleExpressionNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	return result;
}

//expression exluding operations
struct Node simpleExpressionNode(struct Token *t) {
	struct Node result = createNode();
	int c = 0;

	//stuff for parameters
	if (t[c].type == OPENPARAN) {
		c++;
		result = expressionNode(t + c);
		if (result.tokenSize > 0) {
			c += result.tokenSize;
		} else {
			logError("Expected expression after '('");
			return result;
		}

		if (t[c].type == CLOSEPARAN) {
			c++;
		} else {
			logError("Epxected closing )");
			result.tokenSize = 0;
		}

		result.tokenSize = c;

		return result;
	}

	result = floatNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = intNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = stringNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = getVarNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	result = pointerNode(t);
	if (result.tokenSize > 0) {
		return result;
	}

	return result;
}

struct Node createVarNode(struct Token *t) {
	struct Node result = createNode();
	struct Node child;
	int c = 0;

	if (t[c].type == VAR) {
		c++;
	} else {
		return result;
	}

	if (t[c].type == LABEL) {
		result.content = t[c].content;
		c++;
	} else {
		logError("Expected label in variable decleration.");
		return result;
	}
	child = varTypeNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	}

	result.tokenSize = c;
	result.type = CREATEVAR_NODE;
	
	return result;
}

struct Node defFuncNode(struct Token *t) {
	struct Node result = createNode();
	struct Node child;
	int c = 0;

	if (t[c].type == FUNC) {
		c++;
	} else {
		return result;
	}

	if (t[c].type == LABEL) {
		result.content = t[c].content;
		c++;
	} else {
		logError("Expected label in function decleration.");
		return result;
	}

	child = defParamsNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	} else {
		logError("Expected paramater definition in function decleration.");
		return result;
	}

	child = returnsNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	}
	

	if (t[c].type == OPENCURLY) {
		c++;
	} else {
		logError("Expected opening curly in function decleration.");
		return result;
	}

	child = blockNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	}

	if (t[c].type == CLOSECURLY) {
		c++;
	} else {
		logError("Expected closing curly bracket in function delceration.");
		return result;
	}

	result.tokenSize = c;
	result.type = DEFFUNC_NODE;

	return result;
}

struct Node defParamsNode(struct Token *t) {
	struct Node result = createNode();
	int c = 0;

	if (t[c].type == OPENPARAN) {
		c++;
	} else {
		return result;
	}

	struct Node child = defParamNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;

		if (t[c].type == COLON) {
			c++;
		} else {
			logError("Expected : in paramater definition.");
			return result;
		}

		child = defParamNode(t + c);
		if (child.tokenSize > 0) {
			push(&result.children, &child);
			c += child.tokenSize;
		} else {
			logError("Expected type in paramter definition.");
			return result;
		}

		while (t[c].type == COMMA) {
			child = defParamNode(t + c);
			if (child.tokenSize > 0) {
				push(&result.children, &child);
				c += child.tokenSize;
			} else {
				logError("Epxecting variable name following comma in paramter definition.");
				return result;
			}

			if (t[c].type == COLON) {
				c++;
			} else {
				logError("Expecting : in paramter definition.");
				return result;
			}

			child = defParamNode(t + c);
			if (child.tokenSize > 0) {
				push(&result.children, &child);
				c += child.tokenSize;
			} else {
				logError("Expecting type in paramater definition.");
				return result;
			}
		}
	}

	if (t[c].type == CLOSEPARAN) {
		c++;
	} else {
		logError("Expecting closing paramter in paramter definition.");
		return result;
	}

	result.type = DEFPARAMS_NODE;
	result.tokenSize = c;
	
	return result;
}

struct Node defParamNode(struct Token *t) {
	struct Node result = createNode();
	
	if (t->type == LABEL) {
		result.content = t->content;
	} else {
		return result;
	}

	result.type = DEFPARAM_NODE;
	result.tokenSize = 1;

	return result;
}

struct Node setVarNode(struct Token *t) {
	struct Node result = createNode();
	struct Node child;
	
	int c = 0;
	if (t[c].type == LABEL) {
		result.content = t[c].content;
		c++;
	} else {
		return result;
	}

	if (t[c].type == EQUALS) {
		c++;
	} else {
		return result;
	}
	child = expressionNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	} else {
		logError("Expecting expression following = in set var.");
		return result;
	}
	result.type = SETVAR_NODE;
	result.tokenSize = c;
	return result;
}

struct Node setPointerNode(struct Token *t) {
	struct Node result = createNode();
	struct Node child;
	int c = 0;

	if (t[c].type == AT) {
		c++;
	} else {
		return result;
	}

	child = expressionNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	} else {
		logError("Expected expression in set pointer");
		return result;
	}

	if (t[c].type == EQUALS) {
		c++;
	} else {
		logError("Expected = after epxression in set pointer");
		return result;
	}

	child = expressionNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	} else {
		logError("Expected expression after = in set pointer.");
		return result;
	}

	result.type = SETPOINTER_NODE;
	result.tokenSize = c;

	return result;
}

struct Node ifNode(struct Token *t) {
	struct Node result = createNode();
	struct Node child;
	int c = 0;
	
	if (t[c].type == IF) {
		c++;
	} else {
		return result;
	}

	child = expressionNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	} else {
		logError("Expected expression after if");
		return result;
	}

	if (t[c].type == OPENCURLY) {
		c++;
	} else {
		logError("Expected opening curly after expression in if statement.");
		return result;
	}

	child = blockNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	}

	if (t[c].type == CLOSECURLY) {
		c++;
	} else {
		logError("Expected closing curly at end of if statement.");
		return result;
	}

	result.tokenSize = c;
	result.type = IF_NODE;

	return result;
}

struct Node ifElseNode(struct Token *t) {
	struct Node result = createNode();
	struct Node child;
	int c = 0;

	if (t[c].type == IF) {
		c++;
	} else {
		return result;
	}

	child = expressionNode(t + c);
	if (child.tokenSize > 0) {
	} else {
		logError("Epxected expression after if");
		return result;
	}

	if (t[c].type == OPENCURLY) {
		c++;
	} else {
		logError("Expected opening curly after expression in if else statemnt.");
		return result;
	}

	child = blockNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	}

	if (t[c].type == CLOSECURLY) {
		c++;
	} else {
		logError("Epxected closing culry af end of if statement.");
		return result;
	}

	if (t[c].type == ELSE) {
		c++;
	} else {
		return result;
	}
	if (t[c].type == OPENCURLY) {
		c++;
	} else {
		logError("Expected opening culry after else in if else statement.");
		return result;
	}

	child = blockNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	}


	if (t[c].type == CLOSECURLY) {
		c++;
	} else {
		logError("Expected closing curly at end of if else statement.");
		return result;
	}

	result.type = IFELSE_NODE;
	result.tokenSize = c;

	return result;
}

struct Node whileNode(struct Token *t) {
	struct Node result = createNode();
	struct Node child;
	int c = 0;

	if (t[c].type == WHILE) {
		c++;
	} else {
		return result;
	}

	child = expressionNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	} else {
		logError("Expected expression after while.");
		return result;
	}

	if (t[c].type == OPENCURLY) {
		c++;
	} else {
		logError("Epxected opening curly after expression in while statement.");
		return result;
	}

	child = blockNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	}

	if (t[c].type == CLOSECURLY) {
		c++;
	} else {
		logError("Expected closing culry at end of while statemnt.");
	}

	result.tokenSize = c;
	result.type = WHILE_NODE;

	return result;
}

struct Node returnNode(struct Token *t) {
	struct Node result = createNode();
	struct Node child;
	int c = 0;

	if (t[c].type == RETURN) {
		c++;
	} else {
		return result;
	}

	child = expressionNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	}

	result.tokenSize = c;
	result.type = RETURN_NODE;

	return result;
}

struct Node breakNode(struct Token *t) {
	struct Node result = createNode();

	if (t->type == BREAK) {
	} else {
		return result;
	}

	result.tokenSize = 1;
	result.type = BREAK_NODE;

	return result;
}

struct Node intNode(struct Token *t) {
	struct Node result = createNode();


	if (t->type == INT) {
		result.content = t->content;	
	} else {
		return result;
	}

	result.type = INT_NODE;
	result.tokenSize = 1;
	return result;
}

struct Node floatNode(struct Token *t) {
	struct Node result = createNode();
	struct Darray floatString = createDarray(sizeof(char), 16);
	int c = 0;

	if (t[c].type == INT) {
		appendString(&floatString, t[c].content);
		c++;
	} else {
		return result;
	}

	if (t[c].type == PERIOD) {
		appendString(&floatString, ".");
		c++;
	} else {
		return result;
	}

	if (t[c].type == INT) {
		appendString(&floatString, t[c].content);
		c++;
	} else {
		return result;
	}
	result.type = FLOAT_NODE;
	result.tokenSize = c;
	result.content = floatString.data;
	return result;
}

struct Node stringNode(struct Token *t) {
	struct Node result = createNode();

	if (t->type == STRING) {
		result.content = t->content;
	} else {
		return result;
	}

	result.type = STRING_NODE;
	result.tokenSize = 1;

	return result;
}

struct Node operationNode(struct Token *t) {
	struct Node result = createNode();
	int c = 0;
	struct Node child;

	child = simpleExpressionNode(t);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	} else {
		return result;
	}

	if (t[c].type == OPERAND) {
		result.content = t[c].content;
		c++;
	} else if (t[c].type == LABEL) {
		//TODO: make custom operations
		return result;
	} else {
		return result;
	}

	child = expressionNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	} else {
		return result;
	}

	result.tokenSize = c;
	result.type = OPERATION_NODE;
	return result;
}

struct Node pointerNode(struct Token *t) {
	struct Node result = createNode();
	struct Node child;
	int c = 0;

	if (t[c].type == AT) {
		c++;
	} else {
		return result;
	}

	child = expressionNode(t + c);
	if (child.tokenSize > 0) {
		push(&result.children, &child);
		c += child.tokenSize;
	} else {
		return result;
	}
	
	result.tokenSize = c;
	result.type = POINTER_NODE;

	return result;
}

struct Node returnsNode(struct Token *t) {
	struct Node result = createNode();
	int c = 0;
	
	if (t[c].type == RETURNS) {
		c++;
	} else {
		return result;
	}

	if (t[c].type == LABEL) {
		result.content = t[c].content;
		c++;
	} else {
		logError("Expecting type after returns token.");
		return result;
	}

	result.tokenSize = c;
	result.type = RETURNS_NODE;

	return result;
}

struct Node getVarNode(struct Token *t) {
	struct Node result = createNode();

	if (t->type == LABEL) {
		result.content = t->content;
	} else {
		return result;
	}

	result.tokenSize = 1;
	result.type = GETVAR_NODE;
	
	return result;
}

struct Node varTypeNode(struct Token *t) {
	struct Node result = createNode();
	int c = 0;
	if (t[c].type == COLON) {
		c++;
	} else {
		return result;
	}
	println("string thingy: %s", t[c].content);
	if (t[c].type == LABEL) {
		result.content = t[c].content;
		c++;
	} else {
		logError("Expected label in var type node");
		return result;
	}
	result.tokenSize = c;
	result.type = VARTYPE_NODE;

	return result;
}
