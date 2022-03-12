#ifndef COMMAND_H
#define COMMAND_H

#include "../shared/darray.h"
#include "symbolTable.h"

typedef unsigned char uchar;

#define REG_X 0 //x buffer
#define REG_Y 1 //ybuffer
#define REG_O 2 //output buffer
#define REG_C 3 //overfloaw buffer
#define REG_A0 4 //addresss buffer 1
#define REG_A1 5 //address buffer 2
#define REG_IP 6 //input channel
#define REG_OP 7 //output channell
#define REG_P0 8 //program counter
#define REG_P1 9
#define REG_S0 10  //stack pointer
#define REG_S1 11  
#define REG_SE0 12 //stack end
#define REG_SE1 13 
#define REG_SS0 14 //stack size
#define REG_SS1 15

#define REG_0 16
#define REG_1 17
#define REG_2 18
#define REG_3 19
#define REG_4 20
#define REG_5 21
#define REG_6 22
#define REG_7 23
#define REG_8 24
#define REG_9 25
#define REG_10 26
#define REG_11 27
#define REG_12 28
#define REG_13 29
#define REG_14 30
#define REG_15 31

enum CommandType {
	LOAD_COMAND,
	STORE_COMMAND,
	ADD_COMMAND,
	SUB_COMMAND,
	IN_COMMAND,
	OUT_COMMAND,
	TAC_COMMAND,
	JMP_COMMAND,
	AND_COMMAND,
	OR_COMMAND,
	NOR_COMMAND,
	STOP_COMMAND,
	SFTR_COMMAND,
	SFTL_COMMAND,
	MOVE_COMMAND,
	RAW_COMMAND
};

struct Command {
	uchar *arg;
	int argc;
	enum CommandType type;
};

//Creates load command.
//uchar out: register to load data into
struct Command loadCommand(uchar out);

//creates store command.
//uchar src: register to read from
struct Command storeCommand(uchar src);

//creates add command
struct Command addCommand();

//create subtract command
struct Command subtractCommand();

//create input command
//uchar reg: register to load into
struct Command inCommand(uchar reg);

//create output command
//uchar reg: register to read from
struct Command outCommand(uchar reg);

//create tac command (jumps to value in address register)
//uchar exp: register of value to test
struct Command tacCommand(uchar exp);

//create jmp command (jumpts to value in address register)
struct Command jmpCommand();

//create and command
struct Command andCommand();

//create or command
struct Command orCommand();

//creates nor command
struct Command norCommand();

//creates stop command
struct Command stpCommand();

//create shift right command
struct Command sftrCommand();

//creates shift left command
struct Command sftlCommand();

//create move command
//uchar src: address of value to read from
//uchar dest: address of value to load into
struct Command moveCommand(uchar src, uchar dest);

//crates a command to move 16 bits
//uchar src: address of the start of the vlaue
//uchar dest: adress of the start of the area to write to
struct Darray move16Command(uchar src, uchar dest);

//creates a command to move 32 bits
//uchar src: address of register to read from
//uchar dest: address of the start of the register to write toAdr
struct Darray move32Command(uchar src, uchar dest);

struct Darray move64Command(uchar src, uchar dest);

//create raw command
//uchar reg: register to load data into
//uchar d: 1 byte of data to load
struct Command rawCommand(uchar reg, uchar d);


//create load commands
//uchar out: register to laod into
//unsigned short adr: address to load from
struct Darray dLoadCommand(uchar out, unsigned short adr);

//create store commands
//uchar src: register to load from
//unsigned short adr: address to into
struct Darray dStoreCommand(uchar src, unsigned short adr);

//create out command
//uchar reg: register containing ouput value
//uchar channel: channel to output to
struct Darray dOutCommand(uchar reg, uchar channel);

//create print command
//uchar reg: register to print from
struct Darray printCommand(uchar reg);

//create commands to laod 16 bits
//uchar reg: beggining register to load into
//unsigned short d: data to load
struct Darray raw16Command(uchar reg, unsigned short d);

