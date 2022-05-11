#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include "../nodes/node.hpp"
#include "../symbolTable.hpp"
using namespace std;

#define REG_X 0
#define REG_Y 1
#define REG_O 2
#define REG_C 3
#define REG_A0 4
#define REG_A1 5
#define REG_A2 6
#define REG_A3 7
#define REG_P0 8
#define REG_P1 9
#define REG_P2 10
#define REG_P3 11
#define REG_IP 12
#define REG_OP 13


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
#define REG_16 32
#define REG_17 33
#define REG_18 34
#define REG_19 35
#define REG_20 36
#define REG_21 37
#define REG_22 38
#define REG_23 39
#define REG_24 40
#define REG_25 41
#define REG_26 42
#define REG_27 43
#define REG_28 44
#define REG_29 45
#define REG_30 46
#define REG_31 47
#define REG_MAX 47


#define COM_LOD 0
#define COM_STO 1
#define COM_ADD 2
#define COM_SUB 3
#define COM_IN 4
#define COM_OUT 5
#define COM_TAC 6
#define COM_JMP 7
#define COM_AND 8
#define COM_OR 9
#define COM_NOT 10
#define COM_MORE 11
#define COM_SFTR 12
#define COM_SFTL 13
#define COM_MOV 14
#define COM_RAW 15

#define MEM_STK 0 //stack end
#define MEM_STKPTR 4 //stack allocation
#define MEM_FRM 8 //stack frame
#define MEM_HP //12

typedef unsigned char uchar;

class Command {
public:
	uchar instruction;
	vector<uchar> args;
	unsigned int adr;
public:
	virtual vector<uchar> getRaw();
	Command();
	Command(uchar instruction, vector<uchar> args={});
};

class TacCommand: Command {
private:
	Command *targetCmd;
	BlockNode *targetBlock;
public:
	virtual vector<uchar> getRaw();
	TacCommand(vector<uchar> args);
	TacCommand(vector<uchar> args, Command *target);
	TacCommand(vector<uchar> args, BlockNode *target);
};

class JumpCommand: Command {
private:
	Command *targetCmd;
	BlockNode *targetBlock;
public:
	virtual vector<uchar> getRaw();
	JumpCommand(vector<uchar> args);
	JumpCommand(Command *target);
	JumpCommand(BlockNode *target);
};

template <class T>
void append(vector<T> a, vector<T> b);

/**
 *	Loads a single byte form memory into the reg
 *	@param reg The reg to load the value into
 *	@note uses A0-A3
 */
vector<Command *> loadCommand(uchar reg);
/**
 *	Loads a value from memory into reg.
 *	@param reg The reg to load the value into
 *	@param byteLength The number of bytes to load
 *	@param tempReg 4 bytes to be used internally
 *	@note uses and modifies A0-A3
 */
vector<Command *> loadCommand(uchar reg, uchar byteLength, uchar tempReg=REG_0);
/**
 *	Loads a value from end of stack into reg
 *	@param reg The reg to laod the value into
 *	@param byteLength The number of bytes to load
 *	@param tempReg 4 bytes to be used interally
 *	@note uses A0-A3
 */
vector<Command *> loadStackCommand(uchar reg, uchar byteLength, uchar tempReg=REG_0);
/**
 *	Loads a value from the address adr into the reg
 *	@param reg The reg to load the value into
 *	@param adr The address of the value to load
 *	@param byteLength The number of bytes to load
 *	@param tempReg 4 bytes to be used internally
 *	@note uses A0-A3
 */
vector<Command *> loadConstCommand(uchar reg, unsigned int adr, uchar byteLength, uchar tempReg=REG_0);


/**
 *	Stores a single byte from the reg into memory
 *	@param reg The reg that holds the byte
 *	@note uses A0-A3
 */
