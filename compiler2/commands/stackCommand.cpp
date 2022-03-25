#include "command.hpp"
#include <vector>
#include "../error.hpp"

vector<uchar> pushCommand(uchar diffReg, uchar tempReg) {
	auto result = getStackEndAdrCommand(tempReg);
	append(result, subtractCommand(diffReg, tempReg, tempReg, 4));
	append(result, storeConstCommand(tempReg, MEM_STK, 4));
	return result;
};
vector<uchar> pushConstCommand(unsigned int diff, uchar tempReg1, uchar tempReg2) {
	auto result = rawCommand(tempReg1, diff);
	append(result, pushCommand(tempReg1, tempReg2));
	return result;
};

vector<uchar> popCommand(uchar diffReg, uchar tempReg) {
	auto result = getStackEndAdrCommand(tempReg);
	append(result, addCommand(diffReg, tempReg, tempReg, 4));
	append(result, storeConstCommand(tempReg, MEM_STK, 4));
	return result;
};
vector<uchar> popConstCommand(unsigned int diff, uchar tempReg1, uchar tempReg2) {
	auto result = rawCommand(tempReg1, diff);
	append(result, popCommand(tempReg1, tempReg2));
	return result;
};

vector<uchar> getStackAdrCommand(uchar lengthReg, uchar outReg) {
	auto result = getStackEndAdrCommand(outReg);
	append(result, addCommand(outReg, lengthReg, outReg, 4));
	return result;
};

vector<uchar> getStackEndAdrCommand(uchar outReg) {
	return loadConstCommand(outReg, MEM_STK, 4);
};
