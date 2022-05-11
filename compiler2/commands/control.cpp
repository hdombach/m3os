#include "command.hpp"
#include <vector>
#include "../error.hpp"

using namespace std;

vector<Command *> tacCommand(uchar reg) {
	return {new Command(COM_TAC, {reg})};
};

vector<Command *> tacCommand(uchar reg, uchar diffReg) {
	int limit = REG_MAX - 3;
	if (diffReg > limit) {
		logInternalError("diffReg to high for tacCommand");
	};
	auto result = moveCommand(REG_A0, diffReg, 4);
	append(result, tacCommand(reg));
	return result;
};

vector<Command *> jumpCommand() {
	return {new Command(COM_JMP)};
};
vector<Command *> jumpCommand(uchar diffReg) {
	int limit = REG_MAX - 3;
	if (diffReg > limit) {
		logInternalError("diffReg to high for jumpCommand");
	};
	auto result = moveCommand(REG_A0, diffReg, 4);
	append(result, jumpCommand());
	return result;
};
