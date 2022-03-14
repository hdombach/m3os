#include "node.hpp"
#include "../token.hpp"
#include "../error.hpp"
#include "../util.hpp"

GetPointerNode::GetPointerNode(Token *tokens): ExpressionNode() {
	int tempSize = 0;

	if (tokens->type == POINTER) {
		tempSize++;
		tokens++;
	} else {
		return;
	}

	expression = ExpressionNode::create(tokens);
	if (expression->tokenSize > 0) {
		tempSize += expression->tokenSize;
		tokens += expression->tokenSize;
	} else {
		logTokenError(*tokens, "expected expression");
		return;
	}

	expression->parent = this;

	tokenSize = tempSize;
	type = GETPOINTER_NODE;
};

GetPointerNode::operator string() const {
	string result = "";
	result += string(*expression);
	return "Get Pointer {\n" + indentString(result) + "\n}";
};

vector<Node*> GetPointerNode::getChildren() {
	vector<Node*> result;

	result.push_back(expression);

	return result;
};

TypeNode *GetPointerNode::getResultType() {
	TypeNode *expressionType = expression->getResultType();
	TemplateTypeNode *result = new TemplateTypeNode();
	result->name = "pointer";
	result->types.push_back(expressionType);

	return result;
};
