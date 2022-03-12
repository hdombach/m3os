#ifndef MEMORY_H
#define MEMORY_H

#define MEM_SIZE 65536

unsigned char *initMemory();

void loadFile(unsigned char *memory, char *fileName);

unsigned char getHigh(unsigned char *memory, short address);

unsigned char getLow(unsigned char *memory, short address);

#endif

