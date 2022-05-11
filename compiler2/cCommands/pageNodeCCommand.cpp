#include "cCommand.hpp"

string ccommand(PageNode *node) {
	return ccommand(&node->block);
};
