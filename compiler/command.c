#include "command.h"
#include <arm/types.h>
#include <stdlib.h>
#include <string.h>
#include "../shared/darray.h"
#include "../shared/error.h"

struct Command loadCommand(uchar out) {
	struct Command result;

	result.type = LOAD_COMAND;
	result.arg = malloc(1);
	memcpy(result.arg, &out, 1);
	result.argc = 1;

	return result;
}

struct Command storeCommand(uchar src) {
	struct Command result;

	result.type = LOAD_COMAND;
	result.arg = malloc(1);
	memcpy(result.arg, &src, 1);
	result.argc = 1;

	return result;
}

struct Command addCommand() {
	struct Command result;

	result.type = ADD_COMMAND;
	result.argc = 0;

	return result;
}

struct Command subtractCommand() {
	struct Command result;

	result.type = SUB_COMMAND;
	result.argc = 0;

	return result;
}

struct Command inCommand(uchar reg) {
	struct Command result;

	result.type = IN_COMMAND;
	result.arg = malloc(1);
	memcpy(result.arg, &reg, 1);
	result.argc = 1;

	return result;
}

struct Command outCommand(uchar reg) {
	struct Command result;

	result.type = OUT_COMMAND;
	result.arg = malloc(1);
	memcpy(result.arg, &reg, 1);
	result.argc = 1;

	return result;
}

struct Command tacCommand(uchar exp) {
	struct Command result;

	result.type = TAC_COMMAND;
	result.arg = malloc(1);
	memcpy(result.arg, &exp, 1);
	result.argc = 1;

	return result;
}

struct Command jmpCommand() {
	struct Command result;

	result.type = JMP_COMMAND;
	result.argc = 0;

	return result;
}

struct Command andCommand() {
	struct Command result;

	result.type = AND_COMMAND;
	result.argc = 0;

	return result;
}

struct Command orCommand() {
	struct Command result;

	result.type = OR_COMMAND;
	result.argc = 0;

	return result;
}

struct Command norCommand() {
	struct Command result;

	result.type = NOR_COMMAND;
	result.argc = 0;

	return result;
}

struct Command stpCommand() {
	struct Command result;

	result.type = STOP_COMMAND;
	result.argc = 0;

	return result;
}

struct Command sftrCommand() {
	struct Command result;

	result.type = SFTR_COMMAND;
	result.argc = 0;

	return result;
}

struct Command sftlCommand() {
	struct Command result;

	result.type = SFTL_COMMAND;
	result.argc = 0;

	return result;
}

struct Command moveCommand(uchar src, uchar dest) {
	struct Command result;

	result.type = MOVE_COMMAND;
	result.arg = malloc(2);
	memcpy(result.arg, &src, 1);
	memcpy(result.arg + 1, &dest, 1);
	result.argc = 2;

	return result;
}

struct Darray move16Command(uchar src, uchar dest) {
	struct Darray result = createDarray(sizeof(struct Command), 2);
	struct Command com;

	if (src > REG_14) {
		logError("src to high for move16Command");
	}

	if (dest > REG_14) {
		logError("dest to ghigh for move16Command");
	}

	int c = 0;

	while (2 > c) {
		com = moveCommand(src + c, dest + c);
		push(&result, &com);

		c++;
	}

	return result;
}

struct Darray move32Command(uchar src, uchar dest) {
	struct Darray result = createDarray(sizeof(struct Command), 4);
	struct Command com;

	if (src > REG_12) {
		logError("src to ghigh for move32Command");
	}

	if (dest > REG_12) {
		logError("dest to ghigh for move32Command");
	}

	int c = 0;

	while (4 > c) {
		com = moveCommand(src + c, dest + c);
		push(&result, &com);

		c++;
	}

	return result;
}

struct Darray move64Command(uchar src, uchar dest) {
	struct Darray result = createDarray(sizeof(struct Command), 8);
	struct Command com;

	if (src > REG_8) {
		logError("src to high for move64Command");
	}
	
