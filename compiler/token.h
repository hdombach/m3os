#ifndef TOKEN_H
#define TOKEN_H

#include "../shared/darray.h"

enum TokenType {
	INT,
	STRING,
	LABEL,
	OPERAND,
	OPENPARAN,
	CLOSEPARAN,
	OPENCURLY,
	CLOSECURLY,
	VAR,
	FUNC,
	COMMA,
	EQUALS,
	PERIOD,
	IF,
	ELSE,
	RETURN,
	BREAK,
	WHILE,
	LOOP,
	UNTIL,
	END,
	COLON,
	RETURNS,
	AT,
	AND,
};

struct Token {
	enum TokenType type;
	char *content;
	int position;
};

struct Darray tokenize(char *data);


char *tokenString(struct Token t);
char *tokenTypeString(enum TokenType t);

int createToken(char *s, struct Token *t);

int createInt(char *s, struct Token *t);
int createString(char *s, struct Token *t);
int createLabel(char *s, struct Token *t);
int createOperand(char *s, struct Token *t);
int createOpenParan(char *s, struct Token *t);
int createCloseParan(char *s, struct Token *t);
int createOpenCurly(char *s, struct Token *t);
int createCloseCurly(char *s, struct Token *t);
int createVar(char *s, struct Token *t);
int createFunc(char *s, struct Token *t);
int createComma(char *s, struct Token *t);
int createEquals(char *s, struct Token *t);
int createPeriod(char *s, struct Token *t);
int createIf(char *s, struct Token *t);
int createElse(char *s, struct Token *t);
int createReturn(char *s, struct Token *t);
int createBreak(char *s, struct Token *t);
int createWhile(char *s, struct Token *t);
int createLoop(char *s, struct Token *t);
int createUntil(char *s, struct Token *t);
struct Token createEnd();
int createColon(char *s, struct Token *t);
int createReturns(char *s, struct Token *t);
int createAt(char *s, struct Token *t);
int createAnd(char *s, struct Token *t);


#endif
