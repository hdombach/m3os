#include "command.hpp"
#include <vector>
#include "../error.hpp"

vector<uchar> rawCommand(uchar reg, uchar d) {
	return {COM_RAW, d};
};

vector<uchar> rawCommand(uchar reg, uchar *d, int byteLength) {
	int limit = REG_MAX + 1 - byteLength;
	if (reg > limit) {
		logInternalError("reg to high for rawCommand (" + to_string(byteLength) + ") bytes.");
		return {};
	};

	vector<uchar> result;

	for (int i = 0; i < byteLength; i++) {
		append(result, rawCommand(reg + i, d[i]));
	};

	return result;
};

vector<uchar> rawCommand(uchar reg, unsigned short d) {
	return rawCommand(reg, (uchar *) &d, 2);
};
vector<uchar> rawCommand(uchar reg, unsigned int d) {
	return rawCommand(reg, (uchar *) &d, 4);
};
vector<uchar> rawCommand(uchar reg, unsigned long d) {
	return rawCommand(reg, (uchar *) &d, 8);
};
