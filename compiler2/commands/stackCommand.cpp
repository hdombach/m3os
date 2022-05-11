#include "command.hpp"
#include <vector>
#include "../error.hpp"

vector<Command *> pushCommand(uchar diffReg, uchar tempReg) {
	auto result = getStackEndAdrCommand(tempReg);
	append(result, subtractCommand(diffReg, tempReg, tempReg, 4));
	append(result, storeConstCommand(tempReg, MEM_STK, 4));
	return result;
};
vector<Command *> pushConstCommand(unsigned int diff, uchar tempReg1, uchar tempReg2) {
	auto result = rawCommand(tempReg1, diff);
	append(result, pushCommand(tempReg1, tempReg2));
	return result;
};

vector<Command *> popCommand(uchar diffReg, uchar tempReg) {
	auto result = getStackEndAdrCommand(tempReg);
	append(result, addCommand(diffReg, tempReg, tempReg, 4));
	append(result, storeConstCommand(tempReg, MEM_STK, 4));
	return result;
};
vector<Command *> popConstCommand(unsigned int diff, uchar tempReg1, uchar tempReg2) {
	auto result = rawCommand(tempReg1, diff);
	append(result, popCommand(tempReg1, tempReg2));
	return result;
};

vector<Command *> getStackAdrCommand(uchar lengthReg, uchar outReg, uchar tempReg) {
	auto result = getStackEndAdrCommand(outReg, tempReg);
	append(result, addCommand(outReg, lengthReg, outReg, 4));
	return result;
};

vector<Command *> getStackEndAdrCommand(uchar outReg, uchar tempReg) {
	return loadConstCommand(outReg, MEM_STK, 4, tempReg);
};