vector<Command *> storeCommand(uchar reg);
/**
 *	Stores a value from reg into memory
 *	@param reg The reg that holds the value
 *	@param byteLength The number of bytes to store
 *	@param tempReg 4 bytes to be used internally
 *	@note uses A0-A3
 */
vector<Command *> storeCommand(uchar reg, uchar byteLength, uchar tempReg=REG_0);
/**
 *	Stores a value from reg to the end of the stack.
 *	@param reg Teh reg that holds the value
 *	@param byteLnegth The number of bytes to store
 *	@param tempReg 4 bytes to be used internally
 *	@note uses A0-A3
 */
vector<Command *> storeStackCommand(uchar reg, uchar byteLength, uchar tempReg=REG_0);
/**
 *	Stores a value from the reg to the adr
 *	@param reg The reg that holds the value
 *	@param adr The address to load the value into
 *	@param byteLength The number of bytes to store
 *	@param tempReg 4 bytes to be used interally
 */
vector<Command *> storeConstCommand(uchar reg, unsigned int adr, uchar byteLength, uchar tempReg=REG_0);

/**
 *	Adds values in x and y registers
 *	@note uses x, y, o, c
 */
vector<Command *> addCommand();
/**
 *	Adds values (o + c = a + b + c)
 *	@param aReg The first value
 *	@param bReg The second value
 *	@param outReg The output value
 *	@param byteLength The number of bytes to add
 */
vector<Command *> addCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength);
/**
 *	Replaces last two values on stack with sum	
 *	@param byteLength The number of bytes to add
 *	@note uses REG_0 - REG_19 internally
 */
vector<Command *> addStackCommand(uchar byteLength);

/**
 *	Subtracts values in x and y registers
 *	
 */
vector<Command *> subtractCommand();
/**
 *	Subtracts values (o - c= a - b - c)
 *	@param aReg The first value
 *	@param bReg The second value
 *	@param outReg The output value
 *	@param byteLength The number of bytes to subtract
 */
vector<Command *> subtractCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength);
/**
 *	Replaces the last two values on the stack with the difference
 *	@param byteLength The number of bytes to subtract
 *	@note uses REG_) - REG_19 internally
 */
vector<Command *> subtractStackCommand(uchar byteLength);

/**
 *	Gets an input value using REG_IP
 *	@param reg The reg to load the byte of data into
 *	@note uses REG_IP to determain what channel to retrieve data from.
 */
vector<Command *> inputCommand(uchar reg);
/**
 *	Gets an input value from a provided channel
 *	@param reg The register to load the byte of data into
 *	@param channel The channel to input from.
 *	@note uses REG_IP internally
 */
vector<Command *> inputCommand(uchar reg, uchar channel);
/**
 *	Outputs a value from the reg
 *	@param reg The byte to send
 *	@note uses REG_OP to determain what channel to retrieve data from.
 */
vector<Command *> outputCommand(uchar reg);
/**
 *	Outputs a value to the provided channel
 *	@param reg The register to send data from
 *	@param channel The channel to output to.
 *	@note uses REG_OP interally
 */
vector<Command *> outputCommand(uchar reg, uchar channel);
/**
 *	Prints a value to the console
 *	@param The value to printf
 *	@note uses REG_OP interally
 */
vector<Command *> printCommand(uchar reg);

/**
 *	Jumps by A0-A3 if the value in reg is negative.
 *	@param reg The value to test if it is negative
 *	@note uses A0-A3 interally
 */
vector<Command *> tacCommand(uchar reg);
/**
 *	Jumpts by value in diffReg if the value in reg is negative.
 *	@param reg The value to test if it is negative
 *	@note uses A0-A3 interally
 */
vector<Command *> tacCommand(uchar reg, uchar diffReg);
/**
 *	Changes program counter
 *	@note uses value in A0-A3
 */
vector<Command *> jumpCommand();
/**
 *	Changes program counter by value in diffReg
 *	@note uses A0-A3
 */
vector<Command *> jumpCommand(uchar diffReg);

