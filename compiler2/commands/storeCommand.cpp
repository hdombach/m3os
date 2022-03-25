#include "command.hpp"
#include <vector>
#include "../error.hpp"

vector<uchar> storeCommand(uchar reg) {
	return {COM_STO, reg};
};

vector<uchar> storeCommand(uchar reg, uchar byteLength, uchar tempReg) {
	int limit = REG_MAX + 1 - byteLength;
	if (reg >  limit) {
		logInternalError("reg to ghigh for storeCommand");
	}
	if (tempReg > limit) {
		logInternalError("tempReg to high for storeCommand");
	}
	
	auto result = rawCommand(tempReg, (unsigned int) 1);
	for (int i = 0; i < byteLength; i++) {
		append(result, storeCommand(reg + 1));
		append(result, addCommand(REG_A0, tempReg, REG_A0, 4));
	}

	result.pop_back();

	return result;
};

vector<uchar> storeStackCommand(uchar reg, uchar byteLength, uchar tempReg) {
	auto result = getStackEndCommand(tempReg);
	append(result, storeCommand(reg, byteLength, tempReg));
	return result;
};

vector<uchar> storeConstCommand(uchar reg, unsigned int adr) {
	auto result = rawCommand(REG_A0, adr);
	append(result, storeCommand(reg));
	return result;
};
