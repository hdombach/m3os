#include "command.hpp"
#include <vector>
#include "../error.hpp"

using namespace std;

vector<uchar> tacCommand(uchar reg) {
	return {COM_TAC, reg};
};
vector<uchar> tacCommand(uchar reg, uchar diffReg) {
	int limit = REG_MAX - 3;
	if (diffReg > limit) {
		logInternalError("diffReg to high for tacCommand");
	};
	auto result = moveCommand(REG_A0, diffReg, 4);
	append(result, tacCommand(reg));
	return result;
};

vector<uchar> jumpCommand() {
	return {COM_JMP};
};
vector<uchar> jumpCommand(uchar diffReg) {
	int limit = REG_MAX - 3;
	if (diffReg > limit) {
		logInternalError("diffReg to high for jumpCommand");
	};
	auto result = moveCommand(REG_A0, diffReg, 4);
	append(result, jumpCommand());
	return result;
};
