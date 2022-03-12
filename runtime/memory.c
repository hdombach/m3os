#include "memory.h"
#include <stdio.h>

unsigned char *initMemory() {
	static unsigned char result[MEM_SIZE];
	return result;
}

void loadFile(unsigned char *memory, char *fileName) {
	//help from https://c-for-dummies.com/blog/?p=4046
	
	FILE *fp;
	
	size_t r;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fprintf(stderr,"Unable to open %s\n", fileName);
    return;
	}

	fread(memory, MEM_SIZE, 1, fp);

}

unsigned char getHigh(unsigned char *memory, short address) {
	unsigned char d = memory[address];
	return d / 16;
}

unsigned char getLow(unsigned char *memory, short address) {
	unsigned char d = memory[address];
	return d % 16;
}
