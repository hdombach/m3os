#include "command.hpp"
#include <string>
#include "../error.hpp"

using namespace std;

vector<Command *> shiftrCommand() {
	return {new Command(COM_SFTR)};
};

vector<Command *> shiftrCommand(uchar reg, uchar outReg, uchar byteLength) {
	int limit = REG_MAX + 1 - byteLength;

	if (reg > limit) {
		logInternalError("reg to high for shift right command (" + to_string(byteLength) + ") bytes.");
		return {};
	};
	if (outReg > limit) {
		logInternalError("outReg to high for shiftrCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	};

	vector<Command *> result;

	for (int i = 0; i < byteLength; i++) {
		append(result, moveCommand(REG_X, reg + i));
		append(result, shiftrCommand());
		append(result, moveCommand(outReg + i, REG_O));
	};

	return result;
};

vector<Command *> shiftrStackCommand(uchar byteLength) {
	auto result = loadStackCommand(REG_0, byteLength, REG_16);
	append(result, shiftrCommand(REG_0, REG_0, byteLength));
	append(result, storeStackCommand(REG_0, byteLength, REG_16));
	return result;
};
