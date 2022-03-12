#include "registers.h"

unsigned char *initRegisters() {
	static unsigned char result[16];
	result[p0] = 0;
	result[p1] = 0;

	result[s0] = 255;
	result[s1] = 255;

	return result;
}

short getProgramCounter(unsigned char *r) {
	short high = r[p0];
	short low = r[p1];
	return high * 256 + low;
}

void setProgramCounter(short value, unsigned char *r) {
	short high = value / 256;
	short low = value % 256;
	r[p0] = high;
	r[p1] = low;
}

void increaseProgramCounter(short value, unsigned char *r) {
	short counter = getProgramCounter(r);
	counter += value;
	setProgramCounter(counter, r);
}

short getAddress(unsigned char * r) {
	short high = r[a0];
	short low = r[a1];
	return high * 256 + low;
}
