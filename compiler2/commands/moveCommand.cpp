#include "command.hpp"
#include <vector>
#include "../error.hpp"

vector<uchar> moveCommand(uchar reg1, uchar reg2) {
	return {COM_MOV, reg1, reg2};
};

vector<uchar> moveCommand(uchar reg1, uchar reg2, uchar byteLength) {
	int limit = REG_MAX + 1 - byteLength;
	
	if (reg1 > limit) {
		logInternalError("reg1 to ghigh for moveCommand (" + to_string(byteLength) + ") bytes");
		return {};
	};
	if (reg2 > limit) {
		logInternalError("reg2 to high for moveCommand (" + to_string(byteLength) + ") bytes");
		return {};
	};

	vector<uchar> result;

	for (int i = 0; i < byteLength; i++) {
		append(result, moveCommand(reg1 + i, reg2 + i));
	};

	return result;
};
