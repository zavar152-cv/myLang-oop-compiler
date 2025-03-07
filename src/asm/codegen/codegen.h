#pragma once 

#include "../../cfg/cfg.h"
#include "../../cfg/ot/ot.h"
#include "../stringbuffer/stringbuffer.h"
#include <stdint.h>

#define REG_R0 "R0"
#define REG_R1 "R1"
#define REG_R2 "R2"
#define REG_R3 "R3"
#define REG_R4 "R4"
#define REG_R5 "R5"
#define REG_R6 "R6"
#define REG_R7 "R7"

#define REG_IP "IP"
#define REG_AR "AR"
#define REG_RT "RT"
#define REG_SP "SP"
#define REG_BP "BP"

#define REG_BR1 "BR1"
#define REG_BR2 "BR2"
#define REG_ALR "ALR"

#define REG_IN "IN"
#define REG_OUT "OUT"

#define OP_PLUS "+"
#define OP_MINUS "-"
#define OP_MUL "*"
#define OP_DIV "/"
#define OP_MOD "%"
#define OP_EQ "=="
#define OP_NEQ "!="
#define OP_GR ">"
#define OP_LE "<"
#define OP_GREQ ">="
#define OP_LEEQ "<="
#define OP_AND "&&"
#define OP_OR "||"

#define OP_NOT "NOT"
#define OP_NEG "NEG"

#define commentOTPosition(buffer, line, pos) ({stringbuffer_append_string(buffer, "\n  "); stringbuffer_append_string(buffer, ";OT at "); stringbuffer_append_long(buffer, line); stringbuffer_append_string(buffer, ":"); stringbuffer_append_long(buffer, pos + 1); stringbuffer_append_string(buffer, "\n");})
#define commentVar(buffer, name) ({stringbuffer_append_string(buffer, "  "); stringbuffer_append_string(buffer, ";var "); stringbuffer_append_string(buffer, name); stringbuffer_append_string(buffer, "\n");})
#define plain0(buffer, command) ({stringbuffer_append_string(buffer, "  "); stringbuffer_append_string(buffer, command); stringbuffer_append_string(buffer, "\n");})
#define plain1(buffer, command, arg1) ({stringbuffer_append_string(buffer, "  "); stringbuffer_append_string(buffer, command); stringbuffer_append_string(buffer, " "); stringbuffer_append_string(buffer, arg1); stringbuffer_append_string(buffer, "\n");})
#define plain2(buffer, command, arg1, arg2) ({stringbuffer_append_string(buffer, "  "); stringbuffer_append_string(buffer, command); stringbuffer_append_string(buffer, " "); stringbuffer_append_string(buffer, arg1); stringbuffer_append_string(buffer, ", "); stringbuffer_append_string(buffer, arg2); stringbuffer_append_string(buffer, "\n");})
#define plain3(buffer, command, arg1, arg2, arg3) ({stringbuffer_append_string(buffer, "  "); stringbuffer_append_string(buffer, command); stringbuffer_append_string(buffer, " "); stringbuffer_append_string(buffer, arg1); stringbuffer_append_string(buffer, ", "); stringbuffer_append_string(buffer, arg2); stringbuffer_append_string(buffer, ", "); stringbuffer_append_string(buffer, arg3); stringbuffer_append_string(buffer, "\n");})
#define size1(buffer, command, size, arg1) ({stringbuffer_append_string(buffer, "  "); stringbuffer_append_string(buffer, command); stringbuffer_append_string(buffer, " "); stringbuffer_append_string(buffer, size); stringbuffer_append_string(buffer, " "); stringbuffer_append_string(buffer, arg1); stringbuffer_append_string(buffer, "\n");})
#define size2(buffer, command, size, arg1, arg2) ({stringbuffer_append_string(buffer, "  "); stringbuffer_append_string(buffer, command); stringbuffer_append_string(buffer, " "); stringbuffer_append_string(buffer, size); stringbuffer_append_string(buffer, " "); stringbuffer_append_string(buffer, arg1); stringbuffer_append_string(buffer, ", "); stringbuffer_append_string(buffer, arg2); stringbuffer_append_string(buffer, "\n");})
#define sizeOffset3(buffer, command, size, arg1, arg2, arg3) ({stringbuffer_append_string(buffer, "  "); stringbuffer_append_string(buffer, command); stringbuffer_append_string(buffer, " "); stringbuffer_append_string(buffer, size); stringbuffer_append_string(buffer, " "); stringbuffer_append_string(buffer, arg1); stringbuffer_append_string(buffer, ", ["); stringbuffer_append_string(buffer, arg2); stringbuffer_append_string(buffer, ", "); stringbuffer_append_string(buffer, arg3); stringbuffer_append_string(buffer, "]"); stringbuffer_append_string(buffer, "\n");})
#define label0(buffer, label) ({stringbuffer_append_string(buffer, label); stringbuffer_append_string(buffer, ":\n");})
#define label1(buffer, label) ({stringbuffer_append_string(buffer, "."); stringbuffer_append_string(buffer, label); stringbuffer_append_string(buffer, ":\n");})
#define label2(buffer, label) ({stringbuffer_append_string(buffer, ".."); stringbuffer_append_string(buffer, label); stringbuffer_append_string(buffer, ":\n");})

#define commandHLT(buffer) ({plain0(buffer, "HLT");})
#define commandNOP(buffer) ({plain0(buffer, "NOP");})
#define commandRET(buffer) ({plain0(buffer, "RET");})

