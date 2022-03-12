#include "tests.h"
#include "../shared/test.h"
#include "../shared/util.h"
#include "arg.h"
#include <string.h>
#include "token.h"
#include "node.h"

struct TestResult testingSystem() {
	struct TestResult result;
	result.name = "Testing system";
	result.passed = 1;
	return result;
};

struct TestResult arguments() {
	struct TestResult r;
	r.name = "Arguments";
	r.passed = 0;

	char * args[1];
	args[0] = "testFile.h";
	struct Arguments arg = getArg(1, args);
	
	if (strcmp("testFile.h", arg.sourceFile) != 0) {
		r.msg = "source file is not \"testFile.h\"";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingIntToken() {
	struct TestResult r;
	r.name = "Creating int token";
	r.passed = 0;

	struct Token t;
	int i = createInt("132 gdkj baag", &t);
	if (i != 3) {
		r.msg = "i is not 3";
		return r;
	}
	if (t.type != INT) {
		r.msg = "type of token is not int";
		return r;
	}
	if (strcmp(t.content, "132") != 0) {
		r.msg = "content of toke is not 132";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingStringToken() {
	struct TestResult r;
	r.name = "Creating string token";
	r.passed = 0;

	struct Token t;
	int i = createToken("\"thing\"215", &t);
	if (i != 7) {
		r.msg = "i is not 7";
		return r;
	}
	if (t.type != STRING) {
		r.msg = "type of token is not string";
		return r;
	}
	if (strcmp(t.content, "thing") != 0) {
		r.msg = "content of token is not thing";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingLabelToken() {
	struct TestResult r;
	r.name = "Creating label token";
	r.passed = 0;

	struct Token t;
	int i = createToken("thing(5)", &t);
	if (i != 5) {
		r.msg = "i is not 5";
		return r;
	}
	if (t.type != LABEL) {
		r.msg = "type of token is not label";
		return r;
	}
	if (strcmp(t.content, "thing") != 0) {
		r.msg = "content of token is not thing";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingOperantToken() {
	struct TestResult r;
	r.name = "Creating operant token";
	r.passed = 0;

	struct Token t;
	int i = createToken("*(5)", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != OPERAND) {
		r.msg = "type of token is not operand";
		return r;
	}
	if (strcmp(t.content, "*") != 0) {
		r.msg = "content of token is not *";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingOpenParanToken() {
	struct TestResult r;
	r.name = "Creating open paran token";
	r.passed = 0;

	struct Token t;
	int i = createToken("(6)", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != OPENPARAN) {
		r.msg = "type of toke is not open paran";
		return r;
	}
	
	r.passed = 1;
	return r;
}

struct TestResult creatingCloseParanToken() {
	struct TestResult r;
	r.name = "Creating close paran token";
	r.passed = 0;

	struct Token t;
	int i = createToken(")63 dkj23", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != CLOSEPARAN) {
		r.msg = "type of token is not close paran";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingOpenCurlyToken() {
	struct TestResult r;
	r.name = "Creating open curly token";
	r.passed = 0;

	struct Token t;
	int i = createToken("{ if thing}", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != OPENCURLY) {
		r.msg = "type of token is not open curly";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingCloseCurlyToken() {
	struct TestResult r;
	r.name = "Creating close curly token";
	r.passed = 0;

	struct Token t;
	int i = createToken("}fd", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != CLOSECURLY) {
		r.msg = "type of token is not close curly";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingVarToken() {
	struct TestResult r;
	r.name = "Creating var token";
	r.passed = 0;

	struct Token t;
	int i = createToken("var thing", &t);
	if (i != 3) {
		r.msg = "i is not 3";
		return r;
	}
	if (t.type != VAR) {
		r.msg = "type of token is not var";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingFuncToken() {
	struct TestResult r;
	r.name = "Creating func token";
	r.passed = 0;

	struct Token t;
	int i = createToken("func thing", &t);
	if (i != 4) {
		r.msg = "i is not 4";
		return r;
	}
	if (t.type != FUNC) {
		r.msg = "type of token is not func";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingCommaToken() {
	struct TestResult r;
	r.name = "Creating comma token";
	r.passed = 0;

	struct Token t;
	int i = createToken(",hellow", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != COMMA) {
		r.msg = "type of token is not command";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingEqualsToken() {
	struct TestResult r;
	r.name = "Creating equals token";
	r.passed = 0;

	struct Token t;
	int i = createToken("= 5", &t);
	if (i != 1) {
		r.msg = "is is not 1";
		return r;
	}
	if (t.type != EQUALS) {
		r.msg = "type of token is not equals";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingPeriodToken() {
	struct TestResult r;
	r.name = "Creating period token";
	r.passed = 0;

	struct Token t;
	int i = createToken(".5", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != PERIOD) {
		r.msg = "type of token is not period";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingIfToken() {
	struct TestResult r;
	r.name = "creating if token";
	r.passed = 0;

	struct Token t;
	int i = createToken("if(5 < 3)", &t);
	if (i != 2) {
		r.msg = "i is not 2";
		return r;
	}
	if (t.type != IF) {
		r.msg = "type of token is not if";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingElseToken() {
	struct TestResult r;
	r.name = "creating else token";
	r.passed = 0;

	struct Token t;
	int i = createToken("else{", &t);
	if (i != 4) {
		r.msg = "i is not 4";
		return r;
	}
	if (t.type != ELSE) {
		r.msg = "type of token is not else";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingReturnToken() {
	struct TestResult r;
	r.name = "creating return token";
	r.passed = 0;
	
	struct Token t;
	int i = createToken("return 5", &t);
	if (i != 6) {
		r.msg = "i is not 6";
		return r;
	} 
	if (t.type != RETURN) {
		r.msg = "type of token is not return";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingBreakToken() {
	struct TestResult r;
	r.name = "creating break token";
	r.passed = 0;

	struct Token t;
	int i = createToken("break }", &t);
	if (i != 5) {
		r.msg = "i is not 5";
		return r;
	}
	if (t.type != BREAK) {
		r.msg = "type of token is not break";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingWhileToken() {
	struct TestResult r;
	r.name = "creating while token";
	r.passed = 0;

	struct Token t;
	int i = createToken("while 5 < 4", &t);
	if (i != 5) {
		r.msg = "i is not 5";
		return r;
	}
	if (t.type != WHILE) {
		r.msg = "type of token is not while";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingLoopToken() {
	struct TestResult r;
	r.name = "creating loop token";
	r.passed = 0;
	
	struct Token t;
	int i = createToken("loop {", &t);
	if (i != 4) {
		r.msg = "i is not 4";
		return r;
	}
	if (t.type != LOOP) {
		r.msg = "type of token is not loop";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingUntilToken() {
	struct TestResult r;
	r.name = "creating until token";
	r.passed = 0;

	struct Token t;
	int i = createToken("until 5 < 3", &t);
	if (i != 5) {
		r.msg = "i is not 5";
		return r;
	}
	if (t.type != UNTIL) {
		r.msg = "type of token is not until";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingEndToken() {
	struct TestResult r;
	r.name = "creating end token";
	r.passed = 0;

	struct Token t = createEnd();

	if (t.type != END) {
		r.msg = "type of token is not end";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingColonToken() {
	struct TestResult r;
	r.name = "creating colon token";
	r.passed = 0;

	struct Token t;
	int i = createToken(":fd", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != COLON) {
		r.msg = "type of token is not colon";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingReturnsToken() {
	struct TestResult r;
	r.name = "creating returns token";
	r.passed = 0;

	struct Token t;
	int i = createToken("-> int", &t);
	if (i != 2) {
		r.msg = "i is not 2";
		return r;
	}
	if (t.type != RETURNS) {
		r.msg = "type of token is not returns";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingAtToken() {
	struct TestResult r;
	r.name = "creating at token";
	r.passed = 0;

	struct Token t;
	int i = createToken("@(5 - 3)", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != AT) {
		r.msg = "type of token is not at";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingAndToken() {
	struct TestResult r;
	r.name = "creating and token";
	r.passed = 0;

	struct Token t;
	int i = createToken("& 5", &t);
	if (i != 1) {
		r.msg = "i is not 1";
		return r;
	}
	if (t.type != AND) {
		r.msg = "type of token is not and";
		return r;
	}
	
	r.passed = 1;
	return r;
}

struct TestResult creatingPageNode() {
	struct TestResult r;
	r.name = "creating page node";
	r.passed = 0;

	struct Darray tokens = tokenize("var thing = 5");
	struct Node n = pageNode(tokens.data);

	if (n.type != PAGE_NODE) {
		r.msg = "type is not page_node";
		return r;
	}
	if (n.children.size != 1) {
		r.msg = "size of children is not 1";
		return r;
	}
	struct Node child = *(struct Node *)get(n.children, 0);
	if (child.type != BLOCK_NODE) {
		r.msg = "type of child is not block_node";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingBlockNode() {
	struct TestResult r;
	r.name = "creating block node";
	r.passed = 0;

	struct Darray tokens = tokenize("var thing = 5");
	struct Node n = blockNode(tokens.data);

	if (n.type != BLOCK_NODE) {
		r.msg = "type is not block_node";
		return r;
	}
	if (n.children.size != 1) {
		r.msg = "size of children is not 1";
		return r;
	}
	struct Node child = *(struct Node *)get(n.children, 0);
	if (child.type != CREATEVAR_NODE) {
		r.msg = "type of child is not setvar_noe";
		return r;
	}

	r.passed = 1;
	return r;
}

struct TestResult creatingCreateVarNode() {
	struct TestResult r;
	r.name = "creating create var node";
	r.passed = 0;

	struct Darray tokens = tokenize("var thing = 5");
	struct Node n = statementNode(tokens.data);

	if (n.tokenSize != CREATEVAR_NODE) {
		r.msg = "type is not createvar_node";
		return r;
	}
	if (n.children.size != 1) {
		r.msg = "size of children is not 1";
		return r;
	}

	struct Node child = *(struct Node *)get(n.children, 0);
	if (child.tokenSize != INT_NODE) {
		r.msg = "type of child is not int_node";
		return r;
	}
	if (strcmp(child.content, "5") != 0) {
		r.msg = "content of child is not 5";
		return r;
	}

	r.passed = 1;
	return r;
}

void addCompilerTests() {
	initTests();

	addUtilTests();

	addTest(testingSystem());
	addTest(arguments());

	addTest(creatingIntToken());
	addTest(creatingStringToken());
	addTest(creatingLabelToken());
	addTest(creatingOperantToken());
	addTest(creatingOpenParanToken());
	addTest(creatingCloseParanToken());
	addTest(creatingOpenCurlyToken());
	addTest(creatingCloseCurlyToken());
	addTest(creatingVarToken());
	addTest(creatingFuncToken());
	addTest(creatingCommaToken());
	addTest(creatingEqualsToken());
	addTest(creatingPeriodToken());
	addTest(creatingIfToken());
	addTest(creatingElseToken());
	addTest(creatingReturnToken());
	addTest(creatingBreakToken());
	addTest(creatingWhileToken());
	addTest(creatingLoopToken());
	addTest(creatingUntilToken());
	addTest(creatingEndToken());
	addTest(creatingColonToken());
	addTest(creatingReturnsToken());
	addTest(creatingAtToken());
	addTest(creatingAndToken());

	addTest(creatingPageNode());
	addTest(creatingBlockNode());
	addTest(creatingCreateVarNode());

	printTestResults();
}
