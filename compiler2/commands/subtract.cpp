#include "command.hpp"
#include <vector>
#include "../error.hpp"

using namespace std;

vector<Command *> subtractCommand() {
	return {new Command(COM_SUB)};
}

vector<Command *> subtractCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength) {
	int limit = REG_MAX + 1 - byteLength;

	if  (aReg > limit) {
		logInternalError("aReg to high for subtractCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	}
	if (bReg > limit) {
		logInternalError("bReg to high for subtractCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	}
	if (outReg > limit) {
		logInternalError("outReg to ghigh for subtractCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	}

	vector<Command *> result = rawCommand(REG_C, (uchar) 0);

	for (int i = 0; i < byteLength; i++) {
		append(result, moveCommand(REG_X, aReg + i));
		append(result, moveCommand(REG_Y, bReg + i));
		append(result, subtractCommand());
		append(result, moveCommand(outReg + i, REG_O));
	}

	return result;

};


vector<Command *> subtractStackCommand(uchar byteLength) {
	auto result = loadStackCommand(REG_0, byteLength, REG_16);
	append(result, popConstCommand(byteLength, REG_16));
	append(result, loadStackCommand(REG_8, byteLength, REG_16));
	append(result, subtractCommand(REG_0, REG_8, REG_0, byteLength));
	append(result, storeStackCommand(REG_0, byteLength, REG_16));
	return result;
};
