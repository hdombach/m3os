#include "command.hpp"
#include <string>
#include "../error.hpp"

using namespace std;

vector<uchar> orCommand() {
	return {COM_OR};
};

vector<uchar> orCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength) {
	int limit = REG_MAX + 1 - byteLength;

	if (aReg > limit) {
		logInternalError("aReg to high for for orCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	};
	if (bReg > limit) {
		logInternalError("bReg to high for orCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	}
	if (outReg > limit) {
		logInternalError("outReg to high for orCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	}

	vector<uchar> result;

	for (int i = 0; i < byteLength; i++) {
		append(result, moveCommand(REG_X, aReg + i));
		append(result, moveCommand(REG_Y, bReg + i));
		append(result, orCommand());
		append(result, moveCommand(outReg + i, REG_O));
	};

	return result;
};

vector<uchar> orStackCommand(uchar byteLength) {
	auto result = loadStackCommand(REG_0, byteLength, REG_16);
	append(result, popConstCommand(byteLength, REG_16));
	append(result, loadStackCommand(REG_8, byteLength, REG_16));
	append(result, orCommand(REG_0, REG_8, REG_0, byteLength));
	append(result, storeStackCommand(REG_0, byteLength, REG_16));
	return result;
};
