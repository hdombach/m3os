#include "cCommand.hpp"

string ccommand(BlockNode *node) {
	string result;
	for (int i = 0; i < node->statements.size(); i++) {
		result += ccommand(node->statements[i]);
	};
	return result;
};
