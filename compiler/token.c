#include "token.h"
#include "../shared/darray.h"
#include "../shared/util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *numerics = "0123456789";
char *specials = "{}().,\"\'=@*/+-|&!%:><";
char *whitespaces = " \n\t";

char *tokenTypeString(enum TokenType t) {
	switch (t) {
		case 0:
			return "INT";
		case 1:
			return "STRING";
		case 2:
			return "LABEL";
		case 3:
			return "OPERAND";
		case 4:
			return "OPENPARAN";
		case 5:
			return "CLOSEPARAN";
		case 6:
			return "OPENCURLY";
		case 7:
			return "CLOSECURLY";
		case 8:
			return "VAR";
		case 9:
			return "FUNC";
		case 10:
			return "COMMA";
		case 11:
			return "EQUALS";
		case 12:
			return "PERIOD";
		case 13:
			return "IF";
		case 14:
			return "ELSE";
		case 15:
			return "RETURN";
		case 16:
			return "BREAK";
		case 17:
			return "WHILE";
		case 18:
			return "LOOP";
		case 19:
			return "UNTIL";
		case 20:
			return "END";
		case 21:
			return "COLON";
		case 22:
			return "RETURNS";
		case 23:
			return "AT";
		case 24:
			return "AND";
		default:
			return "ERROR";
	}
}
char *tokenString(struct Token t) {
	struct Darray result = createDarray(sizeof(char), 16);
	
	char posStr[10];
	sprintf(posStr, "%d ", t.position);
	appendString(&result, posStr);

	appendString(&result, tokenTypeString(t.type));
	appendString(&result, ": ");
	appendString(&result, t.content);

	appendString(&result, "\n");
	return result.data;
}

struct Darray tokenize(char *data) {
	struct Darray result = createDarray(sizeof(struct Token), 16);
	char *currentPointer = data;
	int currentLine = 1;
	struct Token currentToken;
	while (1) {
		int offset = createToken(currentPointer, &currentToken);
		if (offset > 0) {
			currentToken.position =currentLine;
			push(&result, &currentToken);

			int c = 0;
			while (offset > c) {
				currentPointer++;
				if (*currentPointer == '\n') {
					currentLine ++;
				}
				c++;
			}
		} else {
			break;
		}
	}
	currentToken = createEnd();
	currentToken.position = currentLine;
	push(&result, &currentToken);
	return result;
}