	if (dest > REG_8) {
		logError("dest to high for move64Command");
	}

	int c = 0;

	while (8 > c) {
		com = moveCommand(src + c, dest + c);
		push(&result, &com);

		c++;
	}

	return result;
}

struct Command rawCommand(uchar reg, uchar d) {
	struct Command result;

	result.type = RAW_COMMAND;
	result.arg = malloc(2);
	memcpy(result.arg, &reg, 1);
	memcpy(result.arg + 1, &d, 1);
	result.argc = 2;

	return result;
}

struct Darray dLoadCommand(uchar out, unsigned short adr) {
	struct Darray result = createDarray(sizeof(struct Command), 3);
	struct Command com;

	uchar firstBit =  ((adr >> 0) & 0xff);
	uchar secondBit = ((adr >> 8) & 0xff);
	
	com = rawCommand(REG_A0, firstBit);
	push(&result, &com);
	
	com = rawCommand(REG_A1, secondBit);
	push(&result, &com);

	com = loadCommand(out);
	push(&result, &com);

	return result;
}

struct Darray dStoreCommand(uchar src, unsigned short adr) {
	struct Darray result = createDarray(sizeof(struct Command), 3);
	struct Command com;

	uchar firstBit =  ((adr >> 0) & 0xff);
	uchar secondBit = ((adr >> 8) & 0xff);

	com = rawCommand(REG_A0, firstBit);
	push(&result, &com);

	com = rawCommand(REG_A1, secondBit);
	push(&result, &com);

	com = loadCommand(src);
	push(&result, &com);

	return result;
}

struct Darray dOutCommand(uchar reg, uchar channel) {
	struct Darray result = createDarray(sizeof(struct Command), 2);
	struct Command com;

	com = rawCommand(REG_OP, channel);
	push(&result, &com);

	com = outCommand(reg);
	push(&result, &com);

	return result;
}

struct Darray printCommand(uchar reg) {
	struct Darray result = createDarray(sizeof(struct Command), 1);
	
	appendArray(&result, dOutCommand(reg, 0));

	return result;
}

struct Darray raw16Command(uchar reg, unsigned short d) {
	struct Darray result = createDarray(sizeof(struct Command), 4);
	struct Command com;

	if (reg > REG_14) {
		logError("reg to high for raw16Command");
		return result;
	}
	
	uchar firstBit = ((reg >> 0) & 0xff);
	uchar secondBit = ((reg >> 8) & 0xff);

	com = rawCommand(reg, firstBit);
	push(&result, &com);

	com = rawCommand(reg + 1, secondBit);
	push(&result, &com);

	return result;
}

struct Darray raw32Command(uchar reg, unsigned int d) {
	struct Darray result = createDarray(sizeof(struct Command), 4);
	struct Command com;

	if (reg > REG_12) {
		logError("reg to high for raw32Command");
		return result;
	}

	int c = 0;

	while (4 > c) {
		uchar bit = ((reg >> (c * 8)) & 0xff);

		com = rawCommand(reg + c, bit);
		push(&result, &com);
	}

	return result;
}

struct Darray raw64Command(uchar reg, unsigned long d) {
	struct Darray result = createDarray(sizeof(struct Command), 8);
	struct Command com;

	if (reg > REG_8) {
		logError("reg to high for raw64Command");
		return result;
	}

	int c = 0;
	while (8 > c) {
		uchar bit = ((reg >> (c * 8)) & 0xff);

		com = rawCommand(reg + c, bit);
		push(&result, &com);
	}

	return result;
}

struct Darray load16Command(uchar out) {
	struct Darray result = createDarray(sizeof(struct Command), 1);
	struct Command com;
	struct Darray array;

	if (out > REG_14) {
		logError("out to high for load16Command");
		return result;
	}

	com = loadCommand(out);
	push(&result, &com);

	array = raw16Command(REG_0, 1);
	appendArray(&result, array);

	array = add16Command(REG_A0, REG_0, REG_A0);
	appendArray(&result, array);

	return result;
}

