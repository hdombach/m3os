#include "command.hpp"
#include <string>
#include "../error.hpp"

using namespace std;

vector<uchar> addCommand() {
	return {COM_ADD};
};

vector<uchar> addCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength) {
	int limit = REG_MAX + 1 - byteLength;

	if  (aReg > limit) {
		logInternalError("aReg to high for addCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	}
	if (bReg > limit) {
		logInternalError("bReg to high for addCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	}
	if (outReg > limit) {
		logInternalError("outReg to ghigh for addCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	}

	unsigned int zero = 0;
	vector<uchar> result = rawCommand(REG_C, zero);

	for (int i = 0; i < byteLength; i++) {
		append(result, moveCommand(REG_X, aReg + i));
		append(result, moveCommand(REG_Y, bReg + i));
		append(result, addCommand());
		append(result, moveCommand(outReg + i, REG_O));
	}

	return result;
};

vector<uchar> addStackCommand(uchar byteLength) {
	auto result = loadStackCommand(REG_0, byteLength, REG_16);
	append(result, popConstCommand(byteLength, REG_16));
	append(result, loadStackCommand(REG_8, byteLength, REG_16));
	append(result, addCommand(REG_0, REG_8, REG_0, byteLength));
	append(result, storeStackCommand(REG_0, byteLength, REG_16));
	return result;
};

