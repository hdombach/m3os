#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include "../nodes/node.hpp"
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

template <class T>
void append(vector<T> a, vector<T> b);

vector<uchar> loadCommand(uchar reg);
vector<uchar> loadCommand(uchar reg, uchar byteLength, uchar tempReg=REG_0);
vector<uchar> loadStackCommand(uchar reg, uchar byteLength, uchar tempReg=REG_0);
vector<uchar> loadConstCommand(uchar reg, unsigned int adr, uchar byteLength);

vector<uchar> storeCommand(uchar reg);
vector<uchar> storeCommand(uchar reg, uchar byteLength, uchar tempReg=REG_0);
vector<uchar> storeStackCommand(uchar reg, uchar byteLength, uchar tempReg=REG_0);
vector<uchar> storeConstCommand(uchar reg, unsigned int adr, uchar byteLength);

vector<uchar> addCommand();
vector<uchar> addCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength);
vector<uchar> addStackCommand(uchar byteLength);

vector<uchar> subtractCommand();
vector<uchar> subtractCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength);
vector<uchar> subtractStackCommand(uchar byteLength);

vector<uchar> inputCommand(uchar reg);
vector<uchar> inputCommand(uchar reg, uchar channel);
vector<uchar> outputCommand(uchar reg);
vector<uchar> outputCommand(uchar reg, uchar channel);
vector<uchar> printCommand(uchar reg);

vector<uchar> tacCommand(uchar reg);
vector<uchar> tacCommand(uchar reg, uchar diffReg);
vector<uchar> jumpCommand();
vector<uchar> jumpCommand(uchar diffReg);

vector<uchar> andCommand();
vector<uchar> andCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength);
vector<uchar> andStackCommand(uchar byteLength);

vector<uchar> orCommand();
vector<uchar> orCommand(uchar aReg, uchar bReg, uchar outReg, uchar byteLength);
vector<uchar> orStackCommand(uchar byteLength);

vector<uchar> notCommand();
vector<uchar> notCommand(uchar rg, uchar outReg, uchar byteLength);
vector<uchar> notStackCommand(uchar byteLength);

vector<uchar> moreCommand(uchar reg);

vector<uchar> shiftrCommand();
vector<uchar> shiftrCommand(uchar reg, uchar outReg, uchar byteLength);
vector<uchar> shiftrStackCommand(uchar byteLength);

vector<uchar> shiftlCommand();
vector<uchar> shiftlCommand(uchar reg, uchar outReg, uchar byteLength);
vector<uchar> shiftlStackCommand(uchar areg, uchar outReg, uchar byteLength);

vector<uchar> moveCommand(uchar reg1, uchar reg2);
vector<uchar> moveCommand(uchar reg1, uchar reg2, uchar byteLength);

vector<uchar> rawCommand(uchar reg, uchar d);
vector<uchar> rawCommand(uchar reg, uchar *d, int byteLength);
vector<uchar> rawCommand(uchar reg, unsigned short d);
vector<uchar> rawCommand(uchar reg, unsigned int d);
vector<uchar> rawCommand(uchar reg, unsigned long d);

vector<uchar> pushCommand(uchar diffReg, uchar tempReg=REG_0); //reg points to int
vector<uchar> pushConstCommand(int diff, uchar tempReg1=REG_0, uchar tempReg2=REG_4);
vector<uchar> popCommand(uchar diffReg, uchar tempReg=REG_0); // reg points to int
vector<uchar> popConstCommand(int diff, uchar tempReg1=REG_0, uchar tempReg2=REG_4);
vector<uchar> getStackAdrCommand(uchar offsetAdr, uchar outReg=REG_A0); //reg points to int. 
vector<uchar> getStackEndAdrCommand(uchar outReg=REG_A0);

vector<uchar> mallocCommand(uchar lengthReg, uchar outReg=REG_A0);
vector<uchar> freeCommand(uchar adrReg=REG_A0);

vector<uchar> command(PageNode page);
vector<uchar> command(BlockNode block);
vector<uchar> command(StatementNode statement);


#endif