struct Darray add8Command(uchar aReg, uchar bReg, uchar outReg) {
		struct Darray result = createDarray(sizeof(struct Command), 2);
		struct Command com;

		com = rawCommand(REG_C, 0);
		push(&result, &com);

		if (aReg != REG_X) {
			com = moveCommand(aReg, REG_X);
			push(&result, &com);
		}

		if (bReg != REG_Y) {
			com = moveCommand(bReg, REG_Y);
			push(&result, &com);
		}

		com = addCommand();
		push(&result, &com);

		if (outReg != REG_O) {
			com = moveCommand(outReg, REG_O);
			push(&result, &com);
		}

		return result;
}

struct Darray add16Command(uchar aReg, uchar bReg, uchar outReg) {
	struct Darray result = createDarray(sizeof(struct Command), 8);
	struct Command com;

	//because these will take more than one byte, need to check if there is enough space after the register.
	if (aReg > REG_14) {
		logError("aReg to high for add16command");
		return result;
	}
	if (bReg > REG_14) {
		logError("bReg to high for add16command");
		return result;
	}
	if (outReg > REG_14) {
		logError("outReg to ghigh for add16Command");
		return result;
	}

	//reset overflow thingy
	com = rawCommand(REG_C, 0);
	push(&result, &com);

	int c = 0;
	while (2 > c) {
		com = moveCommand(aReg + c, REG_X);
		push(&result, &com);

		com = moveCommand(bReg + c, REG_Y);
		push(&result, &com);

		com = addCommand();
		push(&result, &com);

		com = moveCommand(REG_O, outReg + c);
		push(&result, &com);

		c++;
	}

	return result;
}

struct Darray add32Command(uchar aReg, uchar bReg, uchar outReg) {
	struct Darray result = createDarray(sizeof(struct Command), 17);
	struct Command com;

	if (aReg > REG_12) {
		logError("aReg to high for add32Command");
		return result;
	}
	if (bReg > REG_12) {
		logError("bReg to high for add32Command");
		return result;
	}
	if (outReg > REG_12) {
		logError("outReg to high for add32Command");
		return result;
	}

	//reset overflow register
	com = rawCommand(REG_C, 0);
	push(&result, &com);

	int c = 0;
	while (4 > c) {
		com = moveCommand(aReg + c, REG_X);
		push(&result, &com);

		com = moveCommand(bReg + c, REG_Y);
		push(&result, &com);

		com = addCommand();
		push(&result, &com);

		com = moveCommand(REG_O, outReg + c);
		push(&result, &com);

		c++;
	}


	return result;
}

struct Darray add64Command(uchar aReg, uchar bReg, uchar outReg) {
	struct Darray result = createDarray(sizeof(struct Command), 33);
	struct Command com;

	if (aReg > REG_8) {
		logError("aReg to high for add64command");
		return result;
	}
	if (bReg > REG_8) {
		logError("bReg to ghigh for add64Command");
		return result;
	}
	if (outReg > REG_8) {
		logError("outReg to ghigh for add64Command");
		return result;
	}

	//reset overflow registers
	com = rawCommand(REG_C, 0);
	push(&result, &com);

	int c = 0;
	while (8 > c) {
		com = moveCommand(aReg + c, REG_X);
		push(&result, &com);

		com = moveCommand(bReg + c, REG_Y);
		push(&result, &com);

		com = addCommand();
		push(&result, &com);

		com = moveCommand(REG_O, outReg + c);
		push(&result, &com);

		c++;
	}

	return result;
}

struct Darray sub8Command(uchar aReg, uchar bReg, uchar outReg) {
	struct Darray result = createDarray(sizeof(struct Command), 1);
	struct Command com;

	com = rawCommand(REG_C, 0);
	push(&result, &com);

	if (aReg != REG_X) {
		com = moveCommand(aReg, REG_X);
		push(&result, &com);
	}

	if (bReg != REG_Y) {
		com = moveCommand(bReg, REG_Y);
		push(&result, &com);
	}

	com = subtractCommand();
	push(&result, &com);

