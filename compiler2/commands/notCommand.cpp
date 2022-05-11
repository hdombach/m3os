#include "command.hpp"
#include <string>
#include "../error.hpp"

using namespace std;

vector<Command *> notCommand() {
	return {new Command(COM_NOT)};
};

vector<Command *> notCommand(uchar reg, uchar outReg, uchar byteLength) {
	int limit = REG_MAX + 1 - byteLength;

	if (reg > limit) {
		logInternalError("aReg to ghigh for notCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	};
	if (outReg > limit) {
		logInternalError("out to high for notCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	};

	vector<Command *> result;

	for (int i = 0; i < byteLength; i++) {
		append(result, moveCommand(REG_X, reg + i));
		append(result, notCommand());
		append(result, moveCommand(outReg + i, REG_O));
	};

	return result;
};

vector<Command *> notStackCommand(uchar byteLength) {
	auto result = loadStackCommand(REG_0, byteLength, REG_16);
	append(result, notCommand(REG_0, REG_0, byteLength));
	append(result, storeStackCommand(REG_0, byteLength, REG_16));
	return result;
};