#define commandADD(buffer, size, reg1, reg2) ({size2(buffer, "ADD", size, reg1, reg2);})
#define commandSUB(buffer, size, reg1, reg2) ({size2(buffer, "SUB", size, reg1, reg2);})
#define commandMUL(buffer, size, reg1, reg2) ({size2(buffer, "MUL", size, reg1, reg2);})
#define commandDIV(buffer, size, reg1, reg2) ({size2(buffer, "DIV", size, reg1, reg2);})
#define commandMOD(buffer, size, reg1, reg2) ({size2(buffer, "MOD", size, reg1, reg2);})

#define commandST(buffer, size, reg1, reg2) ({size2(buffer, "ST", size, reg1, reg2);})
#define commandSToffset(buffer, size, reg1, reg2, offset) ({sizeOffset3(buffer, "ST", size, reg1, reg2, offset);})
#define commandLD(buffer, size, reg1, reg2) ({size2(buffer, "LD", size, reg1, reg2);})
#define commandLDoffset(buffer, size, reg1, reg2, offset) ({sizeOffset3(buffer, "LD", size, reg1, reg2, offset);})
#define commandLDCoffset(buffer, size, reg1, reg2, offset) ({sizeOffset3(buffer, "LDC", size, reg1, reg2, offset);})
#define commandLDI32(buffer, reg1, value32) ({plain2(buffer, "LDI32", reg1, value32);})
#define commandLDC64(buffer, reg1, constAddr) ({plain2(buffer, "LDC64", reg1, constAddr);})

#define commandPUSH(buffer, reg1) ({plain1(buffer, "PUSH", reg1);})
#define commandPOP(buffer, reg1) ({plain1(buffer, "POP", reg1);})

#define commandMOV(buffer, toReg, fromReg) ({plain2(buffer, "MOV", toReg, fromReg);})
#define commandMOVT(buffer, size, toReg, fromReg) ({size2(buffer, "MOVT", size, toReg, fromReg);})
#define commandMOVZX(buffer, size, toReg, fromReg) ({size2(buffer, "MOVZX", size, toReg, fromReg);})

#define commandMEMCPYC(buffer, toPtr, fromPtr, size) ({plain3(buffer, "MEMCPYC", toPtr, fromPtr, size);})

#define commandCBW(buffer, reg1, reg2) ({plain2(buffer, "CBW", reg1, reg2);})
#define commandCBD(buffer, reg1, reg2) ({plain2(buffer, "CBD", reg1, reg2);})
#define commandCBQ(buffer, reg1, reg2) ({plain2(buffer, "CBQ", reg1, reg2);})
#define commandCWD(buffer, reg1, reg2) ({plain2(buffer, "CWD", reg1, reg2);})
#define commandCWQ(buffer, reg1, reg2) ({plain2(buffer, "CWQ", reg1, reg2);})
#define commandCDQ(buffer, reg1, reg2) ({plain2(buffer, "CDQ", reg1, reg2);})

#define commandNEG(buffer, size, reg1) ({size1(buffer, "NEG", size, reg1);})
#define commandNOT(buffer, size, reg1) ({size1(buffer, "NOT", size, reg1);})
#define commandAND(buffer, size, reg1, reg2) ({size2(buffer, "AND", size, reg1, reg2);})
#define commandOR(buffer, size, reg1, reg2) ({size2(buffer, "OR", size, reg1, reg2);})

#define commandEQ(buffer, reg1) ({plain1(buffer, "EQ", reg1);})
#define commandNEQ(buffer, reg1) ({plain1(buffer, "NEQ", reg1);})
#define commandGR(buffer, reg1) ({plain1(buffer, "GR", reg1);})
#define commandLE(buffer, reg1) ({plain1(buffer, "LE", reg1);})
#define commandGREQ(buffer, reg1) ({plain1(buffer, "GREQ", reg1);})
#define commandLEEQ(buffer, reg1) ({plain1(buffer, "LEEQ", reg1);})

#define commandJMP(buffer, label) ({plain1(buffer, "JMP", label);})
#define commandJZ(buffer, label) ({plain1(buffer, "JZ", label);})
#define commandJNZ(buffer, label) ({plain1(buffer, "JNZ", label);})
#define commandJEQ(buffer, label) ({plain1(buffer, "JEQ", label);})
#define commandJNEQ(buffer, label) ({plain1(buffer, "JNEQ", label);})
#define commandJGR(buffer, label) ({plain1(buffer, "JGR", label);})
#define commandJLE(buffer, label) ({plain1(buffer, "JLE", label);})
#define commandJGREQ(buffer, label) ({plain1(buffer, "JGREQ", label);})
#define commandJLEEQ(buffer, label) ({plain1(buffer, "JLEEQ", label);})

#define commandCMP(buffer, size, reg1, reg2) ({size2(buffer, "CMP", size, reg1, reg2);})

#define commandCALL(buffer, label) ({plain1(buffer, "CALL", label);})
#define commandENTER(buffer, size) ({plain1(buffer, "ENTER", size);})
#define commandLEAVE(buffer, size) ({plain1(buffer, "LEAVE", size);})

void calcMaxRegs(OperationTreeNode *root, uint8_t *maxRegs);

void prepareRegsAndTemps(OperationTreeNode *root, bool debug);

void generateASMForOT(FunctionEntry *entry, OperationTreeNode *root, struct StringBuffer *buffer);

void generateASMForFunction(struct StringBuffer *buffer, FunctionInfo *func, FunctionEntry *funcE, bool main, bool debug);