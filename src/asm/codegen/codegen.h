#pragma once 

#include "../../cfg/ot/ot.h"
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
#define REG_IN "IN"
#define REG_OUT "OUT"

#define OP_PLUS "+"
#define OP_MINUS "-"
#define OP_MUL "*"
#define OP_DIV "/"
#define OP_MOD "%"

#define OP_NOT "NOT"
#define OP_NEG "NEG"

void calcMaxRegs(OperationTreeNode *root, uint8_t *maxRegs);

void prepareRegsAndTemps(OperationTreeNode *root);