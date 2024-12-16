#pragma once 

#include "../cfg/ot/ot.h"
#include <stdint.h>

typedef struct LocalVar {
    char *name;
    char *typeName;
    uint8_t size;
    bool custom;
    bool isArray;
    uint32_t arrayDim;
} LocalVar;

void scanOperationTreeForVars(FunctionEntry *entry, OperationTreeNode *root);

LocalVar *createLocalVar(const char *name, const char *typeName, uint8_t size, bool custom, bool isArray);

void freeLocalVar(LocalVar *var);