int createToken(char *s, struct Token *t) {
	int result;
	int c = 0;
	while (strchr(whitespaces, *s) != NULL) {
		if (s[c] == '\0') {
			return 0;
		} else {
			c++;
			s++;
		}
	}

	t->content = "";

	result = createString(s, t);
	if (result > 0) {
		return result + c; 
	}

	result = createReturns(s, t);
	if (result > 0)  {
		return result + c;
	}

	result = createOperand(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createOpenParan(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createCloseParan(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createOpenCurly(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createCloseCurly(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createEquals(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createComma(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createPeriod(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createColon(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createAt(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createAnd(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createVar(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createFunc(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createIf(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createElse(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createReturn(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createBreak(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createWhile(s, t);
	if (result > 0) {
		return result + c;
	}
	
	result = createLoop(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createUntil(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createInt(s, t);
	if (result > 0) {
		return result + c;
	}

	result = createLabel(s, t);
	if (result > 0) {
		return result + c;
	}

	


	printf("Token could not be created. Text left to be tokenized: %s\n", s);
	exit(-1);
	
	return 0;
}

int createInt(char *s, struct Token *t) {
	int c = 0;
	struct Darray content = createDarray(sizeof(char), 16);

	t->type = INT;
	while (strchr(numerics, s[c]) != NULL && s[c] != '\0') {
		push(&content, &s[c]);
		c++;
	}
	t->content = content.data;
	return c;
}

int createString(char *s, struct Token *t) {
	int c = 0;
	int isBackslash = 0;

	if (s[c] != '"') {
		return 0;
	}

	struct Darray content = createDarray(sizeof(char), 16);
	c++;

	t->type = STRING;
	
	while (1) {
		char current = s[c];
		if (isBackslash == 0 && current == '"') {
			c++;
			break;
		}
		push(&content, &current);
		if (current == '\0') {
			return 0;
		}
		if (isBackslash == 0) {
			if (current == '\\') {
				isBackslash = 1;
			}
		} else {
			isBackslash = 0;
		}
		c++;
	}

	t->content = content.data;

	return c;
}

int createLabel(char *s, struct Token *t) {
	struct Darray content = createDarray(sizeof(char), 16);
	int c = 0;

	t->type = LABEL;
	while (1) {
		char current = s[c];
		if (strchr(specials, current) != NULL || strchr(whitespaces, current) != NULL) {
			break;
		}
		push(&content, &current);
		c++;
	}
	
	t->content = content.data;
	return c;
}

int createOperand(char *s, struct Token *t) {
	t->type = OPERAND;
	if (strcstr(s, "&&")) {
		t->content = "&&";
		return 2;
	}
	if (strcstr(s, "==")) {
		t->content = "==";
		return 2;
	}
	if (strcstr(s, "!=")) {
		t->content = "!=";
		return 2;
	}
	if (strcstr(s, "||")) {
		t->content = "||";
		return 2;
	}
	if (strcstr(s, "*")) {
		t-> content = "*";
		return 1;
	}
	if (strcstr(s, "+")) {
		t->content = "+";
		return 1;
	}
	if (strcstr(s, "/")) {
		t->content = "/";
		return 1;
	}
	if (strcstr(s, "-")) {
		t->content = "-";
		return 1;
	}
	if (strcstr(s, ">")) {
		t->content = ">";
		return 1;
	}
	if (strcstr(s, "<")) {
		t->content = "<";
		return 1;
	}
	return 0;
}

int createOpenParan(char *s, struct Token *t) {
	if (strcstr(s, "(")) {
		t->type = OPENPARAN;
		return 1;
	} else {
		return 0;
	}
}

int createCloseParan(char *s, struct Token *t) {
	if (strcstr(s, ")")) {
		t->type = CLOSEPARAN;
		return 1;
	} else {
		return 0;
	}
}

int createOpenCurly(char *s, struct Token *t) {
	if (strcstr(s, "{")) {
		t->type = OPENCURLY;
		return 1;
	} else {
		return 0;
	}
}

int createCloseCurly(char *s, struct Token *t) {
	if (strcstr(s, "}")) {
		t->type = CLOSECURLY;
		return 1;
	} else {
		return 0;
	}
}

int createVar(char *s, struct Token *t) {
	int result = createLabel(s, t);
	if (strcmp(t->content, "var") == 0) {
		t->type = VAR;
		t->content = "";
		return result;
	}
	return 0;
}

int createEquals(char *s, struct Token *t) {
	if (strcstr(s, "=")) {
		t->type = EQUALS;
		return 1;
	} else {
		return 0;
	}
}

int createFunc(char *s, struct Token *t) {
	int result = createLabel(s, t);
	if (strcmp(t->content, "func") == 0) {
		t->type = FUNC;
		t->content = "";
		return result;
	}
	return 0;
}

int createComma(char *s, struct Token *t) {
	if (strcstr(s, ",")) {
		t->type = COMMA;
		return 1;
	} else {
		return 0;
	}
}

int createPeriod(char *s, struct Token *t) {
	if (strcstr(s, ".")) {
		t->type = PERIOD;
		return 1;
	} else {
		return 0;
	}
}

int createIf(char *s, struct Token *t) {
	int result = createLabel(s, t);
	if (strcmp(t->content, "if") == 0) {
		t->type = IF;
		t->content = "";
		return result;
	}
	return 0;
}

int createElse(char *s, struct Token *t) {
	int result = createLabel(s, t);
	if (strcmp(t->content, "else") == 0) {
		t->type = ELSE;
		t->content = "";
		return result;
	}
	return 0;
}

int createReturn(char *s, struct Token *t) {
	int result = createLabel(s, t);
	if (strcmp(t->content, "return") == 0) {
		t->type = RETURN;
		t->content = "";
		return result;
	}
	return 0;
}

int createBreak(char *s, struct Token *t) {
	int result = createLabel(s, t);
	if (strcmp(t->content, "break") == 0) {
		t->type = BREAK;
		t->content = "";
		return result;
	}
	return 0;
}

int createWhile(char *s, struct Token *t) {
	int result = createLabel(s, t);
	if (strcmp(t->content, "while") == 0) {
		t->type = WHILE;
		t->content = "";
		return result;
	}
	return 0;
}

int createLoop(char *s, struct Token *t) {
	int result = createLabel(s, t);
	if (strcmp(t->content, "loop") == 0) {
		t->type = LOOP;
		t->content = "";
		return result;
	}
	return 0;
}

int createUntil(char *s, struct Token *t) {
	int result = createLabel(s, t);
	if (strcmp(t->content, "until") == 0) {
		t->type = UNTIL;
		t->content = "";
		return result;
	}
	return 0;
}

struct Token createEnd() {
	struct Token result;
	result.type = END;
	result.content = "";
	return result;
}

int createColon(char *s, struct Token *t) {
	if (strcstr(s, ":")) {
		t->type = COLON;
		return 1;
	} else {
		return 0;
	}
}

int createReturns(char *s, struct Token *t) {
	if (strcstr(s, "->")) {
		t->type = RETURNS;
		return 2;
	} else {
		return 0;
	}
}

int createAt(char *s, struct Token *t) {
	if (strcstr(s, "@")) {
		t->type = AT;
		return 1;
	} else {
		return 0;
	}
}

int createAnd(char *s, struct Token *t) {
	if (strcstr(s, "&")) {
		t->type = AND;
		return 1;
	} else {
		return 0;
	}
}