/**
 *	Does and operation to values in x and y
 */
vector<Command *> andCommand();
/**
 *	o = a && b
 *	@param aReg The first value
 *	@param bReg the second value
 *	@param outReg The output value
 *	@param byteLength The number of bytes to use
 */
vector<Command *> andCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength);
/**
 *	Repalces last two values on the stack with the and operation of both
 *	@param byteLength The number of bytes to use
 *	@note uses REG_0-REG_19 internally
 */
vector<Command *> andStackCommand(uchar byteLength);

/**
 *	Does OR operation to values x and y
 */
vector<Command *> orCommand();
/**
 *	o = a || byteLength
 *	@param aReg The first value
 *	@param bReg the second value
 *	@param outReg the output value
 *	@param byteLength The number of bytes to use
 */
vector<Command *> orCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength);
/**
 *	Replaces last two values on the stack with the or operation of both
 *	@param byteLength The number of bytes to use
 *	@note uses REG_0-REG_19 internally
 */
vector<Command *> orStackCommand(uchar byteLength);

/**
 *	Does NOT operation to value x
 */
vector<Command *> notCommand();
/**
 *	o = !x
 *	@param reg The value
 *	@param outReg the ouput value
 *	@param byteLength The number of bytes to use
 */
vector<Command *> notCommand(uchar reg, uchar outReg, uchar byteLength);
/**
 *	Replaces last value on stack with the not operation
 *	@param byteLength The number of bytes to use
 *	@note uses REG_0-REG_19 internally
 */
vector<Command *> notStackCommand(uchar byteLength);

/**
 *	Asks for more memory?
 *	idk how this is supposed to work yet
 */
vector<Command *> moreCommand(uchar reg);

/**
 * 	Does a shift right operation
 */
vector<Command *> shiftrCommand();
/**
 *	o = x >> 1
 *	@param reg The value
 *	@param outReg the output value
 *	@param byteLength The number of bytes to use
 */
vector<Command *> shiftrCommand(uchar reg, uchar outReg, uchar byteLength);
/**
 *	Replaces last value on stack with the shiftr operation
 *	@param byteLength The number of bytes to use
 *	@note uses REG_0-REG_19 internally
 */
vector<Command *> shiftrStackCommand(uchar byteLength);

/**
 *	Does a shift left operation
 */
vector<Command *> shiftlCommand();
/**
 *	 o x << 1
 *	 @param reg The value
 *	 @param outReg The output value
 *	 @param byteLength The number of bytes to use
 */
vector<Command *> shiftlCommand(uchar reg, uchar outReg, uchar byteLength);
/**
 *	Replaces last value on stack with the shiftl operation
 *	@param byteLength The number of bytes to use
 *	@note uses REG_0-REG_19 internally
 */
vector<Command *> shiftlStackCommand(uchar areg, uchar outReg, uchar byteLength);

/**
 *	Moves a byte from reg2 to reg1 (reg1 = reg2)
 */
vector<Command *> moveCommand(uchar reg1, uchar reg2);
/**
 *	Moves bytes from reg2 to reg1
 *	@param byteLength The number of bytes to use
 */
vector<Command *> moveCommand(uchar reg1, uchar reg2, uchar byteLength);

/**
 *	Sets a register to a hardcoded byte
 *	@param reg The reg to load the data into
 *	@param d The data to load
 */
vector<Command *> rawCommand(uchar reg, uchar d);
/**
 *	Sets register to a hardcoded value
 *	@param reg The reg to load the data into
 *	@param d The data load
 *	@param byteLength The number of bytes to use
 */
vector<Command *> rawCommand(uchar reg, uchar *d, int byteLength);
/**
 *	Sets a register to 2 bytes
 *	@param reg The reg to load the data into
 *	@param d The data to load
 */
vector<Command *> rawCommand(uchar reg, unsigned short d);
/**
 *	Sets a register to 4 bytes
 *	@param reg The reg to load the data into
 *	@param d The data to load
 */
