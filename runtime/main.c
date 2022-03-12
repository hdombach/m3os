#include <stdio.h>
#include "arg.h"
#include "registers.h"
#include "memory.h"
int main(int argc, char *argv[]) {
		struct Arguments arg = getArg(argc, argv);

		//printf("%s\n", arg.sourceFile);

		//load data into memory
		unsigned char *mem;
		mem = initMemory();
		loadFile(mem, arg.sourceFile);

		//steup registers

		unsigned char *reg = initRegisters();

		short counter = 0;

		while (1) {
			short pc = getProgramCounter(reg);
			unsigned char command = getHigh(mem, pc);
			short add;
			unsigned char r;
			unsigned char exp; //expression
			char oldC;
			short first;
			short second;

			#ifdef DEBUG
			printf("pc: %i (%i): ", pc, command);
			#endif

			counter++;
			if (counter > 200) {
				return 0;
			}

			if (pc > 10) {
				//return 0;
			}
			switch(command) {
				case 0: //load
					add = getAddress(reg);
					r = getLow(mem, pc);
					reg[r] = mem[add];

					#ifdef DEBUG
					printf("Load: r%i = @%i (%i)\n", r, add, mem[add]);
					#endif

					increaseProgramCounter(1, reg);
					break;
				case 1: // store
					add = getAddress(reg);
					r = getLow(mem, pc);
					mem[add] = reg[r];

					#ifdef DEBUG
					printf("Store: @%i = r%i (%i)\n", add, r, reg[r]);
					#endif
					increaseProgramCounter(1, reg);
					break;
				case 2: //add //TODO add overflow
					reg[o] = reg[x] + reg[y];
					increaseProgramCounter(1, reg);

					#ifdef DEBUG
					printf("ADD %i + %i = %i\n", reg[x], reg[y], reg[o]);
					#endif
					break;
				case 3: //sub
					reg[o] = reg[x] - reg[y];
					increaseProgramCounter(1, reg);

					#ifdef DEBUG
					printf("SUB %i - %i = %i\n", reg[x], reg[y], reg[o]);
					#endif
					break;
				case 4: //input
					r = getLow(mem, pc);
					reg[r] = getchar();
					increaseProgramCounter(1, reg);

					#ifdef DEBUG
					printf("INPIT r%i = %i\n", r, reg[r]);
					#endif
					break;
				case 5: //output
					r = getLow(mem, pc);
					#ifdef DEBUG
					printf("Out r%i (%i, %c)\n", r, reg[r], reg[r]);
					#else
					printf("%c", reg[r]);
					#endif
					increaseProgramCounter(1, reg);
					break;
				case 6: //tac
					r = getLow(mem, pc);
					exp = reg[r];

					#ifdef DEBUG
					printf("TAC r%i (%i)\n", r, reg[r]);
					#endif
					if (exp > 127) {
						add = getAddress(reg);
						setProgramCounter(add, reg);
					} else {
						increaseProgramCounter(1, reg);
					}
					break;
				case 7: //jmp
					add = getAddress(reg);
					#ifdef DEBUG
					printf("JUMP %i\n", add);
					#endif
					setProgramCounter(add, reg);
					break;
				case 8: //and
					reg[o] = reg[x] & reg[y];
					#ifdef DEBUG
					printf("AND %i & %i = %i\n", reg[x], reg[y], reg[o]);
					#endif
					increaseProgramCounter(1, reg);
					break;
				case 9: //or
					reg[o] = reg[x] | reg[y];
					#ifdef DEBUG
					printf("OR %i | %i = %i\n", reg[x], reg[y], reg[o]);
					#endif
					increaseProgramCounter(1, reg);
					break;
				case 10: //nor
					reg[o] = ~(reg[x] | reg[y]);
					#ifdef DEBUG
					printf("NOR %i ~| %i = %i\n", reg[x], reg[y], reg[o]);
					#endif
					increaseProgramCounter(1, reg);
					break;
				case 11: //stop
					#ifdef DEBUG
					printf("STOP\n");
					#endif
					return 0;
				case 12: //shift right
					oldC = reg[c];
					reg[o] = reg[x] >> 1;
					#ifdef DEBUG
					printf("SFTR %i >> 1 = %i\n", reg[x], reg[o]);
					#endif
					increaseProgramCounter(1, reg);
					break;
				case 13: //shift left
					reg[o] = reg[x] << 1;
					#ifdef DEBUG
					printf("SFTL %i << 1 = %i\n", reg[x], reg[o]);
					#endif
					increaseProgramCounter(1, reg);
					break;
				case 14: //move
					add = getProgramCounter(reg);
					first = getLow(mem, add);
					increaseProgramCounter(1, reg);
					add = getProgramCounter(reg);
					second = getHigh(mem, add);
					reg[second] = reg[first];
					increaseProgramCounter(1, reg);
					#ifdef DEBUG
					printf("MOVE r%i -> r%i\n", first, second);
					#endif

					break;
				case 15: //raw
					add = getProgramCounter(reg);
					r = getLow(mem, add);
					increaseProgramCounter(1, reg);
					add = getProgramCounter(reg);
					reg[r] = mem[add];
					increaseProgramCounter(1, reg);
					#ifdef DEBUG
					printf("RAW r%i <- %i\n", r, mem[add]);
					#endif
					break;
				default:
					return 0;
			}
		}

		return 0;
}
