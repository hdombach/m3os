#include "command.hpp"
#include <string>
#include "../error.hpp"

using namespace std;

vector<Command *> shiftlCommand();

vector<Command *> shiftlCommand(uchar reg, uchar outReg, uchar byteLength) {
	int limit = REG_MAX + 1 - byteLength;

	if (reg > limit) {
		logInternalError("reg to ghigh for shiftlCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	};
	if (outReg > limit) {
		logInternalError("outReg to high for shiftlCommand )" + to_string(byteLength) + ") bytes.");
		return {};
	};

	vector<Command *> result;

	for (int i = 0; i < byteLength; i++) {
		append(result, moveCommand(REG_X, reg + i));
		append(result, shiftlCommand());
		append(result, moveCommand(outReg + i, REG_O));
	};

	return result;
};

vector<Command *> shiftlStackCommand(uchar byteLength) {
	auto result = loadStackCommand(REG_0, byteLength, REG_16);
	append(result, shiftlCommand(REG_0, REG_0, byteLength));
	append(result, storeStackCommand(REG_0, byteLength, REG_16));
	return result;
};
