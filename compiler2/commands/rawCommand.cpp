#include "command.hpp"
#include <vector>
#include "../error.hpp"

vector<Command *> rawCommand(uchar reg, uchar d) {
	return {new Command(COM_RAW, {d})};
};

vector<Command *> rawCommand(uchar reg, uchar *d, int byteLength) {
	int limit = REG_MAX + 1 - byteLength;
	if (reg > limit) {
		logInternalError("reg to high for rawCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	};

	vector<Command *> result;

	for (int i = 0; i < byteLength; i++) {
		append(result, rawCommand(reg + i, d[i]));
	};

	return result;
};

vector<Command *> rawCommand(uchar reg, unsigned short d) {
	return rawCommand(reg, (uchar *) &d, 2);
};
vector<Command *> rawCommand(uchar reg, unsigned int d) {
	return rawCommand(reg, (uchar *) &d, 4);
};
vector<Command *> rawCommand(uchar reg, unsigned long d) {
	return rawCommand(reg, (uchar *) &d, 8);
};