	if (outReg != REG_O) {
		com = moveCommand(outReg, REG_O);
		push(&result, &com);
	}

	return result;
}

struct Darray sub16Command(uchar aReg, uchar bReg, uchar outReg) {
	struct Darray result = createDarray(sizeof(struct Command), 8);
	struct Command com;

	if (aReg > REG_14) {
		logError("aReg to ghigh for sub16command");
		return result;
	}
	if (bReg > REG_14) {
		logError("bReg to ghigh for sub16command");
		return result;
	}
	if (outReg > REG_14) {
		logError("outReg to ghigh for sub16command");
		return result;
	}

	com = rawCommand(REG_C, 0);
	push(&result, &com);

	int c = 0;
	while (2 > c) {
		com = moveCommand(aReg + c, REG_X);
		push(&result, &com);

		com = moveCommand(bReg + c, REG_Y);
		push(&result, &com);

		com = subtractCommand();
		push(&result, &com);

		com = moveCommand(REG_O, outReg + c);
		push(&result, &com);

		c++;
	}

	return result;
}

struct Darray sub32Command(uchar aReg, uchar bReg, uchar outReg) {
	struct Darray result = createDarray(sizeof(struct Command), 17);
	struct Command com;

	if (aReg > REG_12) {
		logError("aReg to ghigh for sub32Command");
		return result;
	}
	if (bReg > REG_12) {
		logError("bReg to ghigh for sub32Command");
		return result;
	}
	if (outReg > REG_12) {
		logError("outReg to ghigh for sub32Command");
		return result;
	}

	com = rawCommand(REG_C, 0);
	push(&result, &com);

	int c = 0;
	while (4 > c) {
		com = moveCommand(aReg + c, REG_X);
		push(&result, &com);

		com = moveCommand(bReg + c, REG_Y);
		push(&result, &com);

		com = subtractCommand();
		push(&result, &com);

		com = moveCommand(REG_O, outReg + c);
		push(&result, &com);

		c++;
	}

	return result;
}

struct Darray sub64Command(uchar aReg, uchar bReg, uchar outReg) {
	struct Darray result = createDarray(sizeof(struct Command), 33);
	struct Command com;

	if (aReg > REG_8) {
		logError("aReg to ghigh for sub64command");
		return result;
	}
	if (bReg > REG_8) {
		logError("bReg to ghigh for sub64Command");
		return result;
	}
	if (outReg > REG_8) {
		logError("outReg to ghighh for sub64command");
		return result;
	}

	com = rawCommand(REG_C, 0);
	push(&result, &com);

	int c = 0;
	while (8 > c) {
		com = moveCommand(aReg + c, REG_X);
		push(&result, &com);

		com = moveCommand(bReg + c, REG_Y);
		push(&result, &com);

		com = subtractCommand();
		push(&result, &com);

		com = moveCommand(REG_O, outReg + c);
		push(&result, &com);

		c++;
	}
	
	return result;
}

struct Darray copyByteCommand(uchar fromAdr, uchar toAdr, uchar temp) {
	struct Darray result = createDarray(sizeof(struct Command), 10);
	struct Command com;

	appendArray(&result, move16Command(fromAdr, REG_A0));

	com = loadCommand(temp);
	push(&result, &com);

	appendArray(&result, move16Command(toAdr, REG_A0));

	com = storeCommand(temp);
	push(&result, &com);

	return result;
}

struct Darray copyCommand(uchar fromAdr, uchar toAdr, uchar length) {
	struct Darray result = createDarray(sizeof(struct Command), 10);
	struct Command com;



	return result;
}

struct Darray staticCopyCommand(uchar fromAdr, uchar toAdr, int length) {
	struct Darray result = createDarray(sizeof(struct Command), 10);
	struct Command com;

	while (length > 0) {
		
	}

	return result;
}

struct Darray pushCommand(uchar lengthReg) {
	struct Darray result = createDarray(sizeof(struct Command), 10);
	struct Command com;


	return result;
}