//create commands to laod 32 bits
//uchar reg: beggining register to laod int
//unsigned int d: data to laod
struct Darray raw32Command(uchar reg, unsigned int d);

//create commands to laod 64 bits
//uchar reg: beggiing register to laod into
//unsigned long d: data to load
struct Darray raw64Command(uchar reg, unsigned long d);

//create commands to load 16 bits from address at address register
//uchar out: beggining register to load into
struct Darray load16Command(uchar out);

//create commadns to laod 32 bits from address at address register
//uchar out: beggining register to load into
struct Darray load32Command(uchar out);

//create commands to load 64 bits from address at address register
//uchar out: beggining register to load into
struct Darray load64Command(uchar out);

//create commands to store 16 bit
//uchar out: beggining register to read from
struct Darray store16Command(uchar out);

//create commands to store 32 bit
//uchar out: beggining register to read from
struct Darray store32Command(uchar out);

//create commands to store 64 bit
//uchar out: beggining register to read from
struct Darray store64Command(uchar out);

//create commands to add 8 bits
//uchar aReg: left side register
//uchar bReg: right side register
//uchar outReg: register to load result into
struct Darray add8Command(uchar aReg, uchar bReg, uchar outReg);

//create commands to add 16 bits
//uchar aReg: left side register
//uchar bReg: right side register
//uchar outReg: register to laod result into
struct Darray add16Command(uchar aReg, uchar bReg, uchar outReg);

//create commadns to add 32 bits
//uchar aReg: left side register
//uchar bReg: right side register
//uchar outReg: register to load result into
struct Darray add32Command(uchar aReg, uchar bReg, uchar outReg);

//create commands to add 64 bits
//uchar aReg left side register
//uchar bReg: right side register
//uchar outReg: register to laod result into
struct Darray add64Command(uchar aReg, uchar bReg, uchar outReg);

//create commands to subtract 8 bits
//uchar aReg: left side register
//uchar bReg: right sdie register
//outReg: register to load result into
struct Darray sub8Command(uchar aReg, uchar bReg, uchar outReg); //out = a - bReg

//create commands to subtract 16 bits
//uchar aReg: left side register
//uchar bReg: right side register
//uchar outReg: register to load result into
struct Darray sub16Command(uchar aReg, uchar bReg, uchar outReg);

//create commands to subtract 32 bits
//uchar aReg: left side register
//uchar bReg: right side register
//uchar outReg: register to load result into
struct Darray sub32Command(uchar aReg, uchar bReg, uchar outReg);

//create commands to subtract 64 bits
//uchar aReg: left side register
//uchar bReg: right side register
//uchar outReg: register to load result into
struct Darray sub64Command(uchar aReg, uchar bReg, uchar outReg);

//copy a single byte
//uchar fromAdr: register to from address
//uchar toAdr: register to to address
//uchar temp: a register that can be used internally
struct Darray copyByteCommand(uchar fromAdr, uchar toAdr, uchar temp);

//copy command
//uchar fromAdr: register to from address
//uchar toAdr: regist to to address
//uchar length register storing how long it is
struct Darray copyCommand(uchar fromAdr, uchar toAdr, uchar length);

//copy command but length is hardcoded
//uchar fromAdr: register to from address
//uchar toAdr: register to to address
struct Darray staticCopyCommand(uchar fromAdr, uchar toAdr, int length);

//create commands to incriment stack pointer
//uchar lengthReg: register that holds length
struct Darray pushCommand(uchar lengthReg); 

//create commands to decriment stack pointer
//uchar lengthReg: register that holds length
struct Darray popCommand(uchar lengthReg);

//loads offset of current stack pointer into the address registers
//uchar offsetAdr: The offset from the start of the stack
struct Darray getStackCommand(uchar offestAdr);

//loads the appropiate frame onto the stack
struct Darray loadFrame(struct SymbolTable);

struct Darray getVarAddress(struct SymbolTable, char *name);
struct Darray mallocCommand(uchar length, uchar out);
struct Darray freeCommand(uchar add);


#endif