vector<Command *> rawCommand(uchar reg, unsigned int d);
/**
 *	Sets a register to 8 bytes
 *	@param reg The reg to load the data into
 *	@param d The data to load
 */
vector<Command *> rawCommand(uchar reg, unsigned long d);

/**
 *	Increases the stack by the value in diffReg
 *	@param diffReg The value to change the stack by
 *	@param tempReg 4 bytes to be used internally
 */
vector<Command *> pushCommand(uchar diffReg, uchar tempReg=REG_0); //reg points to interface
/**
 *	Increases the stack by a constant value
 *	@param diff The value to change the stack by
 *	@param tempReg1 4 bytes to be used internally
 *	@param tempReg2 4 bytes to be used internaly
 */
vector<Command *> pushConstCommand(int diff, uchar tempReg1=REG_0, uchar tempReg2=REG_4);
/**
 *	Decreases the stack by the value in diffReg
 *	@param diffReg The value to change the stack by
 *	@param tempReg 4 bytes to be used internally
 */
vector<Command *> popCommand(uchar diffReg, uchar tempReg=REG_0); // reg points to int
/**
 *	Decerase the stack by a constant value
 *	@param diff The  value to change the stack bytes
 *	@param tempReg1 4 bytes to be used internally
 *	@param tempReg2 4 bytes to be used internally
 */
vector<Command *> popConstCommand(int diff, uchar tempReg1=REG_0, uchar tempReg2=REG_4);
/**
 *	Gets the stacak pointer with the given offset
 *	@param offsetAdr The offset to change the pointer by
 *	@param outReg Where to put the resulting address
 *	@param tempReg 4 bytes to be used internally
 */
vector<Command *> getStackAdrCommand(uchar offsetAdr, uchar outReg=REG_A0, uchar tempReg=REG_0); //reg points to int. 
/**
 *	Gets the stack pointer
 *	@param outReg The result
 *	@param tempReg 4 bytes to be used interally
 */
vector<Command *> getStackEndAdrCommand(uchar outReg=REG_A0, uchar tempReg=REG_0);

vector<Command *> mallocCommand(uchar lengthReg, uchar outReg=REG_A0);
vector<Command *> freeCommand(uchar adrReg=REG_A0);

/**
 *	Loads a var into the REG_0
 *	@note uses REG_0-REG_11 interally
 */
vector<Command *> getVarAdrCommand(string name, SymbolTable *table, int outReg=REG_A0);

/**
 	*	Gets a value from memory and pushes it to the stack
	*	@note uses registers interally
	*/
vector<Command *> pushVarCommand(string name, SymbolTable *table);
/**
	*	Pops a value from the stack and puts it into the var
	*	@note uses registers interally
	*/
vector<Command *> popVarCommand(string name, SymbolTable *table);

vector<Command *> command(StatementNode *node);
vector<Command *> command(BlockNode *node);
vector<Command *> command(PageNode *node);
vector<Command *> command(ExpressionNode *node);
vector<Command *> command(CreateVarNode *node);
vector<Command *> command(DefParamNode *node);
vector<Command *> command(DefFuncNode *node);
vector<Command *> command(DefStructNode *node);
vector<Command *> command(SetVarNode *node);
vector<Command *> command(SetPointerNode *node);
vector<Command *> command(IfNode *node);
vector<Command *> command(IfElseNode *node);
vector<Command *> command(WhileNode *node);
vector<Command *> command(ReturnNode *node);
vector<Command *> command(BreakNode *node);
vector<Command *> command(FloatNode *node);
vector<Command *> command(IntNode *node);
vector<Command *> command(StringNode *node);
vector<Command *> command(FunctionCallNode *node);
vector<Command *> command(OperationNode *node);
vector<Command *> command(PointerNode *node);
vector<Command *> command(GetPointerNode *node);
vector<Command *> command(GetVarNode *node);



#endif

