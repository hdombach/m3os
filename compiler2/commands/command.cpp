#include "command.hpp"

vector<uchar> Command::getRaw() {
	vector<uchar> result = {instruction};
	append(result, args);
	return result;
};

Command::Command() {};

Command::Command(uchar instruction, vector<uchar> args) {
	this->instruction = instruction;
	this->args = args;
};

vector<uchar> TacCommand::getRaw() {
	vector<uchar> result = {COM_TAC};
	if (targetBlock != nullptr) {
		result;
	};
	return result;
};

TacCommand::TacCommand(vector<uchar> args) {
	this->instruction = COM_TAC;
	this->args = args;
};

TacCommand::TacCommand(vector<uchar> args, Command *target) {
	this->instruction = COM_TAC;
	this->targetCmd = target;
};

TacCommand::TacCommand(vector<uchar> args, BlockNode *target) {
	this->instruction = COM_TAC;
	this->targetBlock = target;
};

JumpCommand::JumpCommand(vector<uchar> args) {
	this->instruction = COM_JMP;
	this->args = args;
};

JumpCommand::JumpCommand(Command *target) {
	this->targetCmd = target;
};

JumpCommand::JumpCommand(BlockNode *target) {
	this->targetBlock = target;
};
