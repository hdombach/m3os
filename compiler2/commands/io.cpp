#include "command.hpp"
#include <vector>

using namespace std;

vector<uchar> inputCommand(uchar reg) {
	return {COM_IN};
};
vector<uchar> inputCommand(uchar reg, uchar channel) {
	auto result = rawCommand(REG_IP, channel);
	append(result, inputCommand(reg));
	return result;
};

vector<uchar> outputCommand(uchar reg) {
	return {COM_OUT};
};
vector<uchar> outputCommand(uchar reg, uchar channel) {
	auto result = rawCommand(REG_OP, channel);
	append(result, outputCommand(reg));
	return result;
};
vector<uchar> printCommand(uchar reg) {
	return outputCommand(reg, 0);
};
