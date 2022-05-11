#include "command.hpp"
#include <vector>
#include "../error.hpp"

vector<Command *> loadCommand(uchar reg) {
	return {new Command(COM_LOD, {reg})};
}

vector<Command *> loadCommand(uchar reg, uchar byteLength, uchar tempReg) {
	int limit = REG_MAX + 1 - byteLength;
	if (reg > limit) {
		logInternalError("reg to high for loadCommand");
	}
	if (tempReg > limit) {
		logInternalError("tempREg to ghigh for loadCommand");
	}
	auto result = rawCommand(tempReg, (unsigned int) 1);

	for (int i = 0; i < byteLength; i++) {
		append(result, loadCommand(reg + i));
		append(result, addCommand(REG_A0, tempReg, REG_A0, 4));
	}
	//strip the last add command as it does nothign
	//If the bytelength is 0, it will strip the raw32Command so win win
	result.pop_back();

	return result;
};

vector<Command *> loadStackCommand(uchar reg, uchar byteLength, uchar tempReg) {
	auto result = getStackEndAdrCommand(tempReg);
	append(result, loadCommand(reg, byteLength, tempReg));
	return result;
}

vector<Command *> loadConstCommand(uchar reg, unsigned int adr, uchar byteLength, uchar tempReg) {
	auto result = rawCommand(REG_A0, adr);
	append(result, loadCommand(reg, byteLength, tempReg));
	return result;
};
