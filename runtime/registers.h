#ifndef REGISTERS_H
#define REGISTERS_H

enum Register{x, y, o, c, a0, a1, ip, op, p0, p1, s0, s1, r3, r2, r1, r0};

unsigned char *initRegisters();

short getProgramCounter(unsigned char *r);

void setProgramCounter(short value, unsigned char *r);

void increaseProgramCounter(short value, unsigned char *r);

short getAddress(unsigned char *r);


#endif
