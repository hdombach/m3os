#include "token.hpp"
#include <cstdlib>
#include <string>
#include <map>
#include <array>
#include "util.hpp"
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

string numerics = "0123456789";
string specials = "{}().,\"\'=@*/+-|&!%:><";
string whitespaces = " \n\t";

Token::Token(std::string data) {
	*this = Token();

	int c = 0;
	while (stringContains(whitespaces, data.at(c))) {
		c++;
		if (c >= data.length()) {
			return;
		}
	}

	*this = createString(data.substr(c));
	if (this->charOffset > 0) {
		this->charOffset += c;
		return;
	}

	*this = createInt(data.substr(c));
	if (this->charOffset > 0) {
		this->charOffset += c;
		return;
	}

	*this = createOperand(data.substr(c));
	if (this->charOffset > 0) {
		this->charOffset += c;
		return;
	}

	*this = createSpecial(data.substr(c));
	if (this->charOffset > 0) {
		this->charOffset += c;
		return;
	}

	*this = createLabel(data.substr(c));
	if (this->charOffset > 0) {
		this->charOffset += c;
		return;
	}
}

Token::operator string() const {
	string result;

	result += "(";
	result += to_string(position.line);
	result += ",";
	result += to_string(position.column);
	result += ")";

	result += ": ";
	result += tokenTypeString(type);
	if (!content.empty()) {
		result += ", (";
		result += content;
		result += ")";
	}

	return result;
};

Token Token::createEnd() {
	Token result;

	result.type = END;

	return result;
}

Token::Token() {
	content = "";
	position.column = 0;
	position.line = 0;
	charOffset = 0;
	type = ERROR;
}

Token Token::createInt(string s) {
	Token result = Token();

	int c = 0;
	while (stringContains(numerics, s[c])) {
		result.content += s[c];
		c++;
	}

	result.type = INT;
	result.charOffset = c;
	return result;
}

Token Token::createString(string s) {
	Token result = Token();

	int c = 0;
	bool isBackslash = false;

	if (s[c] != '"') {
		return result;
	}

	c++;

	while (true) {
		char current = s[c];
		if (!isBackslash && current == '"') {
			c++;
			break;
		}
		result.content += current;
		if (current == '\0') {
			return result;
		}
		if (isBackslash) {
			isBackslash = false;
		} else {
			if (current == '\\') {
				isBackslash = true;
			}
		}
		c++;
	}

	result.charOffset = c;
	result.type = STRING;

	return result;
}

Token Token::createLabel(string s) {
	Token result = Token();

	int length = s.length();
	int c = 0;
	while (true) {
		if (c >= length) {
			return result;
		}
		char current = s[c];
		if (stringContains(specials, current) || stringContains(whitespaces, current)) {
			break;
		}
		result.content += current;
		c++;
	}

	map<string, TokenType> m;
	m["var"] = VAR;
	m["func"] = FUNC;
	m["if"] = IF;
	m["else"] = ELSE;
	m["return"] = RETURN;
	m["break"] = BREAK;
	m["while"] = WHILE;
	m["loop"] = LOOP;
	m["and"] = AND;
	m["or"] = OR;

	result.type = LABEL;

	for (map<string, TokenType>::iterator i = m.begin(); i != m.end(); ++i) {
		if (i->first == result.content) {
			result.type = i->second;
			result.content = "";
			break;
		}
	}

	result.charOffset = c;

	return result;
}

Token Token::createOperand(string s) {
	Token result = Token();
	result.type = OPERAND;

	array<string, 10> a;
	a[0] = "&&";
	a[1] = "==";
	a[2] = "!=";
	a[3] = "||";
	a[4] = "*";
	a[5] = "+";
	a[6] = "/";
	a[7] = "-";
	a[8] = ">";
	a[9] = "<";

	for (int i = 0; i < a.size(); i++) {
		string operand = a[i];
		if (strcomp(s, operand)) {
			result.content = operand;
			result.charOffset = operand.size();
			return result;
		}
	}
	return result;
}

Token Token::createSpecial(string s) {
	Token result;

	//TODO: make this a tuple so you can control the order.
  
  vector<tuple<string, TokenType>> m;
  m.push_back(make_tuple("(", OPENPARAN));
	m.push_back(make_tuple(")", CLOSEPARAN));
	m.push_back(make_tuple("{", OPENCURLY));
	m.push_back(make_tuple("}", CLOSECURLY));
	m.push_back(make_tuple(",", COMMA));
	m.push_back(make_tuple("=>", RETURNS));
	m.push_back(make_tuple("=", EQUALS));
	m.push_back(make_tuple(".", PERIOD));
	m.push_back(make_tuple(":", COLON));
	m.push_back(make_tuple("@", AT));

	for (int i = 0; i < m.size(); i++) {
		string name;
		TokenType tokenType;
		tie(name, tokenType) = m[i];
		if (strcomp(s, name)) {
			result.type = tokenType;
			result.charOffset = name.size();
			return result;
		}
	}
	return result;
}

std::vector<Token> tokenize(std::string data) {
	vector<Token> result;

	string d = data;
	//string *d = data.c_str();
	int currentLine = 1;
	int currentColumn = 1;
	int index = 0;


	while (true) {
		Token token = Token(d);
		if (token.charOffset > 0) {
			token.position.line = currentLine;
			token.position.column = currentColumn;
			result.push_back(token);

			int c = 0;
			while (token.charOffset > c) {
				d = d.substr(1);
				if (d.at(0) == '\n') {
					currentLine++;
					currentColumn = 1;
				}
				c++;
				currentColumn++;
			}
			index += token.charOffset;
			if (index > data.length()) {
				break;
			}

		} else {
			break;
		}
	}
	Token endToken = Token::createEnd();
	endToken.position.line = currentLine;
	endToken.position.column = 0;
	result.push_back(endToken);


	return result;
}

std::string tokenTypeString(TokenType t) {
	switch (t) {
		case INT: return "INT";
		case STRING: return "STRING";
		case LABEL: return "LABEL";
		case OPERAND: return "OPERAND";
		case OPENPARAN: return "OPENPARAN";
		case CLOSEPARAN: return "CLOSEPARAN";
		case OPENCURLY: return "OPENCURLY";
		case CLOSECURLY: return "CLOSECURLY";
		case VAR: return "VAR";
		case FUNC: return "FUNC";
		case COMMA: return "COMMA";
		case EQUALS: return "EQUALS";
		case PERIOD: return "PERIOD";
		case IF: return "IF";
		case ELSE: return "ELSE";
		case RETURN: return "RETURN";
		case BREAK: return "BREAK";
		case WHILE: return "WHILE";
		case LOOP: return "LOOP";
		case UNTIL: return "UNTIL";
		case END: return "END";
		case COLON: return "COLON";
		case RETURNS: return "RETURNS";
		case AT: return "AT";
		case AND: return "AND";
		default: return "ERROR";
	}
};
