#include "command.hpp"
#include <vector>

using namespace std;

vector<Command *> inputCommand(uchar reg) {
	return {new Command(COM_IN, {reg})};
};

vector<Command *> inputCommand(uchar reg, uchar channel) {
	auto result = rawCommand(REG_IP, channel);
	append(result, inputCommand(reg));
	return result;
};

vector<Command *> outputCommand(uchar reg) {
	return {new Command(COM_OUT, {reg})};
};
vector<Command *> outputCommand(uchar reg, uchar channel) {
	auto result = rawCommand(REG_OP, channel);
	append(result, outputCommand(reg));
	return result;
};
vector<Command *> printCommand(uchar reg) {
	return outputCommand(reg, 0);
};
