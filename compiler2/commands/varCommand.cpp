#include "command.hpp"
#include "../symbolTable.hpp"
#include "../error.hpp"

vector<Command *> getVarAdrCommand(string name, SymbolTable *table, int outReg) {
	vector<Command *> result;
	SymbolTable *curTable = table;
	int offset = 0;
	//Loads the frame pointer into memroy
	append(result, loadConstCommand(REG_0, MEM_FRM, 4));
	while (true) {
		offset = curTable->getMemoryOffset(name);
		if (offset > -1) {
			//Loads the offset into reg 4
			append(result, rawCommand(REG_4, (unsigned int) offset));
			//Increase the pointer stack
			append(result, addCommand(REG_0, REG_4, REG_0, 4));
			append(result, moveCommand(REG_0, outReg, 4));
			return result;
		} else {
			offset = curTable->getPrevFrameMemoryOffset();
			//gets the address for the next frame
			append(result, rawCommand(REG_4, (unsigned int) offset));
			append(result, addCommand(REG_0, REG_4, REG_A0, 4));
			//moves address to A0-A3 before loading
			append(result, moveCommand(REG_0, REG_A0, 4));
			append(result, loadCommand(REG_0, 4, REG_8));
			if (curTable->isRoot()) {
				logError("can't find var " + name + " when generating commands");
				return {};
			}
			curTable = curTable->getParent();
		}
	}
};

vector<Command *> pushVarCommand(string name, SymbolTable *table) {
	vector<Command *> result;
	int allocatedSize = table->getAllocatedSize(name);

	//increases stack by a size
	append(result, pushConstCommand(allocatedSize));
	
	append(result, getVarAdrCommand(name, table));

	append(result, loadCommand(REG_0, allocatedSize, REG_0 + allocatedSize));

	append(result, getStackEndAdrCommand(REG_16));

	append(result, storeCommand(REG_0, allocatedSize, REG_0 + allocatedSize));

	return result;
};

vector<Command *> popVarCommand(string name, SymbolTable *table) {
	vector<Command *> result;
	int allocatedSize = table->getAllocatedSize(name);

	append(result, getVarAdrCommand(name, table));

	append(result, loadCommand(REG_0, allocatedSize, REG_0 + allocatedSize));

	append(result, getStackEndAdrCommand(REG_16));

	append(result, storeCommand(REG_0, allocatedSize, REG_0 + allocatedSize));

	return result;

};
